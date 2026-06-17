#include "pch.h"
#include "BLKC_ConnectManager.h"
#include "unmarsahling.h"
#include "BLKC_IdAndObjectContainer.h"
#include "BLKC_StubManager.h"

CallBackContainer BLKC_ConnectManager::mCallBackContainer;
ThreadSafeMap<uint32_t, MutexLock*> BLKC_ConnectManager::mInstanceMutexList(MutexLock::MUTEX_RECURSIVE_NP);
BLKC_IdAndObjectContainer<void> BLKC_ConnectManager::mInstanceIdAndObjectContainer;

BLKC_ConnectManager::BLKC_ConnectManager(int sfd, BLKS_SOCKET_CONTROLDATA *data)
{

	for( BLKD_SOCKID sockid = 0; sockid < BLKD_SOCKID_MAX; sockid++ ){
		connectFD[sockid] = -1;
		
		mRecvThreadRunning[sockid] = false;
		mIsRecvThreadEnd[sockid] = false;
		mIsSocketConnected[sockid] = false;
		
		mReceiveProcessor[sockid] = NULL;
		mReceiveThread[sockid] = NULL;
		mMessageReceiver[sockid] = NULL;
	}

	mCallBackSequenseIdCounter = 0;
	mObservableSequenseIdCounter = 0;

    BLKD_EINTR_RETRY_CALL3(	mEpollFd = epoll_create1(EPOLL_CLOEXEC),
							mEpollFd == -1,
							LOG_ERROR("error epoll_create1\n") );
    
    init(sfd, data->sockid);

	mStubRequestManager = new BLKC_StubRequestManager(*this, data->sys_tid);
	mObserverIdAndObjectContainer = ThreadSafeSingleton<ObserverIdAndObjectContainer>::getInstance();
	mDeleteInstanceManager = new BLKC_DeleteInstanceManager();

	mIsKillProcessor = false;
	mPeerSys_pid = data->sys_pid;
	mPeerSys_tid = data->sys_tid;
	mPeerPriority = data->priority;
	mReceiveControl = 0;

	mConnectionId = 0;
}

BLKC_ConnectManager::~BLKC_ConnectManager()
{
	BLKD_SOCKID sockid;

	int ret = 0;

	for( sockid = 0; sockid < BLKD_SOCKID_MAX; sockid++ ) {
		mReceiveControl->setRxControl(connectFD[sockid],BLKD_RXCTRL_END);

		mIsSocketConnected[sockid] = false;

		if ( mMessageReceiver[sockid] != NULL ) {
			mMessageReceiver[sockid]->exit();

			if(mIsRecvThreadEnd[sockid] == false) {
				mReceiveProcessor[sockid]->post(-1);
			}

			while(mIsRecvThreadEnd[sockid] == false){
				Thread::nanosleepThread(0, 100*1000);	// 100ms wait
			}

			delete mMessageReceiver[sockid];
			mMessageReceiver[sockid] = NULL;
		}

		if( (mEpollFd != -1) && (connectFD[sockid] != -1) ){
			BLKD_EINTR_RETRY_CALL3(	ret = epoll_ctl(mEpollFd, EPOLL_CTL_DEL, connectFD[sockid], NULL),
									ret == -1,
									printf("epoll_ctl: errno[%d]\n", errno) );
		}

		shutdown( connectFD[sockid], SHUT_RDWR );
	}

	if( mEpollFd != -1 ){
		BLKD_EINTR_RETRY_CALL(ret = close(mEpollFd), ret == -1);
		mEpollFd = -1;
	}

	BLKC_ReceiveControl::exitAndDeleteInstance(mPeerSys_pid, connectFD);
	mReceiveControl = NULL;

	for( sockid = 0; sockid < BLKD_SOCKID_MAX; sockid++ ) {
		close(connectFD[sockid]);
		connectFD[sockid] = -1;
	}

	mCallBackContainer.eraseSession( mConnectionId );

	mObserverIdAndObjectContainer->deleteAllObject( mConnectionId );

	if ( NULL != mStubRequestManager ) {
		delete mStubRequestManager;
		mStubRequestManager = NULL;
	}

	if ( NULL != mDeleteInstanceManager ) {
		mDeleteInstanceManager->destoryAllInstance();
		delete mDeleteInstanceManager;
		mDeleteInstanceManager = NULL;
	}
}

BLKC_ConnectManager::ReceiveProcessor::ReceiveProcessor()
{
	mConnectionId = 0;
	mConnectManager = NULL;
	mSockId = BLKD_SOCKID_INVALID;
}

BLKC_ConnectManager::ReceiveProcessor::~ReceiveProcessor()
{
}

BLKC_ConnectManager::ReceiveProcessorTemporary::ReceiveProcessorTemporary()
{
	mManager = 0;
	mSockId = BLKD_SOCKID_INVALID;
}
BLKC_ConnectManager::ReceiveProcessorTemporary::~ReceiveProcessorTemporary()
{
}

void BLKC_ConnectManager::init( int sfd, BLKD_SOCKID sockid )
{
	connectFD[sockid] = sfd;

	int ret = 0;
	struct epoll_event event = {0, reinterpret_cast<void*>(sfd)};
	BLKD_EINTR_RETRY_CALL3(	ret = epoll_ctl(mEpollFd, EPOLL_CTL_ADD, sfd, &event),
							ret == -1,
							LOG_ERROR("error epoll_ctl\n") );

	mRecvThreadRunning[sockid] = true;
	mIsSocketConnected[sockid] = true;
}

bool BLKC_ConnectManager::matchPeerSysId(BLKS_SOCKET_CONTROLDATA *data)
{
	return (data->sys_pid == mPeerSys_pid) && (data->sys_tid == mPeerSys_tid);
}

void BLKC_ConnectManager::start( int connectionId, BLKD_SOCKID sockid )
{
    if(BLKD_SOCKID_SYNC == sockid){
		{
			ScopeLock lock( mInstanceMutexList.mutex() );
			mInstanceMutexList.insert( connectionId, &mInstanceMutex );
		}
		mConnectionId = connectionId;
	}

	mMessageReceiver[sockid] = new BLKC_MessageReceiver( connectFD[sockid], mStubRequestManager, mPeerSys_pid, mPeerSys_tid );
	mMessageReceiver[sockid]->registHealthCheckHandler(new BLKC_StubHelthCheckMessageHandler(*this));
	mMessageReceiver[sockid]->registRequestHandler(new BLKC_StubRequestMessageHandler(*this));
	mMessageReceiver[sockid]->registCallBackHandler(new BLKC_StubCallBackMessageHandler(*this));
	mMessageReceiver[sockid]->registObserverNotifyHandler(new BLKC_StubOseverNotifyMessageHandler(*this));
	mMessageReceiver[sockid]->registErrorHandler(new BLKC_StubErrorMessageHandler(*this));
	mMessageReceiver[sockid]->registTimeOutHandler(new BLKC_StubTimeOutHandler(*this));

	mReceiveProcessor[sockid] = new ReceiveProcessor();
	mReceiveProcessor[sockid]->setParam(this, connectionId, sockid);

	if (BLKD_SOCKID_SYNC == sockid) {
		mReceiveThread[sockid] = new Thread(mReceiveProcessor[sockid], "SrvSessionTh", DEF_STUB_THREAD_PRIO_SRVS_TH);
	} else {
		mReceiveThread[sockid] = new Thread(mReceiveProcessor[sockid], "SrvSessionThAs", DEF_STUB_THREAD_PRIO_SRVS_THAS);
	}

	mReceiveThread[sockid]->setStackSize(DEF_STACK_SIZE_SRVSESSIONTH);

	mReceiveThread[sockid]->run();

	mReceiveControl = BLKC_ReceiveControl::newInstance(mPeerSys_pid,connectFD[sockid],this, false);

	mReceiveControl->addReceiveThreadInfo(mReceiveThread[sockid]->getThreadId(),
								BLKC_ReceiveControl::STATE_IDLE,
								((BLKD_SOCKID_SYNC == sockid) ? BLKC_ReceiveControl::MODE_RECEIVE : BLKC_ReceiveControl::MODE_RECEIVEASYNC),
								this,mReceiveProcessor[sockid],connectFD[sockid]);

	mReceiveControl->setRxControl(connectFD[sockid], BLKD_RXCTRL_START);
}

void BLKC_ConnectManager::ReceiveProcessor::setParam(BLKC_ConnectManager* connect_manager, int connectionId, BLKD_SOCKID sockid) // 2018/06/20 APF E101??¿½?¿½??¿½?¿½??¿½?¿½Î‰ï¿½.
{
	mConnectionId = connectionId;
	mConnectManager = connect_manager;
	mSockId = sockid;
}

void BLKC_ConnectManager::ReceiveProcessor::run()
{
	mConnectManager->srvRcv_Main( mConnectionId, mSockId );	

}

void BLKC_ConnectManager::NotifyReceiveControl(Runnable* processor, BLKD_SOCKID sockid)
{
	ReceiveProcessor* pProcessor = reinterpret_cast<ReceiveProcessor*>(processor);
	if(processor != NULL) {
		pProcessor->post(connectFD[sockid]);
	} else {
		executeRecv( sockid );
	}
}

void BLKC_ConnectManager::executeRecv( BLKD_SOCKID sockid )
{
	ReceiveProcessorTemporary* pProcessor = new ReceiveProcessorTemporary;

	pProcessor->setParam(this, sockid);

	Thread* pThread = new Thread(pProcessor, "SrvSessionThTmp", DEF_STUB_THREAD_PRIO_SRVS_THTMP);

	pThread->setStackSize(DEF_STACK_SIZE_SRVSESSIONTH);

	pThread->run();	

	mReceiveControl->addReceiveThreadInfo(pThread->getThreadId(),
								BLKC_ReceiveControl::STATE_EXEC,
								BLKC_ReceiveControl::MODE_RECEIVETEMPORARY,
								this,pProcessor,connectFD[BLKD_SOCKID_ASYNC]);
}

void BLKC_ConnectManager::ReceiveProcessorTemporary::run()
{
	mManager->Recv_ConnectMgr_Temporary();
}

void BLKC_ConnectManager::Recv_ConnectMgr_Temporary()
{
	BLKC_StubReceiveThreadContext context;

	context.mPeerSysTid = mPeerSys_tid;

	messageReceive(&context, BLKD_SOCKID_ASYNC);

	mReceiveControl->deleteReceiveThreadInfo(pthread_self());

	mReceiveControl->setRxControl(connectFD[BLKD_SOCKID_ASYNC],BLKD_RXCTRL_UPDATE);
}

void BLKC_ConnectManager::ReceiveProcessorTemporary::setParam(BLKC_ConnectManager *manager, BLKD_SOCKID sockid)
{
	mManager = manager;
	mSockId = sockid;
}

void BLKC_ConnectManager::srvRcv_Main(int connectionId, BLKD_SOCKID sockid)
{
	int sockfd = connectFD[sockid];

	if (sockfd == -1){
		notifyConnectError();
		mIsRecvThreadEnd[sockid] = true;
		return;
	}

	int sfd = -1;
	BLKC_StubReceiveThreadContext context;
	context.mPeerSysTid = mPeerSys_tid;

	while(1){
		mReceiveProcessor[sockid]->wait(&sfd);

		messageReceive(&context, sockid);

		mReceiveControl->changeState(pthread_self(),BLKC_ReceiveControl::STATE_IDLE);

		mReceiveControl->setRxControl(sfd,BLKD_RXCTRL_UPDATE);
	}

	mReceiveControl->deleteReceiveThreadInfo(pthread_self());

	mReceiveControl->setRxControl(connectFD[sockid],BLKD_RXCTRL_UPDATE);

	mIsRecvThreadEnd[sockid] = true;
}

void BLKC_ConnectManager::messageReceive(BLKC_ReceiveThreadContext* context, BLKD_SOCKID sockid)
{
	shm_mutex.lockWait();

	MESSAGE_HANDLER_ARRY* handlers = mMessageReceiver[sockid]->getMessages();
	MESSAGE_HANDLER_ARRY c_handler(*handlers);

	shm_mutex.unlock();

	handlers = &c_handler;
	if(handlers->empty() == false){
		MESSAGE_HANDLER_ARRY::iterator it = handlers->begin();
		MESSAGE_HANDLER_ARRY::iterator it_end = handlers->end();
		for(;it != it_end;it++){
			(*it)->exec( context );
			delete *it;
		}
	}
}

void BLKC_ConnectManager::ReceiveProcessor::wait(int* fd)
{
	LOG_DEBUG("Semaphore stub receive wait");
	mOperationSemaphore.wait();
	LOG_DEBUG("Semaphore stub receive release");
	mOperationMutex.lockWait();
	*fd = mOperationList.front();
	mOperationList.pop_front();
	mOperationMutex.unlock();
}

void BLKC_ConnectManager::ReceiveProcessor::post(int fd)
{
	mOperationMutex.lockWait();
	if( fd == -1 ){
		mOperationList.push_front(fd);
	}else{
		mOperationList.push_back(fd);
	}
	mOperationMutex.unlock();

	mOperationSemaphore.post();
	LOG_DEBUG("Semaphore stub receive post");
}

MutexLock* BLKC_ConnectManager::getConnectManagerInstanceMutex(uint32_t session_id)
{
	ScopeLock( mInstanceMutexList.mutex() );
	
	std::map<uint32_t, MutexLock*>::iterator it = mInstanceMutexList.reference().find( session_id );
	std::map<uint32_t, MutexLock*>::iterator it_end = mInstanceMutexList.reference().end();
	
	if(it == it_end){
		return NULL;
	}else{
		return( (*it).second );
	}
}

void  BLKC_ConnectManager::releaseBuffer(unsigned char *buf)
{
	unsigned char* release_address = buf - offsetof(BLKS_MSG_FORMAT, payload);
	delete release_address;
}

int BLKC_ConnectManager::sendReqData( SEQUENS_ID_T seqId, unsigned char* sendbuf, MESSAGE_SIZE_T sendsize, LARGE_PARAM_ARRY* param_arry)
{
	BLKD_SOCKID sockid = BLKD_SOCKID_ASYNC;
	ScopeLock lock( mSocketMutexLock );

	int ret = sendMessage( seqId, sendbuf, sendsize, sockid, true );

	if( ret == -1 ){
		return ret;
	}

	if( param_arry == NULL ){
		return ret;
	}

	LARGE_PARAM_ARRY::iterator it = param_arry->begin();
	LARGE_PARAM_ARRY::iterator it_end = param_arry->end();
	
	BLKS_MSGHEAD msg_header;
	int socket_fd = connectFD[sockid];

	msg_header.sequenceId = seqId & SEQUENSE_ID_KIND_MASK;
	for( ; it != it_end ; it++ ){
		if( (*it)->destination == NULL ){
			(*it)->size = 0;
		}
		msg_header.msgSize = (*it)->size + BLKD_MSGHEAD_SIZE;

		ret = sendSocket( socket_fd, (unsigned char*)&msg_header, BLKD_MSGHEAD_SIZE, true );
		if (-1 == ret){
			return ret;
		}

		ret = sendSocket( socket_fd, (unsigned char*)(*it)->destination, (*it)->size, true );
		if (-1 == ret){
			return ret;
		}
	}
	return ret;
}

int BLKC_ConnectManager::sendMessage( SEQUENS_ID_T seqId, unsigned char* buf, MESSAGE_SIZE_T len, BLKD_SOCKID sockid, bool sendReqData )
{
	unsigned char *sendbuf = buf - BLKD_MSGHEAD_SIZE;
	BLKS_MSGHEAD* msgheader_p = (BLKS_MSGHEAD*)sendbuf;
	MESSAGE_SIZE_T send_len = len + BLKD_MSGHEAD_SIZE;

	msgheader_p->sequenceId = seqId;
	msgheader_p->msgSize = send_len;

	int ret = sendSocket( connectFD[sockid], sendbuf, msgheader_p->msgSize, sendReqData);

	if(ret == -1){
	}

	return ret;
}

int BLKC_ConnectManager::sendSocket(int sock_fd, unsigned char *buf, MESSAGE_SIZE_T size, bool sendReqData)
{
	#define SENDSOCKET_EXCEPTION_LOG_MAX 100
	static unsigned int ui_sendSocket_exceptionlog_cnt = 0;
	if( ( size == 0 ) || ( buf == NULL ) ){
		if ( ui_sendSocket_exceptionlog_cnt < SENDSOCKET_EXCEPTION_LOG_MAX ) {
			LOG_ERROR("BLKC_ConnectManager::sendSocket para check NG: size[%u]buf[%p]\n", size, buf);
			ui_sendSocket_exceptionlog_cnt++;
		}
		return 0;
	}

	int ret = -1;
	int retryCnt = 0;

	MESSAGE_SIZE_T sendedsize = 0;
	int epret = 0;
	struct epoll_event events[1];
	events[0].events = (EPOLLOUT | EPOLLRDHUP);
	events[0].data.fd = sock_fd;
	BLKD_EINTR_RETRY_CALL3(	epret = epoll_ctl(mEpollFd, EPOLL_CTL_MOD, sock_fd, &events[0]),
							epret == -1,
							LOG_ERROR("error epoll_ctl");
							return (true == sendReqData) ? -1 : 0 );

	while(1)
	{
		ret = epoll_wait(mEpollFd, events, sizeof(events)/sizeof(events[0]), -1);

		if (ret == -1){
			if( errno == EINTR ){
				continue;
			}
			LOG_ERROR("error epoll_wait");
			break;
		}

		if(sock_fd != events[0].data.fd){
			continue;
		}

		ret = (int)send(sock_fd, buf + sendedsize, size - sendedsize, MSG_NOSIGNAL );

		if (ret < 0)
		{
			if (errno != EAGAIN)
			{
				if (retryCnt < BLKD_MAX_RETRY_NUM)
				{
					retryCnt++;
					continue;
				}
			}
			ret = -1;
			if ( ui_sendSocket_exceptionlog_cnt < SENDSOCKET_EXCEPTION_LOG_MAX ) {
				LOG_ERROR("BLKC_ConnectManager::sendSocket send failed after retry[%d]times,bort: sock_fd[%u]ret[%d]sendedsize[%d]errno[%d]\n",retryCnt,sock_fd,ret,sendedsize,errno);
				ui_sendSocket_exceptionlog_cnt++;
			}
			break;
		}
		
		if ((sendedsize += ret) >= size)
		{
			break;
		}
	}

	events[0].events = 0;
	events[0].data.fd = sock_fd;
	BLKD_EINTR_RETRY_CALL3(	epret = epoll_ctl(mEpollFd, EPOLL_CTL_MOD, sock_fd, &events[0]),
							epret == -1,
							LOG_ERROR("error epoll_ctl\n"); );

	if(ret == -1){
	}
	
	return ret;
}

void BLKC_ConnectManager::dispatchDo( SEQUENS_ID_T seqId, uint32_t dispatch_msgsize, unsigned char* dispatch_buf, BLKC_ReceiveThreadContext* context)
{
	BLKD_SOCKID sockid = mReceiveControl->getSockId();
	
	mReceiveControl->setSequenceId(seqId);

	BLKS_COMMONID common_Id;

	unsigned char *pt;

	pt = (unsigned char *)dispatch_buf;
	pt = (unsigned char *)unmarshal_ClassMethodID( pt, &common_Id.ClassMethodID );
	pt = (unsigned char *)unmarshal_InstanceID( pt, &common_Id.InstanceID );
	pt = (unsigned char *)unmarshal_unsigned_int32_t( pt, &common_Id.SessionID );

	common_Id.SessionID = mConnectionId;

	SEQUENS_ID_T seqId_kind = seqId & SEQUENSE_ID_KIND_MASK;
	if( !( (seqId_kind == SEQUENSE_ID_SYNC_REQ_LARGE_PARAM)
	|| (seqId_kind == SEQUENSE_ID_SYNC_REQ_LARGE_PARAM_RETVAL) ) ) {

		mReceiveControl->setRxControl(connectFD[sockid], BLKD_RXCTRL_START);
	}

	BLKC_ConnectManager::Stub_APIC_Call( &common_Id, dispatch_buf, context );

	releaseBuffer(dispatch_buf);
	return;
}

int BLKC_ConnectManager::sendRply(unsigned char* sendbuf, MESSAGE_SIZE_T sendsize)
{
	SEQUENS_ID_T seqId = mReceiveControl->getSequenceId();
	BLKD_SOCKID sockid = mReceiveControl->getSockId();

	ScopeLock lock( mSocketMutexLock );
	int ret = sendMessage( seqId, sendbuf, sendsize, sockid );

	if(ret == -1){
		LOG_ERROR("Error \n");
	}

	return ret;
}

void BLKC_ConnectManager::notifyReplyMessage(SEQUENS_ID_T seqnsId, unsigned char* buffer, MESSAGE_SIZE_T length )
{
	// Callback/Observer

	mStubRequestManager->notifyReplyMessage(seqnsId, buffer, length);

	mReceiveControl->setRxControl(connectFD[BLKD_SOCKID_ASYNC], BLKD_RXCTRL_START);
}

void BLKC_ConnectManager::notifyConnectError()
{
	mStubRequestManager->releaseSyncWaitState();

	InstanceScopeLock lock( (getConnectManagerInstanceMutex( mConnectionId )) );

	BLKD_SOCKID sockid = mReceiveControl->getSockId();

	if(mIsSocketConnected[sockid] == false){
		return;
	}
	mIsSocketConnected[sockid] = false;

	BLKC_StubManager::getInstance()->NotifyConnectManagerError( mConnectionId, sockid );

	mRecvThreadRunning[sockid] = false;

	mReceiveControl->setRxControl(connectFD[sockid],BLKD_RXCTRL_END);
}

int BLKC_ConnectManager::sendHelthCheck()
{
	printf("call %s \n", __FUNC_NAME__);
}

void* BLKC_ConnectManager::getObjectPt( uint32_t InstanceID )
{

	return mInstanceIdAndObjectContainer.findObject( InstanceID );
}

uint32_t BLKC_ConnectManager::findInstanceId(uint32_t session_id, void *obj)
{
	return BLKC_ConnectManager::findInstanceId( obj );
}

uint32_t BLKC_ConnectManager::findInstanceId(void *obj)
{

	return mInstanceIdAndObjectContainer.findId( obj );
}

uint32_t BLKC_ConnectManager::getNewInstanceID(uint32_t session_id, void *instance)
{
	return BLKC_ConnectManager::getNewInstanceID( instance );
}

uint32_t BLKC_ConnectManager::getNewInstanceID(void *instance)
{
	if( instance == NULL ) return 0;

	uint32_t ret =  mInstanceIdAndObjectContainer.resistObject( instance );

	return ret;
}

void BLKC_ConnectManager::deleteInstanceId(uint32_t instanceId)
{
	mInstanceIdAndObjectContainer.unregistObject( instanceId );
}

CallBackContainer& BLKC_ConnectManager::getCallBackContainer()
{
	return mCallBackContainer;
}

bool BLKC_ConnectManager::isSocketConnected(BLKD_SOCKID sockid)
{
	if (sockid < 0 || BLKD_SOCKID_MAX <= sockid) {
		return false;
	}
	return mIsSocketConnected[sockid];
}

SEQUENS_ID_T BLKC_ConnectManager::getCallBackSequenceId()
{
	ScopeLock lock( mCallBackSqnsIdMutex );
	
	++mCallBackSequenseIdCounter;
	mCallBackSequenseIdCounter &= ~SEQUENSE_ID_KIND_MASK;
	return mCallBackSequenseIdCounter; 
}

SEQUENS_ID_T BLKC_ConnectManager::getObservableSequenceId()
{
	ScopeLock lock( mObservableSqnsIdMutex );
	
	++mObservableSequenseIdCounter;
	mObservableSequenseIdCounter &= ~SEQUENSE_ID_KIND_MASK;
	return mObservableSequenseIdCounter; 
}

void BLKC_ConnectManager::sendCallBack(uint32_t session_id, unsigned char* sendbuf, MESSAGE_SIZE_T sendsize, LARGE_PARAM_ARRY& param_arry)
{
	InstanceScopeLock lock( (getConnectManagerInstanceMutex( session_id )) );

	BLKC_ConnectManager* connect_manager = BLKC_StubManager::getInstance()->getConnectManager(session_id);
	
	if( connect_manager == NULL ){
		LOG_ERROR("sendCallBack connect_manager is null. session_id: %d", session_id);
		return;
	}
	
	connect_manager->doSendCallBack( sendbuf, sendsize, param_arry );
}

void BLKC_ConnectManager::sendCallBack(uint32_t session_id, unsigned char* sendbuf, MESSAGE_SIZE_T sendsize)
{
	InstanceScopeLock lock( (getConnectManagerInstanceMutex( session_id )) );
	BLKC_ConnectManager* connect_manager = BLKC_StubManager::getInstance()->getConnectManager(session_id);
	
	if( connect_manager == NULL ){
		LOG_ERROR("sendCallBack connect_manager is null. session_id: %d", session_id);
		return;
	}

	if (false == connect_manager->isSocketConnected(BLKD_SOCKID_ASYNC)){
		LOG_ERROR("sendCallBack socket not connected. session_id: %d", session_id);
		return;
	}

	connect_manager->doSendCallBack( sendbuf, sendsize );
}

int BLKC_ConnectManager::doSendCallBack(unsigned char* sendbuf, MESSAGE_SIZE_T sendsize)
{
	SEQUENS_ID_T seqId = SEQUENSE_ID_CALL_BACK | getCallBackSequenceId();

	sendRequestMessage(seqId, sendbuf, sendsize, NULL, NULL );
	return 0;
}

int BLKC_ConnectManager::doSendCallBack(unsigned char* sendbuf, MESSAGE_SIZE_T sendsize, LARGE_PARAM_ARRY& param_arry)
{
	SEQUENS_ID_T seqId = SEQUENSE_ID_CALL_BACK_LARGE_PARAM | getCallBackSequenceId();

	sendRequestMessage(seqId, sendbuf, sendsize, &param_arry, NULL );
	return 0;
}

void BLKC_ConnectManager::sendRequestMessage( SEQUENS_ID_T seqID, unsigned char* buf, MESSAGE_SIZE_T len, LARGE_PARAM_ARRY* param_arry, LARGE_RET_VAL_ARRY* ret_arry )
{
	// BLKC_ConnectManager::sendSynchronizedRequest()
	// ==> BLKC_ConnectManager::sendSynchronizedRequest()
	// ==> BLKC_StubRequestManager::sendRequestData
	// ==> BLKC_ConnectManager::sendReqData
	bool result = false;
	do{
		result = mStubRequestManager->sendSynchronizedRequest(seqID, buf, len, param_arry, ret_arry);
	}while(result == false);
}

void BLKC_ConnectManager::sendObserverNotify(uint32_t session_id, unsigned char* sendbuf, MESSAGE_SIZE_T sendsize)
{
	InstanceScopeLock lock( (getConnectManagerInstanceMutex( session_id )) );
	BLKC_ConnectManager* connect_manager = BLKC_StubManager::getInstance()->getConnectManager(session_id);
	
	if(connect_manager == NULL){
		LOG_ERROR("connect_manager = null");
		return;
	}

	if (false == connect_manager->isSocketConnected(BLKD_SOCKID_ASYNC)){
		LOG_ERROR("socket not connected");
		return;
	}

	connect_manager->doSendObserverNotify( sendbuf, sendsize );
}

void BLKC_ConnectManager::sendObserverNotify(uint32_t session_id, unsigned char* sendbuf, MESSAGE_SIZE_T sendsize, LARGE_PARAM_ARRY& param_arry)
{
	InstanceScopeLock lock( (getConnectManagerInstanceMutex( session_id )) );

	BLKC_ConnectManager* connect_manager = BLKC_StubManager::getInstance()->getConnectManager(session_id);
	
	if(connect_manager == NULL){
		LOG_ERROR("connect_manager = null");
		return;
	}

	if (false == connect_manager->isSocketConnected(BLKD_SOCKID_ASYNC)){
		LOG_ERROR("socket not connected");
		return;
	}

	connect_manager->doSendObserverNotify( sendbuf, sendsize, param_arry );
}

int BLKC_ConnectManager::doSendObserverNotify(unsigned char* sendbuf, MESSAGE_SIZE_T sendsize)
{
	SEQUENS_ID_T seqId = SEQUENSE_ID_OBSERVER_NOTIFY | getObservableSequenceId();

	sendRequestMessage(seqId, sendbuf, sendsize, NULL, NULL );
	return 0;
}

int BLKC_ConnectManager::doSendObserverNotify(unsigned char* sendbuf, MESSAGE_SIZE_T sendsize, LARGE_PARAM_ARRY& param_arry)
{
	SEQUENS_ID_T seqId =  SEQUENSE_ID_OBSERVER_NOTIFY_LARGE_PARAM | getObservableSequenceId();

	sendRequestMessage(seqId, sendbuf, sendsize,  &param_arry, NULL );
	return 0;
}

void BLKC_ConnectManager::addObserverObject(OBSERVER_ID_T id, void* obj)
{
	mObserverIdAndObjectContainer->addIdAndObject( id, (ObserverDestructor*)obj );
}

void* BLKC_ConnectManager::findObserverObject(OBSERVER_ID_T id)
{
	void* obj = mObserverIdAndObjectContainer->findObject( id );

	return obj;
}

OBSERVER_ID_T BLKC_ConnectManager::findObserverId(void* obj)
{
	OBSERVER_ID_T id = mObserverIdAndObjectContainer->findId( (ObserverDestructor*)obj );

	return id;
}
void  BLKC_ConnectManager::deleteObserverObject(OBSERVER_ID_T id)
{
	mObserverIdAndObjectContainer->deleteObject( id );
}

OBSERVER_ID_T BLKC_ConnectManager::resistObserverObject(void* obj)
{
	OBSERVER_ID_T id = mObserverIdAndObjectContainer->resistObject( (ObserverDestructor*)obj );

	return id;
}
void BLKC_ConnectManager::ObserverIdAndObjectContainer::deleteAllObject( uint32_t connectionId )
{
	ScopeLock lock( mMutex );

	doDeleteAllObject( connectionId );
}

void BLKC_ConnectManager::ObserverIdAndObjectContainer::doDeleteAllObject( uint32_t connectionId )
{
	bool blWriteControlLog = false;

	ID_OBJECT_TBL_IT_T it = mIdObjectTbl.begin();
	ID_OBJECT_TBL_IT_T it_end = mIdObjectTbl.end();
	std::list<uint32_t> list;

	for ( ; it != it_end ; it++ ) {
		ObserverDestructor* obs_dst = (*it).second;

		if ( obs_dst != NULL ) {
			if ( obs_dst->getConnectId() == connectionId ) {
				list.push_back((*it).first);
			}
		}
	}

	std::list<uint32_t>::iterator lit = list.begin();
	std::list<uint32_t>::iterator lit_end = list.end();
	for (; lit != lit_end; lit++) {
		doDeleteObject(*lit);
	}
}

bool BLKC_ConnectManager::isKillProcessor()
{
	return mIsKillProcessor;
}

void BLKC_ConnectManager::exit()
{
	{
		ScopeLock lock( mInstanceMutexList.mutex() );
		mInstanceMutexList.erase( mConnectionId );
	}

	mIsKillProcessor = true;

	for( BLKD_SOCKID sockid = 0; sockid < BLKD_SOCKID_MAX; sockid++ ){
		mReceiveControl->setRxControl(connectFD[sockid],BLKD_RXCTRL_END);
	}
}

pid_t BLKC_ConnectManager::getPeerSysTid()
{
	return mPeerSys_tid;
}