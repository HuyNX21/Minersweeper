#include "pch.h"

#include "BLKC_Common.h"
#include "BLKC_CallBackContainer.h"
#include "BLKC_CallBackSemaphore.h"

const uint32_t CallBackContainer::CALL_BACK_ID_PREFIX_MASK = 0xffff0000;
		
CallBackContainer::CallBackContainer()
	: mCurrentValContainer( NULL )
{
}
	
CallBackContainer::~CallBackContainer()
{
	CALL_BACK_CONTAINER::iterator it = mContainer.begin();
	CALL_BACK_CONTAINER::iterator it_end = mContainer.end();
	
	for(;it != it_end;it++){
		delete (*it).second;
	}
}
	
bool CallBackContainer::regist(uint32_t call_back_id, uint32_t session_id)
{
	bool ret = true;
	uint32_t cbid_prefix = call_back_id & 0xffff0000;

	BLKC_CallBackSemaphore::lock( cbid_prefix );

	{
	CallBackContainerScopeLock lock(*this);
	
	try{
		CALL_BACK_VAL_CONTAINER *val_container;
		ret = getContainer(cbid_prefix, val_container);
		if ( ret == true ) {
			val_container->insert( make_pair(call_back_id , session_id) );
		}
		else {
			CALL_BACK_VAL_CONTAINER::iterator it = val_container->find( cbid_prefix );
			while( it != val_container->end() ){
				if((*it).second == session_id){
					return false;
				}
				it++;
			}
			val_container->insert( make_pair(call_back_id , session_id) );
			ret = true;
		}

	}catch(exception& ex){
		LOG_ERROR("The exception was thrown out. %s\n",ex.what());
	}
	
	}
	
	return ret; 

}

void CallBackContainer::lock()
{
	mMutex.lockWait();
}

void CallBackContainer::unlock()
{
	mMutex.unlock();
}

bool CallBackContainer::begin(uint32_t cbid_prefix,
                              uint32_t& call_back_id,
                              uint32_t& session_id)
{
	CallBackContainerScopeLock lock(*this);

	CALL_BACK_CONTAINER::iterator it = mContainer.find( cbid_prefix );

	if(it == mContainer.end()){
		LOG_ERROR("map.find() is failed.\n");
		return false;
	}
	
	mCurrentValContainer = (*it).second;
	mCurrentIterator = mCurrentValContainer->begin();
	
	
	bool result = getElement( mCurrentIterator, call_back_id, session_id);
	if( result == true ){
		mCurrentValContainer->erase( mCurrentIterator );
		BLKC_CallBackSemaphore::unlock( cbid_prefix );
}

	return result;
	
}

bool CallBackContainer::next(uint32_t& call_back_id, uint32_t& session_id)
{
	return false;
}

void CallBackContainer::eraseSession(uint32_t session_id)
{
	ScopeLock lock( mMutex );
	
	CALL_BACK_CONTAINER::iterator it_1 = mContainer.begin();
	CALL_BACK_CONTAINER::iterator it_1_end = mContainer.end();
	
	for(; it_1 != it_1_end ; it_1++){
		CALL_BACK_VAL_CONTAINER::iterator erace_it = (*it_1).second->begin();
		CALL_BACK_VAL_CONTAINER::iterator erace_it_end = (*it_1).second->end();
		while( erace_it != erace_it_end ){
			if((*erace_it).second == session_id){
				BLKC_CallBackSemaphore::unlock( (*it_1).first );
				(*it_1).second->erase( erace_it++ );
			}else{
				erace_it++;
			}
		}
	}
	
}

void CallBackContainer::unregist(uint32_t cbid_prefix)
{
	BLKC_CallBackSemaphore::unlock(cbid_prefix);
}

bool CallBackContainer::getContainer(uint32_t cbid_prefix, CALL_BACK_VAL_CONTAINER*& ret_container)
{
	bool ret = true;

	CALL_BACK_CONTAINER::iterator it;
	try{
		it = mContainer.find( cbid_prefix );
		if(it == mContainer.end()){
			pair<CALL_BACK_CONTAINER::iterator, bool> result;
			result = mContainer.insert( make_pair(cbid_prefix, new CALL_BACK_VAL_CONTAINER) );
			if(result.second != true){
				LOG_ERROR("map.insert() is failed. cbid_prefix = %#x", cbid_prefix);
			}
			it = result.first;
		}else{
			ret = false;
		}
	}catch(exception& ex){
		LOG_ERROR("The exception was thrown out. %s\n",ex.what());
	}
	
	ret_container = (*it).second;
	return ret;
}

bool CallBackContainer::getElement(CALL_BACK_VAL_CONTAINER::iterator it,
		                uint32_t& call_back_id,
		                uint32_t& session_id)
{
	if(it == mCurrentValContainer->end()){
		return false;
	}
	call_back_id = (*it).first;
	session_id = (*it).second;
	return true;
}


CallBackContainerScopeLock::CallBackContainerScopeLock(CallBackContainer& container)
:mContainer( container )
{
	mContainer.lock();
}

CallBackContainerScopeLock::~CallBackContainerScopeLock()
{
	mContainer.unlock();
}



