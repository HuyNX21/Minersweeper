#include "pch.h"
#include "Thread.h"
#include "BLKC_SynchronizedMediator.h"

BLKC_SynchronizedMediator* BLKC_SynchronizedMediator::getNewInstance()
{
	BLKC_SynchronizedMediator* ret = NULL;
	
	try{
		ret = new BLKC_SynchronizedMediator();
		ret->init();
	}catch(std::exception& ex){
        LOG_ERROR("The exception was thrown out. %s\n",ex.what());
	}

	return ret;
}

BLKC_SynchronizedMediator::BLKC_SynchronizedMediator() : mSendBuffer( NULL ), mRequestManager( NULL )
{
	mConditionCheck = NULL;
	mThreadConditionWait = NULL;
	// mSequenceId = 0;
	// mLength = 0;
	// mParam_arry = NULL;
	// mRet_arry = NULL;
	// mReplyProcessor = NULL;
	// mReplyThread = NULL;
	
	try {
		mConditionCheck = new SyncConditionCheck();
	} catch(...) {
		return;
	}
	if(NULL == mConditionCheck){
		return;
	}
	
	try {
		mThreadConditionWait = new ThreadConditionWait( mConditionCheck );
	} catch(...) {
		return;
	}
	if(NULL == mThreadConditionWait){
		return;
	}
}

BLKC_SynchronizedMediator::~BLKC_SynchronizedMediator()
{
	delete mThreadConditionWait;
	delete mConditionCheck;
}

void BLKC_SynchronizedMediator::init()
{
	if(NULL == mConditionCheck){
		return;
	}

	mConditionCheck->setCondition( false );
}

BLKC_SynchronizedMediator::SyncConditionCheck::SyncConditionCheck()
{
	mIsCondition = false;
}

BLKC_SynchronizedMediator::SyncConditionCheck::~SyncConditionCheck()
{
}

void BLKC_SynchronizedMediator::SyncConditionCheck::setCondition( bool condition )
{
	mIsCondition = condition;
}

bool BLKC_SynchronizedMediator::SyncConditionCheck::checkCondition()
{
	return mIsCondition;
}

void BLKC_SynchronizedMediator::setSynchronizedRequestParam(BLKC_RequestManager *manager, SEQUENS_ID_T seqnsId, unsigned char* buffer, unsigned int length,LARGE_PARAM_ARRY* param_arry, LARGE_RET_VAL_ARRY* ret_arry )
{
	mRequestManager = manager;
	mSequenceId = seqnsId;
	mSendBuffer = buffer;
	mLength = length;
	mParam_arry = param_arry;
	mRet_arry = ret_arry;
}

void BLKC_SynchronizedMediator::getSynchronizedRequestParam(BLKC_RequestManager** pManager, SEQUENS_ID_T* pSeqnsId, unsigned char** pBuffer, unsigned int* pLength,LARGE_PARAM_ARRY** pParam_arry, LARGE_RET_VAL_ARRY** pRet_arry )
{
	*pManager = mRequestManager;
	*pSeqnsId = mSequenceId;
	*pBuffer = mSendBuffer;
	*pLength = mLength;
	*pParam_arry = mParam_arry;
	*pRet_arry  =  mRet_arry;
}

void BLKC_SynchronizedMediator::releaseSyncWaitState()
{
	if(NULL == mConditionCheck){
		return;
	}
	if(NULL == mThreadConditionWait){
		return;
	}
	
	if ( false == mConditionCheck->checkCondition() ) {
		mThreadConditionWait->lockWait();
		mConditionCheck->setCondition( true );
		mThreadConditionWait->wakeup();
		mThreadConditionWait->unlock();
	}
}

void BLKC_SynchronizedMediator::sendSynchronizedRequest( BLKC_RequestManager *manager, SEQUENS_ID_T seqnsId, unsigned char* buffer, unsigned int length, LARGE_PARAM_ARRY* param_arry,  LARGE_RET_VAL_ARRY* ret_arry)
{
	if(NULL == mThreadConditionWait){
		return;
	}

	mThreadConditionWait->lockWait();

	init();

	mSendBuffer = buffer;
	mRequestManager = manager;
	mSequenceId = seqnsId;
	mLength = length;
	mParam_arry = param_arry;
	mRet_arry = ret_arry;

	int ret = mRequestManager->sendRequestData( seqnsId, buffer, length, param_arry);

	if (-1 == ret) {
		mThreadConditionWait->unlock();
		LOG_ERROR("send request data error");
		return;
	}

	LOG_INFO("Thread wait request");

	mThreadConditionWait->wait();

	mThreadConditionWait->unlock();

	LOG_INFO("Thread wake up request");
}

void BLKC_SynchronizedMediator::notifyReplyMessage(SEQUENS_ID_T seqnsId, const unsigned char* buffer, unsigned int length )
{
	ReplyProcessor mReplyProcessor( this, seqnsId, buffer, length );
	mReplyProcessor.run();
	
}

BLKC_SynchronizedMediator::ReplyProcessor::ReplyProcessor(BLKC_SynchronizedMediator *mediator, SEQUENS_ID_T sequenceID, const unsigned char *buffer, unsigned int size)
{
	mMediator = mediator;
	mSequenceID = sequenceID;
	mReplyDataBuffer = buffer;
	mReplyDataSize = size;
}

BLKC_SynchronizedMediator::ReplyProcessor::~ReplyProcessor()
{
}


void BLKC_SynchronizedMediator::ReplyProcessor::run()
{
	try{
		mMediator->RecvReply( mSequenceID, mReplyDataBuffer, mReplyDataSize);
	}catch(std::exception& ex){
		LOG_ERROR("The exception was thrown out. %s\n",ex.what());
	}
}

void BLKC_SynchronizedMediator::RecvReply(SEQUENS_ID_T seqnsId, const unsigned char* buffer, unsigned int length )
{
	if(NULL == mConditionCheck){
		return;
	}
	if(NULL == mThreadConditionWait){
		return;
	}

	memcpy( mSendBuffer, buffer, length);

	mThreadConditionWait->lockWait();

	mConditionCheck->setCondition( true );

	mThreadConditionWait->wakeup();

	mThreadConditionWait->unlock();


	LOG_INFO("wakeup waiting...");
}