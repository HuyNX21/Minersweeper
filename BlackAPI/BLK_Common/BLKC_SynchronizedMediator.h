#ifndef __CLASS_BLKC_SYNCHRONIZEDMEDIATOR_H_
#define __CLASS_BLKC_SYNCHRONIZEDMEDIATOR_H_

#include "Runnable.h"
#include "ConditionCheck.h"
#include "ThreadConditionWait.h"

#include "BLKC_Common.h"
#include "BLKC_RequestManager.h"

class ThreadConditionWait;
class BLKC_RequestManager;

class BLKC_SynchronizedMediator
{
    public:
        BLKC_SynchronizedMediator();
        virtual ~BLKC_SynchronizedMediator();
        static BLKC_SynchronizedMediator* getNewInstance();
        void init();
        void getSynchronizedRequestParam(BLKC_RequestManager** pManager, SEQUENS_ID_T* pSeqnsId, unsigned char** pBuffer, unsigned int* pLength,LARGE_PARAM_ARRY** pParam_arry, LARGE_RET_VAL_ARRY** pRet_arry );
        void setSynchronizedRequestParam(BLKC_RequestManager *manager, SEQUENS_ID_T seqnsId, unsigned char* buffer, unsigned int length,LARGE_PARAM_ARRY* param_arry, LARGE_RET_VAL_ARRY* ret_arry );
        void releaseSyncWaitState();
        void sendSynchronizedRequest(BLKC_RequestManager *manager, SEQUENS_ID_T seqnsId, unsigned char* buffer, unsigned int length,LARGE_PARAM_ARRY* param_arry, LARGE_RET_VAL_ARRY* ret_arry );
        void notifyReplyMessage(SEQUENS_ID_T seqnsId, const unsigned char* buffer, unsigned int length );
        void RecvReply(SEQUENS_ID_T seqnsId, const unsigned char* buffer, unsigned int length );

    private:
        class SyncConditionCheck : public ConditionCheck
		{
			public :
				SyncConditionCheck();
				virtual ~SyncConditionCheck();
				bool checkCondition();
				void setCondition(bool);

			private:
				bool mIsCondition;
		};

        class ReplyProcessor : public Runnable
		{
			public :
				ReplyProcessor(BLKC_SynchronizedMediator *mediator, 
				                               SEQUENS_ID_T sequenceID,
				                               const unsigned char* buffer,
				                               unsigned int size);
				~ReplyProcessor();
            
				void run();
			
			private :
				BLKC_SynchronizedMediator *mMediator;
				SEQUENS_ID_T   mSequenceID;
				const unsigned char* mReplyDataBuffer;
				unsigned int   mReplyDataSize;
		};

    private:
        unsigned char* mSendBuffer;
        SyncConditionCheck* mConditionCheck;
		ThreadConditionWait* mThreadConditionWait;
        BLKC_RequestManager* mRequestManager;
        SEQUENS_ID_T mSequenceId;
        MESSAGE_SIZE_T mLength;
		LARGE_PARAM_ARRY* mParam_arry;
		LARGE_RET_VAL_ARRY* mRet_arry;
        ReplyProcessor* mReplyProcessor;
};

#endif