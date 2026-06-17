#ifndef  __CLASS_BLKC_REQUESTMANAGER_H_
#define  __CLASS_BLKC_REQUESTMANAGER_H_

#include "MutexLock.h"

#include "BLKC_Common.h"
#include "BLKC_SynchronizedMediator.h"

class BLKC_SynchronizedMediator;

class BLKC_RequestManager
{
    public:
        typedef struct {
			BLKC_RequestManager* 	pRequestManager;
			SEQUENS_ID_T 			sequenceId;
			unsigned char* 			buffer;
			unsigned int 			length;
			LARGE_PARAM_ARRY* 		param_arry; 
			LARGE_RET_VAL_ARRY* 	ret_arry;
		} BLKS_SynchronizedRequestParam;
    
    public:
        BLKC_RequestManager( bool blProxy, pid_t connectTid );
        virtual ~BLKC_RequestManager();
        void getSynchronizedRequestParam(SEQUENS_ID_T seqnsId, BLKS_SynchronizedRequestParam* pInfo);
		void releaseSyncWaitState();
		bool sendSynchronizedRequest(SEQUENS_ID_T seqnsId, unsigned char* buffer, MESSAGE_SIZE_T length, LARGE_PARAM_ARRY* param_arry, LARGE_RET_VAL_ARRY* ret_arry );
		virtual int sendRequestData( SEQUENS_ID_T seqId, unsigned char* buf, MESSAGE_SIZE_T len, LARGE_PARAM_ARRY* param_arry) = 0;
		void notifyReplyMessage(SEQUENS_ID_T seqnsId, unsigned char* buffer, MESSAGE_SIZE_T length );

    private:
        class SyncMediatorList
		{
			public :
				SyncMediatorList();
				
				virtual ~SyncMediatorList();

				bool registMediator(SEQUENS_ID_T id, BLKC_SynchronizedMediator* mediator);

				BLKC_SynchronizedMediator* getAndUnregist(SEQUENS_ID_T id);
				BLKC_SynchronizedMediator* getMediator(SEQUENS_ID_T id);
				void releaseSyncWaitState();

			private :

				typedef std::map<SEQUENS_ID_T, BLKC_SynchronizedMediator*> MAP_SYNC_MEDIATOR;

				MAP_SYNC_MEDIATOR mSyncMediatorMap;
				MutexLock mListMutexLock;
		};

    private:
        bool mProxy;
		pid_t mConnectTid;
        SyncMediatorList mSyncMediatorList;
};

#endif