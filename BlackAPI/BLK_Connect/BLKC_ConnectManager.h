#ifndef _BLKC_CONNECTMANAGER_H_
#define _BLKC_CONNECTMANAGER_H_

#include <list>
#include "Semaphore.h"

#include "BLKC_Common.h"
#include "BLKC_ReceiveControlObserver.h"
#include "BLKC_ReceiveControl.h"
#include "BLKC_StubRequestManager.h"
#include "BLKC_StubMessageHandler.h"
#include "BLKC_MessageReceiver.h"
#include "BLKC_IdAndObjectContainer.h"
#include "BLKC_CallBackContainer.h"
#include "BLKC_DeleteInstanceManager.h"

class BLKC_ReceiveControl;

class BLKC_ConnectManager : public BLKC_ReceiveControlObserver
{
    public:
        BLKC_ConnectManager(int sfd, BLKS_SOCKET_CONTROLDATA *data);
	    ~BLKC_ConnectManager();
        void init( int sfd, BLKD_SOCKID sockid );
        void start( int connectionId, BLKD_SOCKID sockid );
        void exit();
        static ssize_t recvControlData(int sfd, BLKS_SOCKET_CONTROLDATA *data);
        bool matchPeerSysId(BLKS_SOCKET_CONTROLDATA *data);
        void srvRcv_Main(int connectionId, BLKD_SOCKID sockid);
        void notifyConnectError();
        static void releaseBuffer(unsigned char *buf);
        int sendReqData(SEQUENS_ID_T seqId, unsigned char* sendbuf, MESSAGE_SIZE_T sendsize, LARGE_PARAM_ARRY* param_arry);
        int sendSocket(int sock_fd, unsigned char *buf, MESSAGE_SIZE_T size, bool sendReqData = false);
        void dispatchDo(SEQUENS_ID_T seqId, uint32_t dispatch_msgsize, unsigned char* dispatch_buf, BLKC_ReceiveThreadContext* context );
	    void notifyReplyMessage(SEQUENS_ID_T seqnsId, unsigned char* buffer, MESSAGE_SIZE_T length );
        int sendHelthCheck();
        static void Stub_APIC_Call(BLKS_COMMONID* type_id, void *pt, BLKC_ReceiveThreadContext* context );
        static void *getObjectPt( uint32_t );
        static uint32_t getNewInstanceID( void * );
        static uint32_t findInstanceId( void* );
        void deleteInstanceId( uint32_t );
        static uint32_t findInstanceId(uint32_t session_id, void *obj);
	    static uint32_t getNewInstanceID(uint32_t session_id, void *instance);
        int sendRply(unsigned char* sendbuf, MESSAGE_SIZE_T sendsize);
	    int sendRply(unsigned char* sendbuf, MESSAGE_SIZE_T sendsize, LARGE_RET_VAL_ARRY& ret_arry);
        static void sendCallBack(uint32_t session_id, unsigned char* sendbuf, MESSAGE_SIZE_T sendsize);
	    static void sendCallBack(uint32_t session_id, unsigned char* sendbuf, MESSAGE_SIZE_T sendsize, LARGE_PARAM_ARRY& param_arry);
        int doSendCallBack(unsigned char* sendbuf, MESSAGE_SIZE_T sendsize);
	    int doSendCallBack(unsigned char* sendbuf, MESSAGE_SIZE_T sendsize, LARGE_PARAM_ARRY& param_arry);
        void sendRequestMessage( SEQUENS_ID_T seqID, unsigned char* buf, MESSAGE_SIZE_T len, LARGE_PARAM_ARRY* param_arry, LARGE_RET_VAL_ARRY* ret_arry );
        static CallBackContainer& getCallBackContainer();
        bool isSocketConnected(BLKD_SOCKID sockid);
        SEQUENS_ID_T getCallBackSequenceId();
	    SEQUENS_ID_T getObservableSequenceId();
        static void sendObserverNotify(uint32_t session_id, unsigned char* sendbuf, MESSAGE_SIZE_T sendsize);
	    static void sendObserverNotify(uint32_t session_id, unsigned char* sendbuf, MESSAGE_SIZE_T sendsize, LARGE_PARAM_ARRY& param_arry);
        int doSendObserverNotify(unsigned char* sendbuf, MESSAGE_SIZE_T sendsize);
	    int doSendObserverNotify(unsigned char* sendbuf, MESSAGE_SIZE_T sendsize, LARGE_PARAM_ARRY& param_arry);
        OBSERVER_ID_T resistObserverObject(void* obj);
        OBSERVER_ID_T findObserverId(void* obj);
        void addObserverObject(OBSERVER_ID_T id,void* obj);
        void* findObserverObject(OBSERVER_ID_T id);
        void deleteObserverObject(OBSERVER_ID_T id);
        bool isKillProcessor();
        pid_t getPeerSysTid();

    public:
        BLKC_DeleteInstanceManager* mDeleteInstanceManager;

    private:
        class ReceiveProcessor : public Runnable
        {
            public :
                ReceiveProcessor();
                virtual ~ReceiveProcessor();
                void setParam(BLKC_ConnectManager* connect_manager, int connectionId, BLKD_SOCKID sockid);
                void run();
                
            private :
                BLKC_ConnectManager* mConnectManager;
                int mConnectionId;

            public:
                void post(int fd);
                void wait(int* fd);
                BLKD_SOCKID getSockId();

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
                void setParam(BLKC_ConnectManager *manager, BLKD_SOCKID sockid);
                void run();
            private :
                BLKC_ConnectManager* mManager;
                BLKD_SOCKID mSockId;
        };

        class ObserverIdAndObjectContainer : public BLKC_IdAndObjectContainer<ObserverDestructor>
        {
            public:
                ObserverIdAndObjectContainer(){};
                ~ObserverIdAndObjectContainer(){};
                void deleteAllObject( uint32_t connectionId );
            private:
                void doDeleteAllObject( uint32_t connectionId );
        };
        ObserverIdAndObjectContainer* mObserverIdAndObjectContainer;

    private:
        void NotifyReceiveControl(Runnable* processor, BLKD_SOCKID sockid);
        int  sendMessage( SEQUENS_ID_T seqId, unsigned char* buf, MESSAGE_SIZE_T len, BLKD_SOCKID sockid, bool sendReqData = false);
        static MutexLock* getConnectManagerInstanceMutex(uint32_t session_id);
        void messageReceive(BLKC_ReceiveThreadContext* context, BLKD_SOCKID sockid);
        void executeRecv( BLKD_SOCKID sockid );
        void Recv_ConnectMgr_Temporary();

    private:
        int         mEpollFd;
        int         connectFD[BLKD_SOCKID_MAX];
        bool        mRecvThreadRunning[BLKD_SOCKID_MAX];
	    bool        mIsSocketConnected[BLKD_SOCKID_MAX];
        bool        mIsRecvThreadEnd[BLKD_SOCKID_MAX];
        pid_t	    mPeerSys_pid;
        pid_t	    mPeerSys_tid;
        int		    mPeerPriority;
        int         mConnectionId;
        MutexLock   mInstanceMutex;
        MutexLock   mSocketMutexLock;
        MutexLock   shm_mutex;
        ReceiveProcessor* mReceiveProcessor[BLKD_SOCKID_MAX];
        Thread*   mReceiveThread[BLKD_SOCKID_MAX];
        BLKC_ReceiveControl* mReceiveControl;
        static ThreadSafeMap<uint32_t, MutexLock*> mInstanceMutexList;
        BLKC_StubRequestManager *mStubRequestManager;
        BLKC_MessageReceiver* mMessageReceiver[BLKD_SOCKID_MAX];   
	    SEQUENS_ID_T mCallBackSequenseIdCounter;
	    SEQUENS_ID_T mObservableSequenseIdCounter;
        bool mIsKillProcessor;
        static BLKC_IdAndObjectContainer<void> mInstanceIdAndObjectContainer;
        static CallBackContainer mCallBackContainer;
        MutexLock mCallBackSqnsIdMutex;
        MutexLock mObservableSqnsIdMutex;
};

class InstanceScopeLock
{
	private :

		MutexLock* mLock;
	
	public :
		InstanceScopeLock(MutexLock* mutex)
		:mLock( mutex )
		{
			if( mLock != NULL ){
				mLock->lockWait();
			}
		}
		
		~InstanceScopeLock()
		{
			if( mLock != NULL ){
				mLock->unlock();
			}
		}
		
	private :
		InstanceScopeLock();
		InstanceScopeLock(const ScopeLock&);

		void* operator new(size_t) throw ()
		{
			return NULL;
		}
		
		void  operator delete(void*)
		{
		}
		
		void* operator &() const
		{
			return NULL;
		}
		void  operator =(const ScopeLock&)
		{
		}
};

#endif