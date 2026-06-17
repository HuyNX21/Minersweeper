#include "pch.h"
#include "BLKC_StubManager.h"

BLKC_StubManager* BLKC_StubManager::thisInstance = NULL;
pthread_once_t BLKC_StubManager::mOnceInit = PTHREAD_ONCE_INIT;

BLKC_StubManager::BLKC_StubManager()
{
    mConnectManagerList.reserve( 32 );
	CONNECT_MANAGER_LIST_T::iterator it     = mConnectManagerList.begin();
	CONNECT_MANAGER_LIST_T::iterator it_end = mConnectManagerList.end();
	for( ; it != it_end ; it++ ){
		*it = NULL;
	}
    mConnectMngListMutex = new MutexLock;
	mConnectThreadRunning = false;
	mConnectThread = NULL;
	mConnectProcessor = NULL;
	mConnectSocketFd = -1;
	mEpollFd = -1;

    mUnlockInstanceManager = new BLKC_UnlockInstanceManager();
}
BLKC_StubManager::~BLKC_StubManager(){}
BLKC_StubManager::ConnectProcessor::ConnectProcessor(BLKC_StubManager& stub_manager) : mStubManager( stub_manager ){}
BLKC_StubManager::ConnectProcessor::~ConnectProcessor(){}

BLKC_StubManager::ConnectKillProcessor::ConnectKillProcessor(BLKC_ConnectManager* connect_manager, int connectionId, BLKD_SOCKID sockid)
{
	mConnectManager = connect_manager;
	mConnectionId = connectionId;
	mSockId = sockid;
}
		
BLKC_StubManager::ConnectKillProcessor::~ConnectKillProcessor()
{
}

BLKC_StubManager* BLKC_StubManager::getInstance()
{
	pthread_once(&mOnceInit, bootStubManager);

	return thisInstance;
}

void BLKC_StubManager::bootStubManager()
{
	try{

		thisInstance = new BLKC_StubManager();
		thisInstance->init();

	}catch(std::exception& ex){
        LOG_ERROR("The exception was thrown out. %s",ex.what());
	}
}

void BLKC_StubManager::init()
{
	mConnectProcessor = new ConnectProcessor(*this);
	
	mConnectThread = new Thread(mConnectProcessor, "SrvConnectTh", DEF_STUB_THREAD_PRIO_SRVC);

	mConnectThread->setStackSize(DEF_STACK_SIZE_SRVCONNECTTH);
    
	mConnectThread->run();
}

void BLKC_StubManager::ConnectProcessor::run()
{
    mStubManager.connectWait_Main();
    return;
}

void* BLKC_StubManager::connectWait_Main()
{
    int					result = 0;
	int					connectionId = -1;
	struct epoll_event	events[1];
	struct timespec		elapsed[2];

    struct sockaddr_un addr;
	memset( &addr, 0x00, sizeof(sockaddr_un) );
	strncpy( addr.sun_path, BLKC_PortNumberGetter::createThisServerSocketFile(), (sizeof(addr.sun_path)-1) );
	unlink( addr.sun_path );
	addr.sun_family = AF_UNIX;

	mConnectSocketFd = socket(AF_UNIX, SOCK_STREAM, 0);

    result = bind((int)mConnectSocketFd, (struct sockaddr*)&addr, sizeof(addr));
    if (result != 0){goto ERR_EXIT;}

    result = chmod( addr.sun_path, S_IRUSR | S_IWUSR | S_IXUSR | S_IROTH | S_IWOTH | S_IXOTH );
    if (result != 0){goto ERR_EXIT;}

    result = listen((int)mConnectSocketFd, BLKD_CONNECTID_MAX);
    if (result != 0){goto ERR_EXIT;}

    BLKD_EINTR_RETRY_CALL3(	mEpollFd = epoll_create1(EPOLL_CLOEXEC),
							mEpollFd == -1,
							LOG_ERROR("error epoll_create1");
							goto ERR_EXIT );

    events[0].events = (EPOLLIN | EPOLLRDHUP);
	events[0].data.fd = mConnectSocketFd;

	BLKD_EINTR_RETRY_CALL3(	result = epoll_ctl(mEpollFd, EPOLL_CTL_ADD, mConnectSocketFd, &events[0]),
							result == -1,
							LOG_ERROR("error epoll_ctl");
							goto ERR_EXIT );

    struct timeval  tm_out;
	struct timeval  tm_out_master;
	tm_out_master.tv_sec  = 5;
	tm_out_master.tv_usec = 0;
    mConnectThreadRunning = true;
	while(mConnectThreadRunning == true)
    {
        tm_out = tm_out_master;
		BLKC_ConnectManager* stub_connectManager_p = NULL;
    RETRY:
        result = epoll_wait(mEpollFd, events, sizeof(events)/sizeof(events[0]), getEpollMsec(&tm_out, elapsed));

        if (result < 0){
			if( errno == EINTR ){
				calcEpollElapsed(result, &tm_out, elapsed);
				goto RETRY;
			}

			goto ERR_EXIT;
		}
        if (result == 0){
			continue;
		}
        if(mConnectSocketFd != events[0].data.fd){
			continue;
		}
        if(mConnectThreadRunning == false){
			break;
		}

        int sfd = 0;
		int retry_cnt;
        for(retry_cnt = 0; retry_cnt < BLKD_MAX_RETRY_NUM; retry_cnt++){
			sfd = accept((int)mConnectSocketFd, NULL, NULL);
			if (sfd < 0){
				continue;
			}
			break;
		}

        if(retry_cnt >= BLKD_MAX_RETRY_NUM){
			goto ERR_EXIT;
		}

        BLKS_SOCKET_CONTROLDATA data;
		ssize_t recvsize = BLKC_ConnectManager::recvControlData(sfd, &data);

        if (recvsize <= 0)
		{
			shutdown( sfd, SHUT_RDWR );
			close(sfd);
			continue;
		}

		LOG_DEBUG("server receive control data socket %s success!", (BLKD_SOCKID_ASYNC == data.sockid) ? "async" : "sync");

        if(BLKD_SOCKID_ASYNC == data.sockid)
		{
			stub_connectManager_p = getConnectManager(&data, &connectionId);
			if (stub_connectManager_p ==NULL)
			{
				LOG_ERROR("stub_connectManager_p = NULL");
				shutdown( sfd, SHUT_RDWR );
				close(sfd);
				continue;
			}

			stub_connectManager_p->init(sfd, BLKD_SOCKID_ASYNC);
		}
        else
		{
			stub_connectManager_p = new BLKC_ConnectManager(sfd, &data);
			if (stub_connectManager_p ==NULL)
			{
				LOG_ERROR("stub_connectManager_p = NULL");
				shutdown( sfd, SHUT_RDWR );
				close(sfd);
				continue;
			}
            
			connectionId = addConnectManager(stub_connectManager_p);
		}

        stub_connectManager_p->start(connectionId, data.sockid);
    }

ERR_EXIT:
    if (mEpollFd != -1){
		int ret = 0;
		BLKD_EINTR_RETRY_CALL(ret = close(mEpollFd), ret == -1);
		mEpollFd = -1;
	}

    return (void*)NULL;
}

ssize_t BLKC_ConnectManager::recvControlData(int sfd, BLKS_SOCKET_CONTROLDATA *data)
{
	unsigned char* buffer = (unsigned char*)data;
	ssize_t size = sizeof(BLKS_SOCKET_CONTROLDATA);
	ssize_t received_size = 0;
	ssize_t rcvsize = 0;

	do {
		do {
			rcvsize = recv(sfd, buffer + received_size, size - received_size, MSG_NOSIGNAL );
			BLKS_SOCKET_CONTROLDATA dataLog;
			memcpy(&dataLog, buffer, sizeof(dataLog));
		} while(( rcvsize == -1) && (errno == EINTR)) ;
		if( rcvsize == 0 ) {
			return rcvsize;
		} else if(rcvsize == -1) {
			return rcvsize;
		} else {
			received_size += rcvsize;
		}
	}while( received_size < size );

	return received_size;
}

BLKC_ConnectManager* BLKC_StubManager::getConnectManager(int connectionId)
{
	ScopeLock lock( *mConnectMngListMutex );

	int element_cnt = (int)mConnectManagerList.size();

	if(connectionId < element_cnt){
		return mConnectManagerList[ connectionId ];
	}else{
		return NULL;
	}
}

BLKC_ConnectManager* BLKC_StubManager::getConnectManager(BLKS_SOCKET_CONTROLDATA *data, int *connectionId)
{
	ScopeLock lock( *mConnectMngListMutex );

	int element_cnt = (int)mConnectManagerList.size();
	int i;
	for(i = 0;i < element_cnt;i++){
		BLKC_ConnectManager* connectManager = mConnectManagerList[ i ];
		if( connectManager != NULL ){
			if( connectManager->matchPeerSysId(data) ){
				*connectionId = i;
				return connectManager;
			}
			else
			{
				LOG_ERROR("system id mot match");
			}
		}
		else
		{
			LOG_ERROR("connectManager = null");
		}
	}

	return NULL;
}

int BLKC_StubManager::addConnectManager(BLKC_ConnectManager* connectManager)
{
	ScopeLock lock( *mConnectMngListMutex );
	
	int element_cnt = (int)mConnectManagerList.size();
	
	int i;
	for(i = 0;i < element_cnt;i++){
		if( mConnectManagerList[ i ] == NULL ){
			mConnectManagerList[ i ] = connectManager;
			break;
		}
	}

	if( i == element_cnt ){
		mConnectManagerList.push_back( connectManager );
	}
	
	return i;
}

void BLKC_StubManager::closeSocket()
{
	if(mConnectSocketFd < 0){
		return;
	}

	shutdown( mConnectSocketFd, SHUT_RDWR );
	int ret = close( mConnectSocketFd );

	mConnectSocketFd = -1;

	if(ret == -1){
		std::string msg;
		// Error::toString(msg);
		// ORG_ASSERT(ret == 0,"ret = %d, errno = %d. %s", ret, errno, msg.c_str());
	}
}

int BLKC_StubManager::getEpollMsec(struct timeval *timeout, struct timespec (&elapsed)[2])
{
	int msec = -1;
	if( NULL != timeout ){
		msec = (int)((timeout->tv_sec * 1000) + (timeout->tv_usec / 1000));
		clock_gettime(CLOCK_MONOTONIC, &elapsed[0]);
	}
	return msec;
}

void BLKC_StubManager::calcEpollElapsed(int nfds, struct timeval *timeout, struct timespec (&elapsed)[2])
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

void BLKC_StubManager::NotifyConnectManagerError(int connectionId, BLKD_SOCKID sockid)
{
	ScopeLock lock( *mConnectMngListMutex );

	int element_cnt = (int)mConnectManagerList.size();

	if(element_cnt <= connectionId){
		return;
	}
	
	mUnlockInstanceManager->endSession(connectionId);

	BLKC_ConnectManager* connect_manager = mConnectManagerList[ connectionId ];
	if( connect_manager == NULL ){
		return;
	}
	else if ( connect_manager->isKillProcessor() == true ) {
		return;
	}

	mConnectManagerList[ connectionId ]->exit();

	Thread *KillThread = new Thread( new ConnectKillProcessor( connect_manager, connectionId, sockid ), "ConKillProTh", DEF_STUB_THREAD_PRIO_CONK);

	if (KillThread == NULL){
		LOG_ERROR("ConKillProTh Create Error.");
		return;
	}
	
	LOG_WARN("Connect error... start kill and reset thread %s!!!", (sockid == BLKD_SOCKID_SYNC) ? "sync" : "async");
	KillThread->setStackSize(DEF_STACK_SIZE_CONKILLPROTH);
	KillThread->run();
}

void BLKC_StubManager::exit()
{
	mConnectThreadRunning = false;

	mConnectThread->join();

	ScopeLock lock( *mConnectMngListMutex );

	unsigned int element_cnt = (unsigned int)mConnectManagerList.size();

	for (unsigned int i = 0; i < element_cnt; i++){
		if(mConnectManagerList[i] != NULL){
			deleteConnectManager( i );
		}
	}
}

void BLKC_StubManager::deleteConnectManager(int connectionId)
{
	ScopeLock lock( *mConnectMngListMutex );

	int element_cnt = (int)mConnectManagerList.size();
	
	if(connectionId < element_cnt){
		delete mConnectManagerList[ connectionId ];
		mConnectManagerList[ connectionId ] = NULL;
	}
}

void BLKC_StubManager::ConnectKillProcessor::run()
{
	pid_t appTid = mConnectManager->getPeerSysTid();

	delete mConnectManager;
		
	BLKC_StubManager::getInstance()->connectKillProcessorEndNotify( mConnectionId );
}

void BLKC_StubManager::connectKillProcessorEndNotify( int connectionId )
{
	ScopeLock lock( *mConnectMngListMutex );
	mConnectManagerList[ connectionId ] = NULL;
}


void BLKC_StubManager::dumnyMethod()
{
}



