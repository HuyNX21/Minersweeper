#ifndef __CLASS_BLKC_PROXYMANAGER_H_
#define __CLASS_BLKC_PROXYMANAGER_H_

#include <list>

#include "Thread.h"
#include "Runnable.h"
#include "Semaphore.h"
#include "ObservableExecutor.h"

#include "BLKC_Common.h"
#include "BLKC_MessageReceiver.h"
#include "BLKC_MessageHandlerBase.h"
#include "BLKC_PortNumberGetter.h"
#include "BLKC_ProxyMessageHandler.h"
#include "BLKC_ReceiveControl.h"
#include "BLKC_ProxyRequestManager.h"
#include "SignalHandle.h"
#include "BLKC_IdAndObjectContainer.h"
#include "BLKC_SyncIdAndObjectContainer.h"

// class BLKC_ReceiveThreadContext;

class BLKC_ProxyManager : public BLKC_ReceiveControlObserver
{
	public:
		typedef ThreadSafeMap<pthread_t , BLKC_ProxyManager*> PROXY_MANAGER_LIST_T;
		typedef std::map<pthread_t , BLKC_ProxyManager*>::iterator PROXY_MANAGER_LIST_IT_T;
		class ProxyManagerList : public PROXY_MANAGER_LIST_T
		{
			public:
				ProxyManagerList();
				~ProxyManagerList();
				bool isDestructing() { return mDestructing; }

			private:
				bool mDestructing;
		};
		
		class ProxyManagerListDeleter
		{
			public:
				ProxyManagerListDeleter(ProxyManagerList*& pt);
				~ProxyManagerListDeleter();
			private:
				
				ProxyManagerList*& mList;
			
		};

		class ProxyIdAndObjectContainer : public BLKC_IdAndObjectContainer<void>
		{
			public:
				ProxyIdAndObjectContainer();
			private:
				~ProxyIdAndObjectContainer();
		};
		ProxyIdAndObjectContainer* mInstanceIdAndObjectContainer;

    public:
		void dumnyMethod();
		static BLKC_ProxyManager* getInstance();
        ~BLKC_ProxyManager();
		static void deleteInstance();
		void connectWithServer(BLKD_SOCKID sockid);
        static void pthread_key_destructor(void* arg);
		void releaseBuffer(unsigned char *buf);
		void sendRequestData( SEQUENS_ID_T seqId, unsigned char* buf, MESSAGE_SIZE_T len, LARGE_PARAM_ARRY* mRequestLargeParamArry);
		void notifyConnectError(BLKD_SOCKID sockid);
		void NotifyReplyMessage(unsigned char *buf, MESSAGE_SIZE_T len, SEQUENS_ID_T seqId);
		void NotifyCallBackMessage(unsigned char *buf, MESSAGE_SIZE_T len, SEQUENS_ID_T seqId, BLKC_ReceiveThreadContext* context);
		void NotifyObserverMessage(unsigned char *buf, MESSAGE_SIZE_T len, SEQUENS_ID_T seqId, BLKC_ReceiveThreadContext* context);
		void setInstanceId( uint32_t , void* );
		void deleteInstanceId( uint32_t );
		uint32_t getInstanceId( void* );
		void* getObject( uint32_t );
		uint32_t reserveSyncObject();
		void addSyncObject( const std::type_info* type );
		void readySyncObject( uint32_t uDataIndex );
		bool waitSyncObject( const std::type_info* type );
		void signalSyncObject( uint32_t uDataIndex );
		void Send_ProxyMgr( unsigned char* , MESSAGE_SIZE_T );
		void Send_ProxyMgr( unsigned char* buf, MESSAGE_SIZE_T len, LARGE_RET_VAL_ARRY& ret_arry);
		void Send_ProxyMgr( unsigned char* buf, MESSAGE_SIZE_T len, LARGE_PARAM_ARRY& param_arry);
		void Send_ProxyMgr( unsigned char* buf, MESSAGE_SIZE_T len, LARGE_PARAM_ARRY& param_arry, LARGE_RET_VAL_ARRY& ret_arry);
		void SendRply_ProxyMgr(unsigned char* buf, MESSAGE_SIZE_T len);

		uint32_t setCallBackFP( uint32_t , void* );
		void* getCallBackFP( uint32_t );
		uint32_t getCallBackFPId( uint32_t );
		void deleteCallBackFP( uint32_t );
		void clearCallBackFP( void );

		void callBackExec(unsigned char* buf , MESSAGE_SIZE_T , SEQUENS_ID_T, void *object_pt, BLKC_ReceiveThreadContext* context);
		void observableExec(unsigned char* buf , MESSAGE_SIZE_T , SEQUENS_ID_T, void *object_pt, BLKC_ReceiveThreadContext* context);

		void SendRply_Observer( unsigned char* buf, BLKS_COMMONID* p_common_id, SEQUENS_ID_T seqId );

		OBSERVER_ID_T resistObserverObject(void* obj);
		OBSERVER_ID_T findObserverId(void* obj);
		void addObserverObject(OBSERVER_ID_T id,void* obj);
		void deleteObserverObject(OBSERVER_ID_T id);
		

	public:
		static ProxyManagerList* mProxyManagerList;
		BLKC_ProxyRequestManager* mProxyRequestManager;

	private:
        class ReceiveProcessor : public Runnable
		{
			public :
				ReceiveProcessor();
				virtual ~ReceiveProcessor();
				void setParam(BLKC_ProxyManager *manager, BLKD_SOCKID sockid);
				BLKD_SOCKID getSockId();
				void run();

			private :
				BLKC_ProxyManager *mProxyManager;

			public:
					void post(int fd);
					void wait(int* fd);
			private:
				std::list<int>	mOperationList;
				Semaphore		mOperationSemaphore;
				MutexLock		mOperationMutex;
				BLKD_SOCKID		mSockId;
		};

		class ReceiveProcessorTemporary : public Runnable
		{
			public :
				ReceiveProcessorTemporary();
				virtual ~ReceiveProcessorTemporary();
				void setParam(BLKC_ProxyManager *manager);
				void run();
			private :
				BLKC_ProxyManager* mManager;
		};

		class ConnectResetProcessor : public Runnable
		{
			public :
				ConnectResetProcessor(BLKC_ProxyManager* proxy_manager, BLKD_SOCKID sockid);
				virtual ~ConnectResetProcessor();
				void run();
			
			private :
				BLKC_ProxyManager *mProxyManager;
				BLKD_SOCKID mSockId;
		};

		ObservableExecutor* mObservableExecutor;

		class ObserverIdAndObjectContainer : public BLKC_IdAndObjectContainer<ObserverDestructor>
		{
			public:
				ObserverIdAndObjectContainer(){};
				~ObserverIdAndObjectContainer(){};
		};
		ObserverIdAndObjectContainer* mObserverIdAndObjectContainer;
    
    private:
        BLKC_ProxyManager();
		void init_Map();
		void exit();
		void init_ProxyMgr();
        void sendControlData(BLKD_SOCKID sockid);
        int  sendSocket(int sock_fd, unsigned char *buf, MESSAGE_SIZE_T size, BLKD_SOCKID sockid);
        void Recv_ProxyMgr(BLKD_SOCKID sockid);
        void messageReceive(BLKC_ReceiveThreadContext* context, BLKD_SOCKID sockid);
		void NotifyReceiveControl(Runnable* processor, BLKD_SOCKID sockid);
		void executeRecv( BLKD_SOCKID sockid );
		void Recv_ProxyMgr_Temporary();
		void sendRequestMessage( SEQUENS_ID_T, unsigned char* , MESSAGE_SIZE_T, LARGE_PARAM_ARRY* param_arry = NULL, LARGE_RET_VAL_ARRY* ret_arry = NULL );
		SEQUENS_ID_T getSequenceID();
		void sendMessage( SEQUENS_ID_T seqId, unsigned char* buf, MESSAGE_SIZE_T len, BLKD_SOCKID sockid );
		static int eraseProxyManagerList(bool bErase, BLKC_ProxyManager* pManager);
    
    private:
        MutexLock 				mSocketMutex;
		MutexLock 				mSocketErrorMutex;
		pid_t 					mConnectPid;
		pid_t 					mConnectTid;
		pthread_t				mConnectPThreadId;
		SEQUENS_ID_T 			mRequestSequenseIdCounter;
		int 					mEpollFd;
        int                     mSocketFd[BLKD_SOCKID_MAX];
        Thread*                 mReceiveThread[BLKD_SOCKID_MAX];
		ReceiveProcessor*       mReceiveProcessor[BLKD_SOCKID_MAX];
        bool                    mReceiveThreadRunning[BLKD_SOCKID_MAX];
        BLKC_MessageReceiver*   mMessageReceiver[BLKD_SOCKID_MAX];
		BLKC_ReceiveControl* 	mReceiveControl;
		bool 					mIsSocketConnected[BLKD_SOCKID_MAX];
		bool 					mIsRecvThreadEnd[BLKD_SOCKID_MAX];
		MutexLock 				mRequestSequenseIdMutex;
		static MutexLock		mNotifyConnectErrorMutex;

		BLKC_SyncIdAndObjectContainer* mSyncIdAndObjectContainer;
		static std::map< uint32_t , void* > callBackFPTbl;
		static MutexLock mCallbackFpTblMutex;
		static uint32_t mCallBackIdCounter;
		static MutexLock mCallBackIdMutex;

	private:
		// Declare callback functions
		void ANS__APIC_Call__req_funcCallback__4( unsigned char *buf, MESSAGE_SIZE_T len, SEQUENS_ID_T seqId );
		void ANS__APIC_MineModel__req_openCell__3( unsigned char *buf, MESSAGE_SIZE_T len, SEQUENS_ID_T seqId );
		void ANS__APIC_MineModel__req_toggleFlag__7( unsigned char *buf, MESSAGE_SIZE_T len, SEQUENS_ID_T seqId );

		// Callback function table
		typedef std::map<uint32_t, void (BLKC_ProxyManager::*)(unsigned char*, MESSAGE_SIZE_T, SEQUENS_ID_T)> CALLBACK_TBL;
		CALLBACK_TBL mCallbackFuncTbl;

		typedef std::map<uint32_t, void*> CALLBACK_ARGTBL;
		CALLBACK_ARGTBL mCallbackFuncArgTbl;
		
		typedef std::map<uint32_t, void*> PTR_ARGTBL;
		PTR_ARGTBL mPtrArgTbl;
};

#endif