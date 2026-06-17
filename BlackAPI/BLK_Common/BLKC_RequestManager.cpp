#include "pch.h"
#include "BLKC_RequestManager.h"

BLKC_RequestManager::BLKC_RequestManager( bool blProxy, pid_t connectTid ) : mProxy( blProxy ), mConnectTid( connectTid ){}
BLKC_RequestManager::~BLKC_RequestManager(){}

BLKC_RequestManager::SyncMediatorList::SyncMediatorList()
{
	mSyncMediatorMap.clear();
}

BLKC_RequestManager::SyncMediatorList::~SyncMediatorList()
{
	ScopeLock lock( mListMutexLock );
	mSyncMediatorMap.clear();
	mListMutexLock.unlock();
}

bool BLKC_RequestManager::SyncMediatorList::registMediator(SEQUENS_ID_T id, BLKC_SynchronizedMediator* mediator)
{
	ScopeLock lock( mListMutexLock );

	pair<MAP_SYNC_MEDIATOR::iterator, bool> result;

	result = mSyncMediatorMap.insert( make_pair( id,  mediator ));

	if(result.second == false){
		LOG_ERROR("std::map.insert() is failed.");
	}
	
	return result.second;
}

void BLKC_RequestManager::getSynchronizedRequestParam(SEQUENS_ID_T seqnsId, BLKS_SynchronizedRequestParam* pInfo)
{
	BLKC_SynchronizedMediator*	pMediator = NULL;
	memset(pInfo,0,sizeof(BLKS_SynchronizedRequestParam));

	try{
		pMediator = mSyncMediatorList.getMediator(seqnsId);
		if(pMediator == NULL) {
			return;
		}
		pMediator->getSynchronizedRequestParam(&pInfo->pRequestManager,  
									&pInfo->sequenceId, &pInfo->buffer, &pInfo->length, 
									&pInfo->param_arry, &pInfo->ret_arry);
	}catch(std::exception& ex){
		memset(pInfo,0,sizeof(BLKS_SynchronizedRequestParam));
	}
}

BLKC_SynchronizedMediator* BLKC_RequestManager::SyncMediatorList::getMediator(SEQUENS_ID_T id)
{
	ScopeLock lock( mListMutexLock );

	BLKC_SynchronizedMediator* ret = NULL;
	MAP_SYNC_MEDIATOR::iterator it = mSyncMediatorMap.find( id );
	MAP_SYNC_MEDIATOR::iterator it_end = mSyncMediatorMap.end();

	if(it != it_end){
		ret = (*it).second;
	}
	return ret;
}

void BLKC_RequestManager::releaseSyncWaitState()
{
	mSyncMediatorList.releaseSyncWaitState();
}

void BLKC_RequestManager::SyncMediatorList::releaseSyncWaitState()
{
	ScopeLock lock( mListMutexLock );

	MAP_SYNC_MEDIATOR::iterator it = mSyncMediatorMap.begin();
	MAP_SYNC_MEDIATOR::iterator it_end = mSyncMediatorMap.end();

	for (; it != it_end; ++it) {
		it->second->releaseSyncWaitState();
	}

	mSyncMediatorMap.clear();
}

bool BLKC_RequestManager::sendSynchronizedRequest(SEQUENS_ID_T seqnsId, unsigned char* buffer, MESSAGE_SIZE_T length, LARGE_PARAM_ARRY* param_arry, LARGE_RET_VAL_ARRY* ret_arry )
{
	bool ret = false;
	BLKC_SynchronizedMediator*	pMediator = NULL;
	bool blWriteControlLog = false;
	const char* scpCommonId = NULL;
	const char* scpKind = NULL;
	uint32_t ui32CommonId = 0;
	unsigned char ucKind = 0;
	uint32_t ui32PartitionIndex = 0;

	try{
		pMediator =  new BLKC_SynchronizedMediator;
		pMediator->setSynchronizedRequestParam( this, seqnsId, buffer, length, param_arry, ret_arry );

		ret = mSyncMediatorList.registMediator(seqnsId, pMediator);

		if(ret == true){
			pMediator->sendSynchronizedRequest( this, seqnsId, buffer, length, param_arry, ret_arry );
		}

		delete pMediator;
		pMediator = 0;
	}
	catch(std::exception& ex)
	{
		pMediator = mSyncMediatorList.getAndUnregist( seqnsId );
		delete pMediator;
		ret = false;
		LOG_ERROR("The exception was thrown out. %s",ex.what());
	}

	return ret;
}

BLKC_SynchronizedMediator* BLKC_RequestManager::SyncMediatorList::getAndUnregist(SEQUENS_ID_T id)
{

	ScopeLock lock( mListMutexLock );

	BLKC_SynchronizedMediator* ret = NULL;
	MAP_SYNC_MEDIATOR::iterator it = mSyncMediatorMap.find( id );
	MAP_SYNC_MEDIATOR::iterator it_end = mSyncMediatorMap.end();

	if(it != it_end){
		ret = (*it).second;
		mSyncMediatorMap.erase(it);
	}else{
		LOG_ERROR("std::map:mSyncMediatorMap.find(). Sequense-ID was not found., id = %u", id);
		LOG_ERROR("std::map:mSyncMediatorMap.size(). , size = %u", mSyncMediatorMap.size(), id);
		MESSAGE_SIZE_T cnt = 0;

		for(it = mSyncMediatorMap.begin();it != it_end;it++,cnt++){
			LOG_ERROR(",mSyncMediatorMap[%u], first = %u, second = %p", 
			                cnt, (*it).first, (*it).second);
		}
		LOG_ERROR("std::map.find(). Sequense-ID was not found. id = %u", id);
	}
	
	return ret;
	
}

void BLKC_RequestManager::notifyReplyMessage(SEQUENS_ID_T seqnsId, unsigned char* buffer, MESSAGE_SIZE_T length )
{
	try{
		bool blWriteControlLog = false;
		const char* scpCommonId = NULL;
		const char* scpKind = NULL;
		uint32_t ui32CommonId = 0;
		unsigned char ucKind = 0;
		uint32_t ui32PartitionIndex = 0;

		BLKC_SynchronizedMediator* mediator = mSyncMediatorList.getAndUnregist( seqnsId );

		mediator->notifyReplyMessage(seqnsId, buffer, length);

	}catch(std::exception& ex){
		LOG_ERROR("The exception was thrown out. %s",ex.what());
	}
}