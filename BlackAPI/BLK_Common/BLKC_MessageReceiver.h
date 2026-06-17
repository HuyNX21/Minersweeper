#ifndef __CLASS_BLKC_MESSAGERECEIVER_H_
#define __CLASS_BLKC_MESSAGERECEIVER_H_


#include "BLKC_Common.h"
#include "BLKC_RequestManager.h"
#include "BLKC_MessageHandlerBase.h"

class BLKC_MessageHandlerBase;
typedef std::vector<BLKC_MessageHandlerBase*> MESSAGE_HANDLER_ARRY;

class BLKC_RequestManager;

class BLKC_MessageReceiver
{
    public:
        enum E_RECEIVE_RESULT{
			SUCCESS,
			TIME_OUT,
			SOCKET_ERR,
			INVALID_DATA
		};

    public:
        BLKC_MessageReceiver(int sock_fd, BLKC_RequestManager* pRequestManager, pid_t peerSys_pid = 0, pid_t peerSys_tid = 0);
        BLKC_MessageReceiver(int sock_fd);
        virtual ~BLKC_MessageReceiver();
        void exit();
        MESSAGE_HANDLER_ARRY* getMessages();
        enum E_RECEIVE_RESULT receiveLargeRetVal(SEQUENS_ID_T sequense_id, LARGE_RET_VAL_ARRY* ret_arry);
        BLKC_MessageHandlerBase* newMessage(BLKS_MSG_FORMAT* msg);
        void registHealthCheckHandler(BLKC_MessageHandlerBase* handler);
		void registRequestHandler(BLKC_MessageHandlerBase* handler);
		void registCallBackHandler(BLKC_MessageHandlerBase* handler);
		void registObserverNotifyHandler(BLKC_MessageHandlerBase* handler);
		void registTimeOutHandler(BLKC_MessageHandlerBase* handler);
		void registErrorHandler(BLKC_MessageHandlerBase* handler);

    public:
        BLKC_RequestManager* mRequestManager;
		typedef unsigned char RECEIVE_BUFFER_T;
    
    private:
        enum E_RECEIVE_RESULT receiveDataFromSocket(MESSAGE_SIZE_T size, unsigned char* buffer);
        enum E_RECEIVE_RESULT waitReceiveSocket();
        int getEpollMsec(struct timeval *timeout, struct timespec (&elapsed)[2]);
		void calcEpollElapsed(int nfds, struct timeval *timeout, struct timespec (&elapsed)[2]);
        MESSAGE_HANDLER_ARRY* setNotSuccessHandler(enum E_RECEIVE_RESULT result);
    
    private:
        int mSockFd;
        int mEpollFd;
        bool mEnableTimeOut;
        bool mRunning;
        int mErrorNo;
        struct timeval mTimeOutSetting;
        pid_t mPeerSys_pid;
		pid_t mPeerSys_tid;

        BLKC_MessageHandlerBase* mHealthCheckHandler;
		BLKC_MessageHandlerBase* mRequestHandler;
		BLKC_MessageHandlerBase* mCallBackHandler;
		BLKC_MessageHandlerBase* mObserverNotifyHandler;
		BLKC_MessageHandlerBase* mErrorHandler;
		BLKC_MessageHandlerBase* mTimeOutHandler;

        MESSAGE_HANDLER_ARRY mMessageArry;
};

#endif