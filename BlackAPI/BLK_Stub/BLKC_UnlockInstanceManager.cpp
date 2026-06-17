#include "pch.h"
#include "BLKC_UnlockInstanceManager.h"

BLKC_UnlockInstanceManager::BLKC_UnlockInstanceManager()
{
}

BLKC_UnlockInstanceManager::~BLKC_UnlockInstanceManager()
{
}

void BLKC_UnlockInstanceManager::registInstance( BLKC_UnlockInstance* p_UnlockInstance )
{
	ScopeLock lock( mMutex );
	
	mUnlockInstanceList.push_back( p_UnlockInstance );
}

void BLKC_UnlockInstanceManager::deleteInstance( void* p_ApicInstance, uint32_t SessionID )
{
	ScopeLock lock( mMutex );
	
	if( mUnlockInstanceList.empty() ){
		return;
	}

	list<BLKC_UnlockInstance*>::reverse_iterator rit = mUnlockInstanceList.rbegin();
	while( rit != mUnlockInstanceList.rend() )
	{
		BLKC_UnlockInstance* object = *rit;
		if( object->checkInsAndSessionID(p_ApicInstance, SessionID) ){
			delete object;
			mUnlockInstanceList.remove(object);
			rit = mUnlockInstanceList.rend();
			break;
		}
		++rit;
	}
}

void BLKC_UnlockInstanceManager::onUnlockFlag( uint32_t SessionID )
{
	if( mUnlockInstanceList.empty() ){
		return;
	}

	list<BLKC_UnlockInstance*>::reverse_iterator rit = mUnlockInstanceList.rbegin();
	while( rit != mUnlockInstanceList.rend() )
	{
		BLKC_UnlockInstance* object = *rit;
		object->onUnlockFlag(SessionID);
		++rit;
	}
}

void BLKC_UnlockInstanceManager::callUnlock()
{
	if( mUnlockInstanceList.empty() ){
		return;
	}

	list<BLKC_UnlockInstance*>::reverse_iterator rit = mUnlockInstanceList.rbegin();
	bool b_unlockFlag = true;
	while( rit != mUnlockInstanceList.rend() && b_unlockFlag )
	{
		BLKC_UnlockInstance* object = *rit;
		b_unlockFlag = object->callUnlock();
		if( b_unlockFlag ) mUnlockInstanceList.pop_back();
		rit = mUnlockInstanceList.rbegin();
	}

}

void  BLKC_UnlockInstanceManager::endSession( uint32_t SessionID )
{
	ScopeLock lock( mMutex );
	
	onUnlockFlag(SessionID);
	callUnlock();
}

void BLKC_UnlockInstanceManager::dump_UnlockInsTbl( int mode )
{
	LOG_INFO("regist count : %d\n", mUnlockInstanceList.size());
	if ( mode == 1 ) {
		list<BLKC_UnlockInstance*>::iterator it = mUnlockInstanceList.begin();
		uint32_t count = 0;
		while( it != mUnlockInstanceList.end() ) {
			BLKC_UnlockInstance* object = *it;
			object->outputLog( ++count );
			++it;
		}
	}
}