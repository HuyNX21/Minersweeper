#include "pch.h"
#include "BLKC_MessageReceiver.h"

BLKC_MessageReceiver::BLKC_MessageReceiver(int sock_fd, BLKC_RequestManager* pRequestManager, pid_t peerSys_pid, pid_t peerSys_tid)
{
    mSockFd = sock_fd;
	mEnableTimeOut = false;

    BLKD_EINTR_RETRY_CALL3(	mEpollFd = epoll_create1(EPOLL_CLOEXEC),
							mEpollFd == -1,
							LOG_ERROR("error epoll_create1") );

    if(mEpollFd != -1) {
		int ret = 0;
		struct epoll_event event = {(EPOLLIN | EPOLLRDHUP), reinterpret_cast<void*>(mSockFd)};
		BLKD_EINTR_RETRY_CALL3(	ret = epoll_ctl(mEpollFd, EPOLL_CTL_ADD, mSockFd, &event),
								ret == -1,
								LOG_ERROR("error epoll_ctl") );
	}

	mPeerSys_pid = peerSys_pid;
	mPeerSys_tid = peerSys_tid;
	
	mHealthCheckHandler = new BLKC_MessageHandlerBase;
	mRequestHandler = new BLKC_MessageHandlerBase;
	mCallBackHandler = new BLKC_MessageHandlerBase;
	mObserverNotifyHandler = new BLKC_MessageHandlerBase;
	mErrorHandler = new BLKC_MessageHandlerBase;
	mTimeOutHandler = new BLKC_MessageHandlerBase;

	mErrorNo = 0;
	mRequestManager = pRequestManager;

	memset( &mTimeOutSetting, 0, sizeof( struct timeval ) );

	mRunning = true;
}

BLKC_MessageReceiver::~BLKC_MessageReceiver()
{
    if( mEpollFd != -1 ){
		int ret = 0;
		BLKD_EINTR_RETRY_CALL(ret = close(mEpollFd), ret == -1);
		mEpollFd = -1;
	}

	delete mHealthCheckHandler;
	delete mRequestHandler;
	delete mCallBackHandler;
	delete mObserverNotifyHandler;
	delete mErrorHandler;
	delete mTimeOutHandler;
}

void BLKC_MessageReceiver::exit()
{
	mRunning = false;
}

MESSAGE_HANDLER_ARRY* BLKC_MessageReceiver::getMessages()
{
    mMessageArry.clear();

    enum E_RECEIVE_RESULT result = SUCCESS;

    BLKS_MSGHEAD rcv_msg_header;
	BLKS_MSG_FORMAT* rcv_msg = NULL;
	RECEIVE_BUFFER_T* rcv_msg_alloc = NULL;

	LOG_DEBUG("receive data head from socket");
    result = receiveDataFromSocket(BLKD_MSGHEAD_SIZE, (unsigned char*)&(rcv_msg_header));
	
    if( result != SUCCESS ){
		LOG_ERROR("socket error - setNotSuccessHandler - result : %d", result);
		return setNotSuccessHandler( result );
	}
    SEQUENS_ID_T sequenceId_kind = rcv_msg_header.sequenceId & SEQUENSE_ID_KIND_MASK;

    BLKC_RequestManager::BLKS_SynchronizedRequestParam sRequestParam;
	memset(&sRequestParam,0,sizeof(sRequestParam));

	if(mRequestManager != NULL) {
		mRequestManager->getSynchronizedRequestParam(rcv_msg_header.sequenceId, &sRequestParam);
	}

	if(sRequestParam.buffer != NULL) {
		rcv_msg = (BLKS_MSG_FORMAT*)(sRequestParam.buffer - sizeof(BLKS_MSGHEAD));
	}else {
		rcv_msg = new BLKS_MSG_FORMAT;
	}

	rcv_msg->header = rcv_msg_header;

	LOG_DEBUG("receive data payload from socket");
	result = receiveDataFromSocket( rcv_msg->header.msgSize - BLKD_MSGHEAD_SIZE, rcv_msg->payload );

	if( result != SUCCESS ){
		delete [] rcv_msg_alloc;
		LOG_DEBUG("setNotSuccessHandler");
		return setNotSuccessHandler( result );
	}

	if(sRequestParam.buffer != NULL) {
		if(sRequestParam.ret_arry != NULL) {
			result = receiveLargeRetVal(SEQUENSE_ID_SYNC_REQ_LARGE_RETVAL,sRequestParam.ret_arry);
			if( result != SUCCESS ){
				delete [] rcv_msg_alloc;
				LOG_DEBUG("setNotSuccessHandler");
				return setNotSuccessHandler( result );
			}
		}
	}

	mMessageArry.push_back( newMessage( rcv_msg ));

	return &mMessageArry;
}

enum BLKC_MessageReceiver::E_RECEIVE_RESULT BLKC_MessageReceiver::receiveDataFromSocket(MESSAGE_SIZE_T size, unsigned char* buffer)
{
    MESSAGE_SIZE_T received_size = 0;
	enum E_RECEIVE_RESULT select_result = SUCCESS;
	ssize_t rcvsize = 0;

	if( ( size == 0 ) || ( buffer == NULL ) ){
		LOG_INFO("size: %d - buffer: %s", size, ( buffer == NULL ) ? "null" : "notnull");
		return SUCCESS;
	}

    do{
        select_result = waitReceiveSocket();
        if(select_result != SUCCESS){
			return select_result;
		}
    RETRY:
        rcvsize = recv(mSockFd, buffer + received_size, size - received_size, MSG_NOSIGNAL );

        if( rcvsize == 0 ){
            return SOCKET_ERR;
		}else if( rcvsize < 0 ){
            if( errno == EINTR ){
				goto RETRY;
			}else{
				return SOCKET_ERR;
			}
        }else{
			received_size += (MESSAGE_SIZE_T)rcvsize;
		}
        
    }while( received_size < size );

    return SUCCESS;
}

enum BLKC_MessageReceiver::E_RECEIVE_RESULT BLKC_MessageReceiver::waitReceiveSocket()
{
    int sfd;
    struct epoll_event events[1];
	struct timespec elapsed[2];
    struct timeval  tm_out_setting;
	struct timeval* tm_out = NULL;

	if(mEnableTimeOut == true){
		tm_out = &tm_out_setting;
	}

	enum E_RECEIVE_RESULT result = SUCCESS;

    while(mRunning == true)
    {
        tm_out_setting = mTimeOutSetting;
    
    RETRY:
		// mEpollFd la fd cua epoll instance, dung de giam sat fd
        sfd = epoll_wait(mEpollFd, events, sizeof(events)/sizeof(events[0]), getEpollMsec(tm_out, elapsed));
		calcEpollElapsed(sfd, tm_out, elapsed);
        if (sfd == -1){
			if( errno == EINTR ){
				goto RETRY;
            }
			result = SOCKET_ERR;
			break;
		}
        if(sfd == 0){
			result = TIME_OUT;
			break;
		}
        if(mSockFd != events[0].data.fd){
			continue;
		}
		// mSockFd la fd cua socket thuc su
		// Neu dung la fd cua mSockFd thi moi dung lai
		// Phong truong hop epoll dang giam sat nhieu fd
		break;
    }

    return result;
}

int BLKC_MessageReceiver::getEpollMsec(struct timeval *timeout, struct timespec (&elapsed)[2])
{
	int msec = -1;
	if( NULL != timeout ){
		msec = (int)((timeout->tv_sec * 1000) + (timeout->tv_usec / 1000));
		clock_gettime(CLOCK_MONOTONIC, &elapsed[0]);
	}
	return msec;
}

void BLKC_MessageReceiver::calcEpollElapsed(int nfds, struct timeval *timeout, struct timespec (&elapsed)[2])
{
	if( NULL == timeout ){
		return;
	}

	if( nfds != 0 ){
		int lasterrno = errno;
		clock_gettime(CLOCK_MONOTONIC, &elapsed[1]);
		errno = lasterrno;

		elapsed[1].tv_sec -= elapsed[0].tv_sec;
		elapsed[1].tv_nsec -= elapsed[0].tv_nsec;
		if( elapsed[1].tv_nsec < 0 ){
			elapsed[1].tv_nsec += 1000000000;
			elapsed[1].tv_sec -= 1;
		}

		timeout->tv_sec -= elapsed[1].tv_sec;
		timeout->tv_usec -= elapsed[1].tv_nsec / 1000;
		if( timeout->tv_usec < 0 ){
			timeout->tv_usec += 1000000;
			timeout->tv_sec -= 1;
		}
		if( timeout->tv_sec < 0 ){
			timeout->tv_sec = 0;
			timeout->tv_usec = 0;
		}
	}else{
		timeout->tv_sec = 0;
		timeout->tv_usec = 0;
	}
}

MESSAGE_HANDLER_ARRY* BLKC_MessageReceiver::setNotSuccessHandler(enum E_RECEIVE_RESULT result)
{
	BLKC_MessageHandlerBase* handler;

	switch( result ){
		case TIME_OUT:
			handler = mTimeOutHandler->clone();
			break;
		case SOCKET_ERR:
		default:
			handler = mErrorHandler->clone();
			break;
	}
	mMessageArry.push_back( handler );
	return &mMessageArry;
}

enum BLKC_MessageReceiver::E_RECEIVE_RESULT BLKC_MessageReceiver::receiveLargeRetVal(SEQUENS_ID_T sequense_id, LARGE_RET_VAL_ARRY* mRetValArry)
{
	BLKS_MSGHEAD rcv_msg_header;
	memset(&rcv_msg_header,0,sizeof(BLKS_MSGHEAD));

	enum E_RECEIVE_RESULT result = SUCCESS;
	
	if( mRetValArry == NULL ){
		return result;
	}

	LARGE_RET_VAL_ARRY::iterator it     = mRetValArry->begin();
	LARGE_RET_VAL_ARRY::iterator it_end = mRetValArry->end();

	for(;it != it_end;it++){
		result = receiveDataFromSocket( BLKD_MSGHEAD_SIZE, (unsigned char*)&rcv_msg_header);
		if( result != SUCCESS ){
			return result;
		}

		if( ( rcv_msg_header.sequenceId & SEQUENSE_ID_KIND_MASK ) != sequense_id ){
			return INVALID_DATA;
		}

		if( 0 == (rcv_msg_header.msgSize - BLKD_MSGHEAD_SIZE)){
			continue;
		}

		if((*it)->destination != NULL){
			result = receiveDataFromSocket( rcv_msg_header.msgSize - BLKD_MSGHEAD_SIZE, (unsigned char*)(*it)->destination );
			if( result != SUCCESS ){
				return result;
			}
		}
	}
	
	return result;
}

BLKC_MessageHandlerBase* BLKC_MessageReceiver::newMessage(BLKS_MSG_FORMAT* msg)
{
	BLKC_MessageHandlerBase* ret;

	switch(msg->header.sequenceId & SEQUENSE_ID_KIND_MASK){
		case SEQUENSE_ID_HELTH_CHECK:     
			ret = mHealthCheckHandler->clone();
			break;
		case SEQUENSE_ID_SYNC_REQUEST:
		case SEQUENSE_ID_SYNC_REQ_WITH_LARGE_RETVAL:
		case SEQUENSE_ID_SYNC_REQ_LARGE_PARAM:
		case SEQUENSE_ID_SYNC_REQ_LARGE_PARAM_RETVAL:
		case SEQUENSE_ID_SYNC_REQ_JOBSPEC_DEL:
			ret = mRequestHandler->clone();
			break;
		case SEQUENSE_ID_CALL_BACK:
		case SEQUENSE_ID_CALL_BACK_LARGE_PARAM:
		case SEQUENSE_ID_CALL_BACK_NOWAIT:
		case SEQUENSE_ID_CALL_BACK_LARGEPRM_NOWAIT:
			ret = mCallBackHandler->clone();
			break;
		case SEQUENSE_ID_OBSERVER_NOTIFY: 
		case SEQUENSE_ID_OBSERVER_NOTIFY_LARGE_PARAM:
		case SEQUENSE_ID_OBSERVER_NOWAIT: 
		case SEQUENSE_ID_OBSERVER_LARGEPRM_NOAWIT: 
		case SEQUENSE_ID_SYNC_REQ_JOBSPEC_DEL_SRV:
			ret = mObserverNotifyHandler->clone();
			break;
		default:
			ret = new BLKC_MessageHandlerBase;
			break;
	}

	ret->setMessage(msg->header.sequenceId, msg->payload, msg->header.msgSize - BLKD_MSGHEAD_SIZE);
	
	return ret;
}

void BLKC_MessageReceiver::registHealthCheckHandler(BLKC_MessageHandlerBase* handler)
{
	delete mHealthCheckHandler;
	mHealthCheckHandler = handler;
}

void BLKC_MessageReceiver::registRequestHandler(BLKC_MessageHandlerBase* handler)
{
	delete mRequestHandler;
	mRequestHandler = handler;
}

void BLKC_MessageReceiver::registCallBackHandler(BLKC_MessageHandlerBase* handler)
{
	delete mCallBackHandler;
	mCallBackHandler = handler;
}

void BLKC_MessageReceiver::registObserverNotifyHandler(BLKC_MessageHandlerBase* handler)
{
	delete mObserverNotifyHandler;
	mObserverNotifyHandler = handler;
}


void BLKC_MessageReceiver::registErrorHandler(BLKC_MessageHandlerBase* handler)
{
	delete mErrorHandler;
	mErrorHandler = handler;
}

void BLKC_MessageReceiver::registTimeOutHandler(BLKC_MessageHandlerBase* handler)
{
	delete mTimeOutHandler;
	mTimeOutHandler = handler;
}