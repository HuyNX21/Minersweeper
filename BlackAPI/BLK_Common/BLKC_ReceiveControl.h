#ifndef _BLKC_RECEIVECONTROL_H_
#define _BLKC_RECEIVECONTROL_H_

#include "Runnable.h"
#include "Thread.h"

#include "BLKC_Common.h"
#include "BLKC_ReceiveControlObserver.h"

#define BLKD_RXCTRL_STOP		((uint32_t)0x01)
#define BLKD_RXCTRL_START		((uint32_t)0x02)
#define BLKD_RXCTRL_END			((uint32_t)0x04)
#define BLKD_RXCTRL_WAIT		((uint32_t)0x08)
#define BLKD_RXCTRL_ENDREQ 		((uint32_t)0x40)
#define BLKD_RXCTRL_UPDATE		((uint32_t)0x80)

inline const char* convertRxControlToString(uint32_t control) {
    switch(control) {
        case BLKD_RXCTRL_STOP:
            return "BLKD_RXCTRL_STOP";
        case BLKD_RXCTRL_START:
            return "BLKD_RXCTRL_START";
        case BLKD_RXCTRL_END:
            return "BLKD_RXCTRL_END";
        case BLKD_RXCTRL_WAIT:
            return "BLKD_RXCTRL_WAIT";
        case BLKD_RXCTRL_ENDREQ:
            return "BLKD_RXCTRL_ENDREQ";
        case BLKD_RXCTRL_UPDATE:
            return "BLKD_RXCTRL_UPDATE";
        default:
            return "UNKNOWN_CONTROL";
    }
}

class BLKC_ReceiveControlObserver;

class BLKC_ReceiveControl
{
    public:
        enum E_RECEIVE_THREAD_MODE {
            MODE_RECEIVE = 0,
            MODE_RECEIVEASYNC,
            MODE_RECEIVETEMPORARY
        };

        enum E_RECEIVE_THREAD_STATE {
            STATE_IDLE = 0,
            STATE_EXEC,
            STATE_ENDING
        };

        BLKC_ReceiveControl();
        ~BLKC_ReceiveControl();
        static BLKC_ReceiveControl* newInstance(pid_t peer_pid, int sfd, BLKC_ReceiveControlObserver *manager, bool bProxy);
        static void exitAndDeleteInstance(pid_t peer_pid, int sfd[]);
        void start(bool mode, pid_t	pid);
        void setRxControl(int socketFd, uint32_t infomation);
        BLKD_SOCKID getSockId(pthread_t threadId = 0);
        void changeState(pthread_t threadId, enum E_RECEIVE_THREAD_STATE state);
        int  getFdSet(int epollfd);
        void getRxControl(int* pSocketFd, pthread_t* pThreadId, uint32_t* pInfomation);
        void changeFdState(int sfd, uint32_t ul_State);
        void notifyRxUpdate(int sfd);
        uint32_t getNoIdleState();
        void deleteReceiveThreadInfo(pthread_t threadId);
        void addReceiveThreadInfo(pthread_t threadId,
				enum E_RECEIVE_THREAD_STATE state,
				enum E_RECEIVE_THREAD_MODE mode,
				BLKC_ReceiveControlObserver* manager,
				Runnable* receiver,
				int sfd);
        void setSequenceId(SEQUENS_ID_T seqId);
        SEQUENS_ID_T getSequenceId();

    private:
        class Processor : public Runnable
        {
            public :
                Processor(BLKC_ReceiveControl*pReceiveControl );
                virtual ~Processor();
                void run();
            private :
                BLKC_ReceiveControl* mReceiveControl;
        };

        typedef struct {
            int32_t reference;
            BLKC_ReceiveControl* pReceiveControl;
        } BLKS_CTRL_T;
        typedef std::map<pid_t, BLKS_CTRL_T> BLKT_CTRL_MAP_T;

        struct FdInfo {
            BLKC_ReceiveControlObserver* mManager;
            uint32_t m_FdState;
        };

        struct ReciveThreadInfo 
        {
            enum E_RECEIVE_THREAD_STATE mState;
            enum E_RECEIVE_THREAD_MODE mMode;
            Runnable* mReceiver;
            BLKC_ReceiveControlObserver*	mManager;
            int mSfd;
            SEQUENS_ID_T mSeqId;
        };

        typedef struct {
            int 		sfd;
            pthread_t	threadId;
            uint32_t 	infomation;
        } BLKS_CONTROLDATA;

        typedef std::map<int, FdInfo> BLKT_FD_MAP_T;
        typedef std::map<pthread_t, ReciveThreadInfo> BLKT_RECEIVE_THREAD_MAP_T;

    private:
        int  openPipe();
        void closePipe();
        void mainLoop();
        void exit();
        Runnable* getWaitThreadInfo(int sfd, FdInfo* pFdInfo, BLKD_SOCKID* pSockId);
        void exitThreadForFd(int sfd);
        void deleteThreadInfoForFd(int sfd);

    private:
        bool                        mProxy;
        pid_t	                    mPid;
        bool                        mRunning;
        int                         mPipefd[2];
        Processor*                  mProcessor;
	    Thread*                     mThread;
        static MutexLock	        mMutex;
        static BLKT_CTRL_MAP_T 	    mCtrlMap;
        BLKT_FD_MAP_T   	        mFDMap;
        BLKT_RECEIVE_THREAD_MAP_T   mThreadMap;
};

inline const char* convertReceiveThreadStateToString(BLKC_ReceiveControl::E_RECEIVE_THREAD_STATE state) {
    switch(state) {
        case BLKC_ReceiveControl::STATE_IDLE:
            return "STATE_IDLE";
        case BLKC_ReceiveControl::STATE_EXEC:
            return "STATE_EXEC";
        case BLKC_ReceiveControl::STATE_ENDING:
            return "STATE_ENDING";
        default:
            return "UNKNOWN_STATE";
    }
}

#endif