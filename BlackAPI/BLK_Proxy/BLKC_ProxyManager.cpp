#include "pch.h"
#include "BLKC_ProxyManager.h"
#include "BLKC_ProxyCallBackTypedef.h"
#include "marsahling.h"
#include "unmarsahling.h"

uint32_t BLKC_ProxyManager::mCallBackIdCounter = 0;
std::map< uint32_t , void* > BLKC_ProxyManager::callBackFPTbl;
MutexLock BLKC_ProxyManager::mCallbackFpTblMutex;
MutexLock BLKC_ProxyManager::mCallBackIdMutex;
MutexLock BLKC_ProxyManager::mNotifyConnectErrorMutex;

BLKC_ProxyManager::ProxyManagerList* BLKC_ProxyManager::mProxyManagerList = NULL;

uint32_t getClassMethodIdByBuff( unsigned char* buf );
uint32_t getClassMethodIdByBuff(unsigned char* buf)
{
	return *(uint32_t*)buf;
}

BLKC_ProxyManager::BLKC_ProxyManager() : 
	mInstanceIdAndObjectContainer( NULL )
,	mSyncIdAndObjectContainer( NULL )
,	mEpollFd( -1 )
,	mConnectPid( 0 )
,	mConnectTid( 0 )
,	mRequestSequenseIdCounter( 0 )
,	mProxyRequestManager( 0 )
,	mObservableExecutor( 0 )
,	mObserverIdAndObjectContainer( 0 )
,	mConnectPThreadId( 0 )
,	mReceiveControl( 0 )
{

	for( BLKD_SOCKID sockid = 0; sockid < BLKD_SOCKID_MAX; sockid++ ) {
		mSocketFd[sockid] = -1;
		mIsSocketConnected[sockid] = false;
		mMessageReceiver[sockid] = 0;
		mReceiveThread[sockid] = 0;
		mReceiveProcessor[sockid] = 0;
		mReceiveThreadRunning[sockid] = false;
		mIsRecvThreadEnd[sockid] = false;
	}
}
BLKC_ProxyManager::~BLKC_ProxyManager()
{
	this->exit();
}

BLKC_ProxyManager::ReceiveProcessor::ReceiveProcessor()
{
	mProxyManager = NULL;
	mSockId = BLKD_SOCKID_INVALID;
}
BLKC_ProxyManager::ReceiveProcessor::~ReceiveProcessor(){}

BLKC_ProxyManager::ProxyIdAndObjectContainer::ProxyIdAndObjectContainer()
{
}

BLKC_ProxyManager::ProxyIdAndObjectContainer::~ProxyIdAndObjectContainer()
{
}

BLKC_ProxyManager::ReceiveProcessorTemporary::ReceiveProcessorTemporary() : mManager( NULL )
{
}
BLKC_ProxyManager::ReceiveProcessorTemporary::~ReceiveProcessorTemporary()
{
}

BLKC_ProxyManager::ConnectResetProcessor::ConnectResetProcessor(BLKC_ProxyManager* proxy_manager, BLKD_SOCKID sockid)
{
	mProxyManager = proxy_manager;
	mSockId = sockid;
}
		
BLKC_ProxyManager::ConnectResetProcessor::~ConnectResetProcessor()
{
}

BLKC_ProxyManager::ProxyManagerList::ProxyManagerList()
: mDestructing(false)
{
}

BLKC_ProxyManager::ProxyManagerList::~ProxyManagerList()
{
	typedef std::map<pthread_t , BLKC_ProxyManager*> PROXY_MANAGER_MAP_T;
	
	mDestructing = true;
	ScopeLock lock(PROXY_MANAGER_LIST_T::mutex());

	PROXY_MANAGER_MAP_T& instanse_map = PROXY_MANAGER_LIST_T::reference();
	PROXY_MANAGER_LIST_IT_T it = instanse_map.begin();
	PROXY_MANAGER_LIST_IT_T it_end = instanse_map.end();

	std::set<BLKC_ProxyManager*> instance_set;

	for(;it != it_end; it++){
		BLKC_ProxyManager* proxy = (*it).second;
		instance_set.insert( proxy  );
	}
	
	std::set<BLKC_ProxyManager*>::iterator it2 = instance_set.begin();
	std::set<BLKC_ProxyManager*>::iterator it2_end = instance_set.end();
	
	for(;it2 != it2_end; it2++){
		BLKC_ProxyManager* proxy = (*it2);
		delete  proxy;
		proxy = NULL;	
	}
}

static pthread_key_t  pthread_key_thread_finishing = (pthread_key_t)-1;
static pthread_once_t once_control = PTHREAD_ONCE_INIT;
static void BLKC_ProxyManagerThreadKeyCreate()
{
	pthread_key_create(&pthread_key_thread_finishing, BLKC_ProxyManager::pthread_key_destructor);
}

void BLKC_ProxyManager::pthread_key_destructor( void* arg)
{
    mProxyManagerList = ThreadSafeSingleton<ProxyManagerList>::getInstance();
    ScopeLock lock( mProxyManagerList->mutex() );
    mProxyManagerList->reference().erase( pthread_self() );
}

BLKC_ProxyManager* BLKC_ProxyManager::getInstance()
{
    pthread_t thread = pthread_self();

	pthread_once(&once_control,BLKC_ProxyManagerThreadKeyCreate);

	mProxyManagerList = ThreadSafeSingleton<ProxyManagerList>::getInstance();

	ScopeLock lock( mProxyManagerList->mutex() );

	
	PROXY_MANAGER_LIST_IT_T it = mProxyManagerList->reference().find( thread );
	PROXY_MANAGER_LIST_IT_T it_end = mProxyManagerList->reference().end();

	if(it != it_end){
		return (*it).second;
	}else{
		BLKC_ProxyManager* add_instance = new BLKC_ProxyManager;
		mProxyManagerList->reference().insert( std::make_pair( thread, add_instance ));
		add_instance->init_ProxyMgr();
		
		for(BLKD_SOCKID sockid = 0; sockid < BLKD_SOCKID_MAX; sockid++){

			while( add_instance->mReceiveThreadRunning[sockid] == false )
			{
				Thread::nanosleepThread(0, 100*1000);	// 100ms wait
			};

			mProxyManagerList->reference().insert( std::make_pair( add_instance->mReceiveThread[sockid]->getThreadId(), add_instance ));
		}
		
		pthread_setspecific(pthread_key_thread_finishing, add_instance);
		return add_instance;
	}
}

void BLKC_ProxyManager::init_ProxyMgr()
{
	ScopeLock lock( mSocketErrorMutex );

	mConnectPid = getpid();
	mConnectTid = (pid_t)syscall(SYS_gettid);
	mConnectPThreadId = pthread_self();

	init_Map();

	mInstanceIdAndObjectContainer = ThreadSafeSingleton<ProxyIdAndObjectContainer>::getInstance();
	mSyncIdAndObjectContainer = ThreadSafeSingleton<BLKC_SyncIdAndObjectContainer>::getInstance();

	mRequestSequenseIdCounter = 0;

    BLKD_SOCKID sockid;

	for( sockid = 0; sockid < BLKD_SOCKID_MAX; sockid++ ) {
		mIsSocketConnected[sockid] 		= false;
		mSocketFd[sockid] 				= -1;
		mMessageReceiver[sockid] 		= NULL;
		mReceiveThreadRunning[sockid] 	= false;
		mIsRecvThreadEnd[sockid] 		= false;
		mReceiveThread[sockid] 			= NULL;
		mReceiveProcessor[sockid] 		= NULL;
	}

	mObservableExecutor = new ObservableExecutor();
	
	mObserverIdAndObjectContainer = ThreadSafeSingleton<ObserverIdAndObjectContainer>::getInstance();

	mProxyRequestManager = new BLKC_ProxyRequestManager( mConnectTid );

    BLKD_EINTR_RETRY_CALL3(	mEpollFd = epoll_create1(EPOLL_CLOEXEC),
							mEpollFd == -1,
							LOG_ERROR("error epoll_create1\n") );
    
    for( sockid = 0; sockid < BLKD_SOCKID_MAX; sockid++ )
    {
        connectWithServer(sockid);

		mMessageReceiver[sockid] = new BLKC_MessageReceiver(mSocketFd[sockid], mProxyRequestManager, mConnectPid, mConnectTid);
		mMessageReceiver[sockid]->registHealthCheckHandler(new BLKC_ProxyHelthCheckMessageHandler(*this));
		mMessageReceiver[sockid]->registRequestHandler(new BLKC_ProxyRequestMessageHandler(*mProxyRequestManager, *this));
		mMessageReceiver[sockid]->registCallBackHandler(new BLKC_ProxyCallBackMessageHandler(*this));
		mMessageReceiver[sockid]->registObserverNotifyHandler(new BLKC_ProxyObseverNotifyMessageHandler(*this));
		mMessageReceiver[sockid]->registErrorHandler(new BLKC_ProxyErrorMessageHandler(*this, sockid));

		mIsSocketConnected[sockid] = true;
    }

    for( sockid = 0; sockid < BLKD_SOCKID_MAX; sockid++ ) 
    {
        sendControlData(sockid);

        mReceiveProcessor[sockid] = new ReceiveProcessor;
		mReceiveProcessor[sockid]->setParam(this, sockid);

        if(BLKD_SOCKID_SYNC == sockid) {
			mReceiveThread[sockid] = new Thread(mReceiveProcessor[sockid], "ProxyRcvTh" , DEF_PROXY_RECV_CTRL_THREAD_PRIO_RCV);
		} else {
			mReceiveThread[sockid] = new Thread(mReceiveProcessor[sockid], "ProxyAsyncRcvTh", DEF_PROXY_RECV_CTRL_THREAD_PRIO_ASYNCRCV);
		}

        mReceiveThread[sockid]->setStackSize(DEF_STACK_SIZE_PROXYRCVTH);
		mReceiveThread[sockid]->run();

		mReceiveControl = BLKC_ReceiveControl::newInstance(mConnectPid,mSocketFd[sockid], this, true );

		mReceiveControl->addReceiveThreadInfo(mReceiveThread[sockid]->getThreadId(),
									BLKC_ReceiveControl::STATE_IDLE,
									((BLKD_SOCKID_SYNC == sockid) ? BLKC_ReceiveControl::MODE_RECEIVE : BLKC_ReceiveControl::MODE_RECEIVEASYNC),
									this,mReceiveProcessor[sockid],mSocketFd[sockid]);

		mReceiveControl->setRxControl(mSocketFd[sockid], BLKD_RXCTRL_START);
    }
}

void BLKC_ProxyManager::connectWithServer(BLKD_SOCKID sockid)
{
    struct sockaddr_un servAddr;

	memset( &servAddr, 0x00, sizeof(sockaddr_un) );
	servAddr.sun_family = AF_UNIX;
	strncpy( servAddr.sun_path, BLKC_PortNumberGetter::createThatServerSocketFile(), (sizeof(servAddr.sun_path)-1) );

    mSocketFd[sockid] = socket( AF_UNIX, SOCK_STREAM, 0);

    if ( -1 >= mSocketFd[sockid] ) {
		return;
	}

    if ( -1 >= fcntl( mSocketFd[sockid], F_SETFD, FD_CLOEXEC ) ) {
		shutdown(mSocketFd[sockid], SHUT_RDWR );
		close(mSocketFd[sockid]);
		mSocketFd[sockid] = -1;
		return;
	}

    int result = -1;
    int count = 0;
	while(result < 0)
	{
		result = connect(mSocketFd[sockid], (struct sockaddr*)&servAddr, sizeof(servAddr));
		if (result >= 0)
		{
			break;
		}
        count++;
		usleep(500000);
	}

	LOG_DEBUG("socket mode %s connect to server success!", (sockid == BLKD_SOCKID_SYNC) ? "sync" : "async");

    struct epoll_event event = {0, reinterpret_cast<void*>(mSocketFd[sockid])};
	BLKD_EINTR_RETRY_CALL3(	result = epoll_ctl(mEpollFd, EPOLL_CTL_ADD, mSocketFd[sockid], &event),
							result == -1,
							LOG_ERROR("error epoll_ctl\n") );
}

void BLKC_ProxyManager::sendControlData(BLKD_SOCKID sockid)
{
    BLKS_SOCKET_CONTROLDATA data;
	int ret;
	int policy;
	struct sched_param param;

    memset(&data,0,sizeof(data));
	data.sys_pid = getpid();
	data.sys_tid = (pid_t)syscall( SYS_gettid );
	ret = pthread_getschedparam(pthread_self(),&policy,&param);
	if(ret != 0) {
		param.sched_priority = 0;
	}

    data.priority = param.sched_priority;
	data.sockid = sockid;

    ScopeLock lock(mSocketMutex);
	LOG_DEBUG("client send control data to server...");
    sendSocket( mSocketFd[sockid], (unsigned char*)&data,sizeof(data), sockid );
}

int BLKC_ProxyManager::sendSocket(int sock_fd, unsigned char *buf, MESSAGE_SIZE_T size, BLKD_SOCKID sockid)
{
    if( ( size == 0 ) || ( buf == NULL ) ){
		return 0;
	}

	int ret = -1;
	MESSAGE_SIZE_T sendedsize = 0;
    int epret = 0;
	struct epoll_event events[1];

    events[0].events = (EPOLLOUT | EPOLLRDHUP);
	events[0].data.fd = sock_fd;
	BLKD_EINTR_RETRY_CALL3(	epret = epoll_ctl(mEpollFd, EPOLL_CTL_MOD, sock_fd, &events[0]),
							epret == -1,
							LOG_ERROR("error epoll_ctl\n");
							return 0 );

    while( true )
    {
        ret = epoll_wait(mEpollFd, events, sizeof(events)/sizeof(events[0]), -1);

        if (ret == -1){
			if( errno == EINTR ){
				continue;
			}
			break;
		}

        if(sock_fd != events[0].data.fd){
			continue;
		}

		BLKS_SOCKET_CONTROLDATA dataLog;
		memcpy(&dataLog, buf, sizeof(dataLog));
		LOG_DEBUG("client send to server...");
        ret = (int)send(sock_fd, buf + sendedsize, size - sendedsize, MSG_NOSIGNAL );

		if (ret < 0)
		{
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
							LOG_ERROR("error epoll_ctl\n") );

	if((ret == -1) && (mIsSocketConnected[sockid] == true)){
		notifyConnectError(sockid);
	}

    return ret;
}

void BLKC_ProxyManager::ReceiveProcessor::setParam(BLKC_ProxyManager *manager, BLKD_SOCKID sockid)
{
	mProxyManager = manager;
	mSockId = sockid;
}

BLKD_SOCKID BLKC_ProxyManager::ReceiveProcessor::getSockId()
{
	return mSockId;
}

void BLKC_ProxyManager::ReceiveProcessor::run()
{
	mProxyManager->Recv_ProxyMgr(mSockId);
}

void BLKC_ProxyManager::Recv_ProxyMgr(BLKD_SOCKID sockid)
{
    int sfd = -1;
    mReceiveThreadRunning[sockid] = true;
    BLKC_ProxyReceiveThreadContext context;

    while(1)
    {
        mReceiveProcessor[sockid]->wait(&sfd);

        if(sfd < 0) { break;}

        messageReceive(&context, sockid);

		mReceiveControl->changeState(pthread_self(),BLKC_ReceiveControl::STATE_IDLE);

		mReceiveControl->setRxControl(sfd,BLKD_RXCTRL_UPDATE);
    }

	mReceiveControl->deleteReceiveThreadInfo(pthread_self());

	mReceiveControl->setRxControl(mSocketFd[sockid],BLKD_RXCTRL_UPDATE);

	{
		mProxyManagerList = ThreadSafeSingleton<ProxyManagerList>::getInstance();

		if( !mProxyManagerList->isDestructing() ){

			{
				ScopeLock lock( mProxyManagerList->mutex() );

				mProxyManagerList->reference().erase( pthread_self() );
			}

		}
	}

	mIsRecvThreadEnd[sockid] = true;

	return;
}

void BLKC_ProxyManager::ReceiveProcessor::wait(int* fd)
{
	LOG_DEBUG("Semaphore proxy receive wait");
	mOperationSemaphore.wait();
	LOG_DEBUG("Semaphore proxy receive release");
	mOperationMutex.lockWait();
	*fd = mOperationList.front();
	mOperationList.pop_front();
	mOperationMutex.unlock();
}

void BLKC_ProxyManager::messageReceive(BLKC_ReceiveThreadContext* context, BLKD_SOCKID sockid)
{
	MESSAGE_HANDLER_ARRY* handlers = mMessageReceiver[sockid]->getMessages();
	MESSAGE_HANDLER_ARRY c_handler(*handlers);
	handlers = &c_handler;
	if(handlers->empty() == false){
		MESSAGE_HANDLER_ARRY::iterator it = handlers->begin();
		MESSAGE_HANDLER_ARRY::iterator it_end = handlers->end();
		for(;it != it_end;it++){
			(*it)->exec(context);
			delete *it;
		}
	}
}

void BLKC_ProxyManager::NotifyReceiveControl(Runnable* processor, BLKD_SOCKID sockid)
{
	ReceiveProcessor* pProcessor = reinterpret_cast<ReceiveProcessor*>(processor);
	if(pProcessor != NULL) {
		pProcessor->post(mSocketFd[sockid]);
	} else {
		executeRecv( sockid );
	}
}

void BLKC_ProxyManager::ReceiveProcessor::post(int fd)
{
	mOperationMutex.lockWait();
	if( fd == -1 ){
		mOperationList.push_front(fd);
	}else{
		mOperationList.push_back(fd);
	}
	mOperationMutex.unlock();

	mOperationSemaphore.post();
	LOG_DEBUG("Semaphore proxy receive post");
}

void BLKC_ProxyManager::executeRecv( BLKD_SOCKID sockid )
{
	ReceiveProcessorTemporary* pProcessor = NULL;
	try {
		pProcessor = new ReceiveProcessorTemporary;
	} catch(...) {
		LOG_ERROR("ReceiveProcessorTemporary Create Failed.");
		return;
	}
	if(NULL == pProcessor){
		LOG_ERROR("ReceiveProcessorTemporary Create Failed.");
		return;
	}
	pProcessor->setParam(this);
	
	Thread* pThread = NULL;
	try {
		pThread = new Thread(pProcessor, "ProxyTmpRcvTh", TYPD_PRIONO_BLKLIB__ProxyTmpRcvTh);
	} catch(...) {
		LOG_ERROR("ReceiveProcessorTemporary Create Failed.");
		delete pProcessor;
		return;
	}
	if(NULL == pThread){
		LOG_ERROR("ReceiveProcessorTemporary Create Failed.");
		delete pProcessor;
		return;
	}

	pThread->setStackSize(DEF_STACK_SIZE_PROXYRCVTH);

	pThread->run();	

	pthread_t threadId = pThread->getThreadId();
	mReceiveControl->addReceiveThreadInfo(threadId, 
									BLKC_ReceiveControl::STATE_EXEC,
									BLKC_ReceiveControl::MODE_RECEIVETEMPORARY,
									this,pProcessor,mSocketFd[BLKD_SOCKID_ASYNC]);
}

void BLKC_ProxyManager::ReceiveProcessorTemporary::run()
{
	mManager->Recv_ProxyMgr_Temporary();
}

void BLKC_ProxyManager::Recv_ProxyMgr_Temporary()
{
	{
		ProxyManagerList* mProxyManagerList = ThreadSafeSingleton<ProxyManagerList>::getInstance();
		ScopeLock lock( mProxyManagerList->mutex() );
		mProxyManagerList->reference().insert( std::make_pair( pthread_self(), this ));
	}

	BLKC_ProxyReceiveThreadContext context;
	
	messageReceive(&context, BLKD_SOCKID_ASYNC);

	mReceiveControl->deleteReceiveThreadInfo(pthread_self());

	mReceiveControl->setRxControl(mSocketFd[BLKD_SOCKID_ASYNC],BLKD_RXCTRL_UPDATE);

	{
		mProxyManagerList = ThreadSafeSingleton<ProxyManagerList>::getInstance();
		ScopeLock lock( mProxyManagerList->mutex() );
		mProxyManagerList->reference().erase( pthread_self() );
	}
}

void BLKC_ProxyManager::ReceiveProcessorTemporary::setParam(BLKC_ProxyManager *manager)
{
	mManager = manager;
}

void  BLKC_ProxyManager::releaseBuffer(unsigned char *buf)
{	
	unsigned char* release_address = buf - offsetof(BLKS_MSG_FORMAT, payload);
	delete release_address;
}

void BLKC_ProxyManager::setInstanceId(uint32_t instanceId , void* instanceObj)
{

	mInstanceIdAndObjectContainer->addIdAndObject( instanceId, instanceObj);
}

uint32_t  BLKC_ProxyManager::getInstanceId(void* obj)
{
	return mInstanceIdAndObjectContainer->findId( obj );
}

void* BLKC_ProxyManager::getObject(uint32_t instanceId)
{
	if( instanceId == 0 ) return NULL;
	
	return mInstanceIdAndObjectContainer->findObject( instanceId );
}

void BLKC_ProxyManager::deleteInstanceId(uint32_t instanceId)
{
	mInstanceIdAndObjectContainer->unregistObject( instanceId );
}

uint32_t BLKC_ProxyManager::reserveSyncObject()
{
	return mSyncIdAndObjectContainer->reserveSyncObject();
}

void BLKC_ProxyManager::addSyncObject( const std::type_info* type )
{
	mSyncIdAndObjectContainer->addSyncObject( type );
}

void BLKC_ProxyManager::readySyncObject( uint32_t uDataIndex )
{
	mSyncIdAndObjectContainer->readySyncObject( uDataIndex );
}

bool BLKC_ProxyManager::waitSyncObject( const std::type_info* type )
{
	return mSyncIdAndObjectContainer->waitSyncObject( type );
}

void BLKC_ProxyManager::signalSyncObject( uint32_t uDataIndex )
{
	mSyncIdAndObjectContainer->signalSyncObject( uDataIndex );
}

void BLKC_ProxyManager::sendRequestData( SEQUENS_ID_T seqId, unsigned char* buf, MESSAGE_SIZE_T len,  LARGE_PARAM_ARRY* mRequestLargeParamArry)
{
	BLKD_SOCKID sockid = mReceiveControl->getSockId();
	ScopeLock lock(mSocketMutex);

	sendMessage(seqId, buf, len, sockid);
	
	if( mRequestLargeParamArry == NULL ){
		return;
	}

	LARGE_PARAM_ARRY::iterator it = mRequestLargeParamArry->begin();
	LARGE_PARAM_ARRY::iterator it_end = mRequestLargeParamArry->end();
	
	BLKS_MSGHEAD msg_header;
	
	msg_header.sequenceId = SEQUENSE_ID_REQUEST_LARGE_PARAM;
	for( ; it != it_end ; it++ ){
		if( (*it)->destination == NULL ){
			(*it)->size = 0;
		}
		msg_header.msgSize = (*it)->size + BLKD_MSGHEAD_SIZE;

		sendSocket( mSocketFd[sockid], (unsigned char*)&msg_header, BLKD_MSGHEAD_SIZE, sockid );

		sendSocket( mSocketFd[sockid], (unsigned char*)(*it)->destination, (*it)->size, sockid );
	}
}

void BLKC_ProxyManager::sendMessage( SEQUENS_ID_T seqId, unsigned char* buf, MESSAGE_SIZE_T len, BLKD_SOCKID sockid )
{
	unsigned char *wbuf = buf - BLKD_MSGHEAD_SIZE;
	BLKS_MSGHEAD* msgheader_p;
	MESSAGE_SIZE_T send_len= len + BLKD_MSGHEAD_SIZE;

	msgheader_p = (BLKS_MSGHEAD*)wbuf;
	msgheader_p->msgSize = send_len;
	msgheader_p->sequenceId = seqId;
	msgheader_p++;

	int ret = sendSocket( mSocketFd[sockid], wbuf, send_len, sockid );

	if(ret == -1) {LOG_ERROR("sendSocket error");}
}

void BLKC_ProxyManager::NotifyReplyMessage(unsigned char *buf, MESSAGE_SIZE_T len, SEQUENS_ID_T seqId)
{

	BLKD_SOCKID sockid = mReceiveControl->getSockId();

	mReceiveControl->setRxControl(mSocketFd[sockid], BLKD_RXCTRL_START);

	mProxyRequestManager->notifyReplyMessage(seqId,buf,len);
}

void BLKC_ProxyManager::NotifyCallBackMessage(unsigned char *buf, MESSAGE_SIZE_T len, SEQUENS_ID_T seqId, BLKC_ReceiveThreadContext* context)
{
	SEQUENS_ID_T seqId_kind = seqId & SEQUENSE_ID_KIND_MASK;

	if(!( (seqId_kind == SEQUENSE_ID_CALL_BACK_LARGE_PARAM) || (seqId_kind == SEQUENSE_ID_CALL_BACK_LARGEPRM_NOWAIT) ) ) {

		mReceiveControl->setRxControl(mSocketFd[BLKD_SOCKID_ASYNC], BLKD_RXCTRL_START);
	}

	mReceiveControl->setSequenceId(seqId);

	BLKC_ProxyManager::callBackExec(buf, len, seqId, NULL, context);

	releaseBuffer(buf);
}

void BLKC_ProxyManager::NotifyObserverMessage(unsigned char *buf, MESSAGE_SIZE_T len, SEQUENS_ID_T seqId, BLKC_ReceiveThreadContext* context)
{

	mReceiveControl->setSequenceId(seqId);

	SEQUENS_ID_T seqId_kind = seqId & SEQUENSE_ID_KIND_MASK;
	if(!( (seqId_kind == SEQUENSE_ID_OBSERVER_NOTIFY_LARGE_PARAM) || (seqId_kind == SEQUENSE_ID_OBSERVER_LARGEPRM_NOAWIT) ) ) {
		mReceiveControl->setRxControl(mSocketFd[BLKD_SOCKID_ASYNC], BLKD_RXCTRL_START);
	}

	BLKS_COMMONID common_id;
	unsigned char* pt = buf;
	void *object_pt = NULL;

	pt = (unsigned char*)unmarshal_ClassMethodID(pt, &common_id.ClassMethodID );
	pt = (unsigned char*)unmarshal_InstanceID(pt, &common_id.InstanceID );
	pt = (unsigned char*)unmarshal_SessionID(pt, &common_id.SessionID );


	if ( common_id.InstanceID == BLKD_PRE_OBSERVER_ID_NOWAIT ) {
		object_pt = getObject( BLKD_PRE_OBSERVER_ID );
	}
	else {
		object_pt = getObject( common_id.InstanceID );
	}

	if ( ((common_id.InstanceID == BLKD_PRE_OBSERVER_ID) || (common_id.InstanceID == BLKD_PRE_OBSERVER_ID_NOWAIT)) && (object_pt == NULL) ) {
		common_id.InstanceID = BLKD_NOTPRE_OBSERVER_ID;
		SendRply_Observer( buf, &common_id, seqId );
		releaseBuffer(buf);

		return;
	}
	else if ( common_id.InstanceID == BLKD_PRE_OBSERVER_ID_NOWAIT ) {
		SendRply_Observer( buf, &common_id, seqId );
	}

	BLKC_ProxyManager::observableExec(buf, len, seqId, object_pt, context);

	releaseBuffer(buf);
}

void BLKC_ProxyManager::notifyConnectError(BLKD_SOCKID sockid)
{
	ScopeLock lock( mSocketErrorMutex );
	
	if(mIsSocketConnected[sockid] == false){
		LOG_WARN("socket %s disconect", (sockid == BLKD_SOCKID_SYNC) ? "sync" : "async");
		return;
	}

	mReceiveControl->setRxControl(mSocketFd[sockid],BLKD_RXCTRL_END);
	
	mIsSocketConnected[sockid] = false;

	if( !mProxyManagerList->isDestructing() ){

		Thread *KillThread = new Thread( new BLKC_ProxyManager::ConnectResetProcessor( this, sockid ), "ConResetProTh", TYPD_PRIONO_BLKLIB__ConResetProTh);

		if (KillThread == NULL){
			LOG_ERROR("ConResetProTh Create Error!!!");
			return;
		}
		
		LOG_WARN("Connect error... start kill and reset thread %s!!!", (sockid == BLKD_SOCKID_SYNC) ? "sync" : "async");
		KillThread->setStackSize(DEF_STACK_SIZE_CONRESETPROTH);
		KillThread->run();
	}
}

void BLKC_ProxyManager::ConnectResetProcessor::run()
{
	ScopeLock lock( mNotifyConnectErrorMutex );
	
	mProxyManager->exit();

	mProxyManager->init_ProxyMgr();
}

void BLKC_ProxyManager::Send_ProxyMgr( unsigned char* buf, MESSAGE_SIZE_T len)
{
	sendRequestMessage( SEQUENSE_ID_SYNC_REQUEST, buf, len );
}

void BLKC_ProxyManager::Send_ProxyMgr( unsigned char* buf, MESSAGE_SIZE_T len, LARGE_RET_VAL_ARRY& ret_arry)
{
	sendRequestMessage( SEQUENSE_ID_SYNC_REQ_WITH_LARGE_RETVAL, buf, len, NULL, &ret_arry );
}


void BLKC_ProxyManager::Send_ProxyMgr( unsigned char* buf, MESSAGE_SIZE_T len, LARGE_PARAM_ARRY& param_arry)
{
	sendRequestMessage( SEQUENSE_ID_SYNC_REQ_LARGE_PARAM, buf, len, &param_arry );
}

void BLKC_ProxyManager::Send_ProxyMgr( unsigned char* buf, MESSAGE_SIZE_T len, LARGE_PARAM_ARRY& param_arry, LARGE_RET_VAL_ARRY& ret_arry)
{
	sendRequestMessage( SEQUENSE_ID_SYNC_REQ_LARGE_PARAM_RETVAL, buf, len, &param_arry, &ret_arry );
}

void BLKC_ProxyManager::sendRequestMessage( SEQUENS_ID_T seqID, unsigned char* buf, MESSAGE_SIZE_T len, LARGE_PARAM_ARRY* param_arry, LARGE_RET_VAL_ARRY* ret_arry )
{
	SEQUENS_ID_T sequence_id;
	bool result;
	
	sequence_id = seqID | getSequenceID();

	bool blWriteControlLog = false;
	uint32_t ui32ClassMethodId = 0;
	uint32_t ui32PartitionIndex = 0;
	pthread_t threadId = 0;

	if ( getpid() != mConnectPid ) { return; }

	do{
		// BLKC_ProxyRequestManage::sendSynchronizedRequest()
		// ==> BLKC_SynchronizedMediator::sendSynchronizedRequest()
		// ==> BLKC_ProxyRequestManager::sendRequestData
		// ==> BLKC_ProxyManager::sendRequestData
		result = mProxyRequestManager->sendSynchronizedRequest( sequence_id, buf, len, param_arry, ret_arry);
	}while(result == false);
}

SEQUENS_ID_T BLKC_ProxyManager::getSequenceID()
{
	ScopeLock lock( mRequestSequenseIdMutex );

	++mRequestSequenseIdCounter;
	mRequestSequenseIdCounter &= ~SEQUENSE_ID_KIND_MASK;
	return mRequestSequenseIdCounter;
}

void BLKC_ProxyManager::deleteInstance()
{
	pthread_t thread = pthread_self();

	ScopeLock lock( mProxyManagerList->mutex() );
	
	PROXY_MANAGER_LIST_IT_T it = mProxyManagerList->reference().find( thread );
	PROXY_MANAGER_LIST_IT_T it_end = mProxyManagerList->reference().end();

	if(it != it_end){
		delete (*it).second;
		mProxyManagerList->reference().erase( thread );
	}
}

void BLKC_ProxyManager::exit()
{
	mSocketErrorMutex.lockWait();
		
	BLKD_SOCKID sockid; 
	bool bIsShutdown[BLKD_SOCKID_MAX] = {};
	int ret = 0;

	for( sockid = 0; sockid < BLKD_SOCKID_MAX; sockid++ ) {
		bIsShutdown[sockid] = false;
		if(mIsSocketConnected[sockid] == false){
			continue;
		}

		if( mReceiveControl != NULL ){
			mReceiveControl->setRxControl(mSocketFd[sockid],BLKD_RXCTRL_END);
		}

		if( (mEpollFd != -1) && (mSocketFd[sockid] != -1) ) {
			BLKD_EINTR_RETRY_CALL3(	ret = epoll_ctl(mEpollFd, EPOLL_CTL_DEL, mSocketFd[sockid], NULL),
									ret == -1,
									printf("error epoll_ctl\n") );
		}

		mIsSocketConnected[sockid] = false;
		shutdown(mSocketFd[sockid], SHUT_RDWR );
		bIsShutdown[sockid] = true;

		mMessageReceiver[sockid]->exit();

		if ( getpid() == mConnectPid ) {
			mSocketErrorMutex.unlock();
			if(mIsRecvThreadEnd[sockid] == false) {
				mReceiveProcessor[sockid]->post(-1);
			}

			while(mIsRecvThreadEnd[sockid] == false){
				Thread::nanosleepThread(0, 100*1000);	// 100ms wait
			}
			mSocketErrorMutex.lockWait();
		}
		else {
			LOG_ERROR( "BLKC_ProxyManager::exit() RecvThread no wait (%d)!=(%d)\n", getpid(), mConnectPid );
		}
	}

	if( mEpollFd != -1 ) {
		BLKD_EINTR_RETRY_CALL(ret = close(mEpollFd), ret == -1);
		mEpollFd = -1;
	}

	BLKC_ReceiveControl::exitAndDeleteInstance(mConnectPid, mSocketFd);
	mReceiveControl = NULL;

	eraseProxyManagerList(true,this);

	for( sockid = 0; sockid < BLKD_SOCKID_MAX; sockid++ ) {
		close(mSocketFd[sockid]);
		mSocketFd[sockid] = -1;
	}

	for( sockid = 0; sockid < BLKD_SOCKID_MAX; sockid++ ) {
		delete mMessageReceiver[sockid];
	}

	delete mObservableExecutor;
//	delete mObserverIdAndObjectContainer;
	delete mProxyRequestManager;
	
	mSocketErrorMutex.unlock();
	
}

int BLKC_ProxyManager::eraseProxyManagerList(bool bErase, BLKC_ProxyManager* pManager)
{
	int count = 0;
	mProxyManagerList = ThreadSafeSingleton<ProxyManagerList>::getInstance();

	if( !mProxyManagerList->isDestructing() ){
		ScopeLock lock( mProxyManagerList->mutex() );

		if(bErase != false) {

			PROXY_MANAGER_LIST_IT_T it = mProxyManagerList->reference().begin();
			for(;it != mProxyManagerList->reference().end();){
				if(pManager == it->second) {
					mProxyManagerList->reference().erase(it++);
					count++;
				} else {
					++it;
				}
			}
		} else {
			PROXY_MANAGER_LIST_IT_T it = mProxyManagerList->reference().begin();
			PROXY_MANAGER_LIST_IT_T it_end = mProxyManagerList->reference().end();
			for(;it != it_end;++it){
				if(pManager == it->second) {
					count++;
				}
			}
		}
	}
	return count;
}

uint32_t BLKC_ProxyManager::setCallBackFP(uint32_t callbackId, void* callBackFP)
{
	ScopeLock lock( mCallbackFpTblMutex );
	
	uint32_t workId = 0;

	std::map<uint32_t, void*>::iterator it = callBackFPTbl.end();

	if(!callBackFPTbl.empty()){
		workId = callbackId;

		for(int i=0;it != callBackFPTbl.find(workId);i++){
			if(i>65535){
				return 0xffffffff;
			}

			workId = getCallBackFPId( callbackId & BLKD_PROXY_CBID_FRAG );
		}
	}
	if(workId != 0){
		callBackFPTbl.insert( std::map<uint32_t, void*>::value_type( workId, callBackFP ) );

		// BLKC_WatchPanelLock::getInstance()->registerCallBackId( workId, mConnectTid );
	}else{
		callBackFPTbl.insert( std::map<uint32_t, void*>::value_type( callbackId, callBackFP ) );

		// BLKC_WatchPanelLock::getInstance()->registerCallBackId( callbackId, mConnectTid );
	}

	return workId;
}

void* BLKC_ProxyManager::getCallBackFP(uint32_t callbackId)
{
	ScopeLock lock( mCallbackFpTblMutex );

	void *ret;

	std::map<uint32_t, void*>::iterator it = callBackFPTbl.find(callbackId);
	if(callBackFPTbl.end() != it){
		ret = (*it).second;

		// BLKC_WatchPanelLock::getInstance()->resetCallBackIdTime( callbackId );
	}else{
		ret = NULL;
	}

	return ret;
}

void BLKC_ProxyManager::deleteCallBackFP(uint32_t callbackId)
{
	ScopeLock lock( mCallbackFpTblMutex );

	callBackFPTbl.erase(callbackId);

	// BLKC_WatchPanelLock::getInstance()->unregisterCallBackId( callbackId );
}

void BLKC_ProxyManager::clearCallBackFP()
{
	ScopeLock lock( mCallbackFpTblMutex );

	callBackFPTbl.clear();

	// BLKC_WatchPanelLock::getInstance()->clearCallBackId();
}

SEQUENS_ID_T BLKC_ProxyManager::getCallBackFPId(uint32_t callBackId)
{
	ScopeLock lock( mCallBackIdMutex );

	++mCallBackIdCounter;
	mCallBackIdCounter &= ~BLKD_PROXY_CBID_FRAG;

	return callBackId | mCallBackIdCounter;
}

void BLKC_ProxyManager::SendRply_ProxyMgr(unsigned char* buf, MESSAGE_SIZE_T len)
{
	// ReciveProcesser::getMessage()
	// =>xxxHandler
	// =>NotifyCallBackMessage/NotifyObserverMessage.
	// =>BLKC_ProxyManager::callBackExec or BLKC_ProxyManager::observableExec.
	// 	 => Template:xxxxPre  ==>receiveLargeParamCallBack/receiveLargeParamObserverNotify
	// 	 =>Template:xxxxPost  ==>SendRply_ProxyMgr
	
	SEQUENS_ID_T seqId = mReceiveControl->getSequenceId();
	BLKD_SOCKID sockid = BLKD_SOCKID_ASYNC;
	ScopeLock lock(mSocketMutex);
	sendMessage(seqId, buf, len, sockid);
}

OBSERVER_ID_T BLKC_ProxyManager::resistObserverObject(void* obj)
{
	OBSERVER_ID_T id = mObserverIdAndObjectContainer->resistObject( (ObserverDestructor*)obj );
	return id;
}

void BLKC_ProxyManager::addObserverObject(OBSERVER_ID_T id, void* obj)
{
	mObserverIdAndObjectContainer->addIdAndObject( id, (ObserverDestructor*)obj );
}

OBSERVER_ID_T BLKC_ProxyManager::findObserverId(void* obj)
{
	OBSERVER_ID_T id = mObserverIdAndObjectContainer->findId( (ObserverDestructor*)obj );
	return id;
}


void BLKC_ProxyManager::deleteObserverObject(OBSERVER_ID_T id)
{
	mObserverIdAndObjectContainer->unregistObject( id );
}

void BLKC_ProxyManager::observableExec(unsigned char* buf , MESSAGE_SIZE_T len, SEQUENS_ID_T seqId, void *object_pt, BLKC_ReceiveThreadContext* context)
{
	BLKS_COMMONID common_id;
	
	unsigned char* pt = buf;
	
	pt = (unsigned char*)unmarshal_ClassMethodID(pt, &common_id.ClassMethodID );
	pt = (unsigned char*)unmarshal_InstanceID(pt, &common_id.InstanceID );
	pt = (unsigned char*)unmarshal_SessionID(pt, &common_id.SessionID );

	mObservableExecutor->exec( *this, &common_id, buf, object_pt, context);
}

void BLKC_ProxyManager::SendRply_Observer( unsigned char* buf, BLKS_COMMONID* p_common_id, SEQUENS_ID_T seqId )
{
	short size = 0;
	unsigned char* pt = buf;
	marshal_setCommonID( pt, p_common_id, &size );
	ScopeLock lock(mSocketMutex);
	sendMessage( seqId, buf, size, BLKD_SOCKID_ASYNC );
}

// =============================================================================================

void BLKC_ProxyManager::dumnyMethod()
{
}