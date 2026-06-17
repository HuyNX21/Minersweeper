#include "pch.h"
#include "Semaphore.h"
#include "ThreadSafeMap.h"
#include "ThreadSafeSingleton.h"

#include "BLKC_Common.h"
#include "BLKC_CallBackSemaphore.h"


typedef std::map<uint32_t, Semaphore*> SEMPHORE_MAP_T;

BLKC_CallBackSemaphore* BLKC_CallBackSemaphore::mThisInstace = NULL;

static const uint32_t mCallBackIdMask = 0xffff0000;


void BLKC_CallBackSemaphore::lock(uint32_t callback_id)
{
	if( mThisInstace == NULL ){
		mThisInstace = ThreadSafeSingleton<BLKC_CallBackSemaphore>::getInstance();
	}
	mThisInstace->doLock( callback_id );
}

	
void BLKC_CallBackSemaphore::unlock(uint32_t callback_id)
{

	if( mThisInstace == NULL ){
		return;
	}

	mThisInstace->doUnlock( callback_id );
}
	
BLKC_CallBackSemaphore::BLKC_CallBackSemaphore()
{
	mSemaphoreList = new SEMPHORE_LIST_T;
}

BLKC_CallBackSemaphore::BLKC_CallBackSemaphore(const BLKC_CallBackSemaphore& arg)
:mSemaphoreList( NULL )
{
	
}

BLKC_CallBackSemaphore::~BLKC_CallBackSemaphore()
{
	delete mSemaphoreList;
}
	
void BLKC_CallBackSemaphore::doLock(uint32_t callback_id)
{
	static const int32_t timeout_sec = 1 * 10;
	static const int32_t timeout_nanosec = 0;
	
	
	uint32_t key_val = callback_id & mCallBackIdMask;
	Semaphore* sem = NULL;
	
	{		
		ScopeLock( mSemaphoreList->mutex() );
		
		SEMPHORE_MAP_T& sem_map = mSemaphoreList->reference();
		
		SEMPHORE_MAP_T::iterator it = sem_map.find( key_val );
		SEMPHORE_MAP_T::iterator it_end = sem_map.end();
		
		if( it == it_end ){
			sem = new Semaphore(1);
			sem_map.insert( std::make_pair( key_val, sem ) );
		}else{
			sem = (*it).second;
		}
	}

#if 1
	bool result = false;
	do{
		LOG_DEBUG("Try to lock semaphore. CBID = %#x", key_val);
		result = sem->timedWait( timeout_sec, timeout_nanosec );
		if(result == false){
			sem->post();
		}
	}while(result == false);
#else
	printf("%s,%d,Try to lock semaphore. CBID = %#x\n", __FUNCTION__, __LINE__, key_val);
	sem->wait();

#endif
	LOG_DEBUG("To lock semaphore is successed!!! CBID = %#x", key_val);
	return;
	
}


void BLKC_CallBackSemaphore::doUnlock(uint32_t callback_id)
{
	uint32_t key_val = callback_id & mCallBackIdMask;
	Semaphore* sem = NULL;
	{
		ScopeLock( mSemaphoreList->mutex() );
		
		SEMPHORE_MAP_T& sem_map = mSemaphoreList->reference();
		
		SEMPHORE_MAP_T::iterator it = sem_map.find( key_val );
		SEMPHORE_MAP_T::iterator it_end = sem_map.end();
		
		if( it == it_end ){
			// assert
			LOG_ERROR("To unlock semaphore is failed. unkown CBID(=%#x)!!!", key_val);
			return;
		}
		LOG_DEBUG("To unlock semaphore is successed. CBID(=%#x)!!!", key_val);
		sem = (*it).second;

	}

	sem->post();
	
	return;
}
	
