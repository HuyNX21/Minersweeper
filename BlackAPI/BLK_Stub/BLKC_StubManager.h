#ifndef _BLKC_STUBMANAGER_H_
#define _BLKC_STUBMANAGER_H_

#include "BLKC_Common.h"
#include "BLKC_ConnectManager.h"
#include "BLKC_PortNumberGetter.h"
#include "BLKC_UnlockInstanceManager.h"

static const int BLKD_CONNECTID_MAX = (7*2);

class BLKC_StubManager
{
    public:
        void dumnyMethod();
        static BLKC_StubManager* getInstance();
        ~BLKC_StubManager();
        static void bootStubManager();
        BLKC_ConnectManager* getConnectManager(int connectionId);
	    BLKC_ConnectManager* getConnectManager(BLKS_SOCKET_CONTROLDATA *data, int *connectionId);
        void NotifyConnectManagerError(int connectionId, BLKD_SOCKID sockid);
        void connectKillProcessorEndNotify(int connectionId);

    private:

        class ConnectProcessor : public Runnable
        {
            public :
                ConnectProcessor(BLKC_StubManager& stub_manager);
                virtual ~ConnectProcessor();
                void run();
                
            private :
                BLKC_StubManager& mStubManager;
        };

        class ConnectKillProcessor : public Runnable
        {
            public :
                ConnectKillProcessor(BLKC_ConnectManager* connect_manager, int connectionId, BLKD_SOCKID sockid);            
                virtual ~ConnectKillProcessor();
                void run();
                
            private :
                BLKC_ConnectManager* mConnectManager;
                int mConnectionId;
                BLKD_SOCKID mSockId;
        };

    private:
        BLKC_StubManager();
        void init();
        void exit();
        void* connectWait_Main();
        void closeSocket();
        int getEpollMsec(struct timeval *timeout, struct timespec (&elapsed)[2]);
        void calcEpollElapsed(int nfds, struct timeval *timeout, struct timespec (&elapsed)[2]);
        int addConnectManager(BLKC_ConnectManager* connectManager);
        void deleteConnectManager(int connectionId);
        BLKC_UnlockInstanceManager* mUnlockInstanceManager;

    private:
        static BLKC_StubManager* thisInstance;
        static pthread_once_t mOnceInit;
        Thread* mConnectThread;
	    ConnectProcessor* mConnectProcessor;
        int mConnectSocketFd;
        int mEpollFd;
        bool mConnectThreadRunning;
        MutexLock *mConnectMngListMutex;
        typedef std::vector<BLKC_ConnectManager*> CONNECT_MANAGER_LIST_T;
	    CONNECT_MANAGER_LIST_T mConnectManagerList;
};

#endif