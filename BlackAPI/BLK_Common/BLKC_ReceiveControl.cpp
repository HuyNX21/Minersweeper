#include "pch.h"
#include "BLKC_ReceiveControl.h"

__attribute__((init_priority(101))) MutexLock BLKC_ReceiveControl::mMutex = MutexLock::MUTEX_RECURSIVE_NP;
__attribute__((init_priority(102))) BLKC_ReceiveControl::BLKT_CTRL_MAP_T BLKC_ReceiveControl::mCtrlMap;

BLKC_ReceiveControl::BLKC_ReceiveControl()
{
	mProxy = false;
	mPid = (pid_t)-1;
	mPipefd[0] = -1;
	mPipefd[1] = -1;
	mRunning = false;
	mProcessor = 0;
	mThread =  0;

	int ret = openPipe();
	if(ret != 0) {
		printf("Failed to open pipe\n");
		return;
	}
}

BLKC_ReceiveControl::~BLKC_ReceiveControl()
{
	closePipe();
}

BLKC_ReceiveControl::Processor::Processor(BLKC_ReceiveControl*pReceiveControl)
{
	mReceiveControl = pReceiveControl;
}

BLKC_ReceiveControl::Processor::~Processor()
{
}

int BLKC_ReceiveControl::openPipe()
{
	int ret = pipe(mPipefd);
	if(ret != 0) {
		mPipefd[0] = -1;
		mPipefd[1] = -1;
		printf("Failed to open pipe\n");
		return -1;
	}

	ret = fcntl( mPipefd[0], F_SETFD, FD_CLOEXEC );
	if(ret == -1) {
		printf("Failed to set pipefd[0] flags\n");
		closePipe();
		return -1;
	}

	ret = fcntl( mPipefd[1], F_SETFD, FD_CLOEXEC );
	if(ret == -1) {
		printf("Failed to set pipefd[1] flags\n");
		closePipe();
		return -1;
	}

	return 0;
}

void BLKC_ReceiveControl::closePipe()
{
	if(mPipefd[1] != -1) {
		close(mPipefd[1]);
		mPipefd[1] = -1;
	}
	if(mPipefd[0] != -1) {
		close(mPipefd[0]);
		mPipefd[0] = -1;
	}
}

BLKC_ReceiveControl*  BLKC_ReceiveControl::newInstance(pid_t peer_pid, int sfd, BLKC_ReceiveControlObserver* manager, bool bPoxy)
{
	ScopeLock lock( BLKC_ReceiveControl::mMutex );

	BLKC_ReceiveControl* pReceiveControl = NULL;
	BLKS_CTRL_T data;

	BLKT_CTRL_MAP_T::iterator it = mCtrlMap.find( peer_pid );
	BLKT_CTRL_MAP_T::iterator it_end = mCtrlMap.end();
	if(it == it_end) {
		data.reference = 1;
		data.pReceiveControl = pReceiveControl = new BLKC_ReceiveControl;
		mCtrlMap.insert(  BLKT_CTRL_MAP_T::value_type( peer_pid, data ) );

		pReceiveControl->start(bPoxy,peer_pid);

	} else {
		BLKS_CTRL_T& rData = (*it).second;
		rData.reference++;
		pReceiveControl = rData.pReceiveControl;
	}

	FdInfo fdinfo;
	fdinfo.mManager = manager;
	fdinfo.m_FdState = BLKD_RXCTRL_STOP;

	pReceiveControl->mFDMap.insert( BLKT_FD_MAP_T::value_type( sfd, fdinfo ) );
	return pReceiveControl;
}

void BLKC_ReceiveControl::start(bool mode,pid_t pid)
{
	if(mRunning) {
		return;
	}
	mProxy = mode;
	mPid = pid;

	mProcessor = new Processor( this );

	if(mode) {
		mThread = new Thread(mProcessor, "ProxyRxCtrlTh", DEF_PROXY_RECV_CTRL_THREAD_PRIO_RX);
		mThread->setStackSize(DEF_STACK_SIZE_PROXYRCVTH);
	} else {
		mThread = new Thread(mProcessor, "SrvRxCtrlTh", DEF_STUB_RECV_CTRL_THREAD_PRIO);
		mThread->setStackSize(DEF_STACK_SIZE_STUBRCVCTRLTH);
	}

	mRunning = true;
	mThread->run();
}

void BLKC_ReceiveControl::Processor::run()
{
	mReceiveControl->mainLoop();
}

// Mục đích tổng quát
// Đây l�? vòng lặp trung tâm của h�? thống nhận dữ liệu. Nó dùng epoll đ�? theo dõi nhiều socket cùng lúc v�? dispatch công việc khi có data đến.
// Lý do rebuild mỗi vòng: sau khi xử lý xong một socket, state của nó đổi th�?nh STOP �? vòng sau sẽ không đăng ký lại cho đến khi được START tr�? lại.
void BLKC_ReceiveControl::mainLoop()
{
	LOG_DEBUG("start loop receive control...");
	int sfd = -1;
	uint32_t infomation;
	pthread_t threadid;
	int	nsfd = 0;
	int fdMax = 0;
	int epollfd = -1;
	int ret = -1;
	int n = 0;
	std::vector<struct epoll_event> events;
	bool ending = false;
	uint32_t num = 0;

	while(mRunning == true)
	{
		if (epollfd != -1) {
			// close epoll cũ (nếu có)
			BLKD_EINTR_RETRY_CALL3(	ret = close(epollfd),
									ret == -1,
									LOG_ERROR("mainLoop close ") );
			epollfd = -1;
		}

		BLKD_EINTR_RETRY_CALL3(	epollfd = epoll_create1(EPOLL_CLOEXEC),
								epollfd == -1,
								LOG_ERROR("error epoll_create1") );
		
		struct epoll_event event = {(EPOLLIN | EPOLLRDHUP), reinterpret_cast<void*>(mPipefd[0])};

		// đăng ký event EPOLLIN của mPipefd[0] v�?o epoll
		BLKD_EINTR_RETRY_CALL3(	ret = epoll_ctl(epollfd, EPOLL_CTL_ADD, mPipefd[0], &event),
								ret == -1,
								LOG_ERROR("error epoll_ctl") );

		if(ending == true) {
		} else {
			// đăng ký tất cả socket đang active v�?o epoll
			fdMax = getFdSet(epollfd);
		}

		if (events.size() <= (size_t)fdMax) {
			events.resize(fdMax+1);
		}

		do {
			// ch�? event từ bất kỳ fd n�?o
			LOG_DEBUG("epoll wait receive event in socket");
			nsfd = epoll_wait(epollfd, events.data(), (int)events.size(), -1);
			LOG_DEBUG("epoll release receive event in socket");
		} while((nsfd == -1) && (errno == EINTR) );

		if (nsfd == -1){}

		for(n = 0; n < nsfd; ++n) {
			if (mPipefd[0] == events[n].data.fd) {
				break;
			}
		}

		if(n < nsfd){
			// Nếu có event từ pipe �? đọc lệnh điều khiển:
			getRxControl(&sfd, &threadid, &infomation);

			// RXCTRL_START		Bật socket �? đăng ký v�?o epoll vòng sau
			// RXCTRL_STOP		Tắt socket �? không nhận data
			// RXCTRL_END		Xóa socket khỏi h�? thống
			// RXCTRL_UPDATE	Nếu socket đang WAIT �? chuyển v�? START
			// RXCTRL_ENDREQ	Bắt đầu shutdown, set ending=true
			switch(infomation) {
			case BLKD_RXCTRL_END:
				changeFdState(sfd,BLKD_RXCTRL_END);
				break;
			case BLKD_RXCTRL_STOP:
				changeFdState(sfd,BLKD_RXCTRL_STOP);
				break;

			case BLKD_RXCTRL_START:
				changeFdState(sfd,BLKD_RXCTRL_START);
				break;

			case BLKD_RXCTRL_UPDATE:
				notifyRxUpdate(sfd);
				break;

			case BLKD_RXCTRL_ENDREQ:
				// Nếu ending = true: kiểm tra còn thread n�?o đang xử lý không (getNoIdleState()), nếu hết thì thoát vòng lặp.
				ending = true;
				break;
			default:
				break;
			}
		}

		if(ending == true) {
			num = getNoIdleState();
			if(num == 0) {
				break;
			}
			continue;
		}

		Runnable* mReceiver;

		for(int n = 0; n < nsfd; ++n) {
			if (mPipefd[0] == events[n].data.fd) continue;

			FdInfo* pFdInfo = 0;
			ScopeLock lock(BLKC_ReceiveControl::mMutex);
			// tìm fd trong mFDMap
			BLKT_FD_MAP_T::iterator it = mFDMap.find(events[n].data.fd);
			BLKT_FD_MAP_T::iterator it_end = mFDMap.end();

			if(it != it_end) {
				sfd = it->first;
				pFdInfo = &(it->second);

				BLKD_SOCKID sockid;
				// getWaitThreadInfo() �? lấy ReceiveProcessor đang idle cho socket n�?y
				// Nếu getWaitThreadInfo() không tìm được thread idle �? mReceiver = NULL �? NotifyReceiveControl() sẽ tạo thread tạm thời (ReceiveProcessorTemporary) thay vì dùng semaphore.
				// Đây l�? fallback khi thread pool bận hết.
				mReceiver = getWaitThreadInfo(sfd, pFdInfo, &sockid);
				if(BLKD_RXCTRL_WAIT != pFdInfo->m_FdState) {
					LOG_INFO("Notify receive - socketFd: %d - socketId: %s", sfd, (sockid == 0) ? "Type sync" : "Type async");
					pFdInfo->mManager->NotifyReceiveControl(mReceiver, sockid);

					if(pFdInfo->m_FdState != BLKD_RXCTRL_END) {
						// đổi state = STOP  �? ngăn nhận thêm event cho đến khi xử lý xong
						pFdInfo->m_FdState = BLKD_RXCTRL_STOP;
					}
				}
			}
		}

		LOG_DEBUG("reset loop receive!!!");
	}

	if (epollfd != -1) {
		BLKD_EINTR_RETRY_CALL3(	ret = close(epollfd),
								ret == -1,
								LOG_ERROR("error close") );
		epollfd = -1;
	}

	mRunning = false;
}

void BLKC_ReceiveControl::getRxControl(int* pSocketFd, pthread_t* pThreadId, uint32_t* pInfomation)
{
	*pSocketFd = -1;
	*pThreadId = -1;
	*pInfomation = -1;

	BLKS_CONTROLDATA data;

	ssize_t size = 0;
	do {
		size = read(mPipefd[0], &data, sizeof(data));
		LOG_DEBUG("read Rx with sfd: %d", data.sfd);
	} while((size == -1) && (errno == EINTR));
	if(size == -1) {

		return;
	} else if(size != sizeof(data)) {

		return;
	} 

	*pSocketFd = data.sfd;
	*pThreadId = data.threadId;;
	*pInfomation = data.infomation;
	return;
}

void BLKC_ReceiveControl::changeFdState(int sfd, uint32_t ul_State)
{
	ScopeLock lock( BLKC_ReceiveControl::mMutex );

	BLKT_FD_MAP_T::iterator it = mFDMap.find( sfd );
	BLKT_FD_MAP_T::iterator it_end = mFDMap.end();
	if(it == it_end) {
		return;
	}
	FdInfo& rInfo = (*it).second;
	if(rInfo.m_FdState != BLKD_RXCTRL_END) {
		rInfo.m_FdState = ul_State;
	}
}

int  BLKC_ReceiveControl::getFdSet(int epollfd)
{
	int fdMax = 0;

	ScopeLock lock( BLKC_ReceiveControl::mMutex );

	FdInfo* pInfo = 0;
	int sfd = 0;
	int ret = 0;

	BLKT_FD_MAP_T::iterator it 		= mFDMap.begin();
	BLKT_FD_MAP_T::iterator it_end	= mFDMap.end();

	for(; it != it_end;++ it ) {
		sfd = (*it).first ;
		pInfo = &(it->second);
		LOG_DEBUG("get socket fd %d active with state: %s",sfd , convertRxControlToString(pInfo->m_FdState) );
		// duyệt mFDMap, ch�? đăng ký socket có state == START
		if(pInfo->m_FdState == BLKD_RXCTRL_START) {
			LOG_DEBUG("assign fd to epoll event ~ fd: %d", sfd);
			struct epoll_event event = {(EPOLLIN | EPOLLRDHUP), reinterpret_cast<void*>(sfd)};
			BLKD_EINTR_RETRY_CALL3(	ret = epoll_ctl(epollfd, EPOLL_CTL_ADD, sfd, &event),
									ret == -1,
									LOG_ERROR("error epoll_ctl \n") );
			fdMax++;
		}
	}
	return fdMax;
}

void BLKC_ReceiveControl::notifyRxUpdate(int sfd)
{
	ScopeLock lock(BLKC_ReceiveControl::mMutex);

	ReciveThreadInfo* pInfo = NULL;
	{
		BLKT_RECEIVE_THREAD_MAP_T::iterator it = mThreadMap.begin();
		BLKT_RECEIVE_THREAD_MAP_T::iterator it_end = mThreadMap.end();
		for(; it != it_end; ++it ) {
			//threadId = (*it).first ;
			pInfo = &(it->second);
			if(pInfo->mSfd == sfd) {
				break;
			}else {
				pInfo = NULL;
			}
		}
		if(NULL == pInfo) {
			return;
		}
	}
	if(MODE_RECEIVE != pInfo->mMode) {
		return;
	}

	FdInfo* pFdInfo = NULL;
	{
		BLKT_FD_MAP_T::iterator it = mFDMap.find(sfd);
		BLKT_FD_MAP_T::iterator it_end = mFDMap.end();
		if(it == it_end) {
			return;
		}
		pFdInfo = &(it->second);
	}
	if(BLKD_RXCTRL_WAIT == pFdInfo->m_FdState) {
		pFdInfo->m_FdState = BLKD_RXCTRL_START;
	}
}

uint32_t BLKC_ReceiveControl::getNoIdleState()
{
	uint32_t num = 0;
	ScopeLock lock(BLKC_ReceiveControl::mMutex);


	BLKT_RECEIVE_THREAD_MAP_T::iterator it = mThreadMap.begin();
	BLKT_RECEIVE_THREAD_MAP_T::iterator it_end = mThreadMap.end();
	for(; it != it_end;++ it ) {
		ReciveThreadInfo& rInfo = (*it).second;
		if((rInfo.mMode == MODE_RECEIVE) || (rInfo.mMode == MODE_RECEIVEASYNC)) {
			if(rInfo.mState != STATE_IDLE) {
				num++;
			}
		} else {
			num++;
		}
	}
	return num;
}

Runnable* BLKC_ReceiveControl::getWaitThreadInfo(int sfd, FdInfo* pFdInfo, BLKD_SOCKID* pSockId)
{
	ReciveThreadInfo* pInfo = 0;
	*pSockId = BLKD_SOCKID_INVALID;

	ScopeLock lock(BLKC_ReceiveControl::mMutex);

	BLKT_RECEIVE_THREAD_MAP_T::iterator it = mThreadMap.begin();
	BLKT_RECEIVE_THREAD_MAP_T::iterator it_end = mThreadMap.end();
	for(; it != it_end;++ it ) {
		pInfo = &(it->second);
		if((pInfo->mMode == MODE_RECEIVE) || (pInfo->mMode == MODE_RECEIVEASYNC)) {
			if(pInfo->mSfd == sfd) {
				LOG_DEBUG("get sfd pending : %d - state: %s", pInfo->mSfd, convertReceiveThreadStateToString(pInfo->mState));
				*pSockId = (pInfo->mMode == MODE_RECEIVE) ? BLKD_SOCKID_SYNC : BLKD_SOCKID_ASYNC;
				if(pInfo->mState == STATE_IDLE) {
					pInfo->mState = STATE_EXEC;
					return pInfo->mReceiver;
				}else if(pInfo->mMode == MODE_RECEIVE) {
					pFdInfo->m_FdState = BLKD_RXCTRL_WAIT;
					return NULL;
				}
			}
		}
	}
	return NULL;
}

void BLKC_ReceiveControl::addReceiveThreadInfo(pthread_t threadId, 
				enum E_RECEIVE_THREAD_STATE state,
				enum E_RECEIVE_THREAD_MODE mode,
				BLKC_ReceiveControlObserver* manager,
				Runnable* receiver,	int sfd)
{
	ScopeLock lock(BLKC_ReceiveControl::mMutex);
	{
		ReciveThreadInfo info;
		info.mState = state;
		info.mMode = mode;
		info.mManager = manager; 
		info.mReceiver = receiver; 
		info.mSfd = sfd;
		info.mSeqId = 0;
		mThreadMap.insert( BLKT_RECEIVE_THREAD_MAP_T::value_type( threadId,info ));
	}
	
}

void BLKC_ReceiveControl::setRxControl(int socketFd, uint32_t infomation)
{
	BLKS_CONTROLDATA data;
	data.sfd = socketFd;
	data.threadId = pthread_self();
	data.infomation = infomation;

	if(mPipefd[0] == -1) {
		return;
	}

	ssize_t size = 0;
	do {
		size = write(mPipefd[1],&data,sizeof(data));
		LOG_DEBUG("write Rx with sfd: %d", data.sfd);
	} while((size == -1) && (errno == EINTR));
	if(size == -1) {

	} else if(size != sizeof(data)) {

	}
	return;
}

BLKD_SOCKID BLKC_ReceiveControl::getSockId(pthread_t threadId)
{
	ScopeLock lock(BLKC_ReceiveControl::mMutex);

	if(0 == threadId) {
		threadId = pthread_self();
	}

	BLKT_RECEIVE_THREAD_MAP_T::iterator it = mThreadMap.find( threadId );
	BLKT_RECEIVE_THREAD_MAP_T::iterator it_end = mThreadMap.end();
	if(it == it_end) {
		if( mProxy ) {
			return BLKD_SOCKID_SYNC;
		} else {
			return BLKD_SOCKID_ASYNC;
		}
	} else {
		if(MODE_RECEIVE == (*it).second.mMode) {
			return BLKD_SOCKID_SYNC;
		} else {
			return BLKD_SOCKID_ASYNC;
		}
	}
}

void BLKC_ReceiveControl::changeState(pthread_t threadId, enum E_RECEIVE_THREAD_STATE state)
{
	ScopeLock lock(BLKC_ReceiveControl::mMutex);

	BLKT_RECEIVE_THREAD_MAP_T::iterator it = mThreadMap.find( threadId );
	BLKT_RECEIVE_THREAD_MAP_T::iterator it_end = mThreadMap.end();
	if(it == it_end) {
		return;
	}
	ReciveThreadInfo& rInfo = (*it).second;
	rInfo.mState = state;
}

void BLKC_ReceiveControl::deleteReceiveThreadInfo(pthread_t threadId)
{
	ScopeLock lock(BLKC_ReceiveControl::mMutex);


	BLKT_RECEIVE_THREAD_MAP_T::iterator it = mThreadMap.find( threadId );
	BLKT_RECEIVE_THREAD_MAP_T::iterator it_end = mThreadMap.end();
	if(it == it_end) {
		return;
	}
	mThreadMap.erase( threadId );
}

void BLKC_ReceiveControl::setSequenceId(SEQUENS_ID_T seqId)
{
	pthread_t threadId = pthread_self();

	ScopeLock lock(BLKC_ReceiveControl::mMutex);


	BLKT_RECEIVE_THREAD_MAP_T::iterator it = mThreadMap.find( threadId );
	BLKT_RECEIVE_THREAD_MAP_T::iterator it_end = mThreadMap.end();
	if(it == it_end) {
		return;
	}
	ReciveThreadInfo& rInfo = (*it).second;
	rInfo.mSeqId = seqId;
}

SEQUENS_ID_T BLKC_ReceiveControl::getSequenceId()
{
	pthread_t threadId = pthread_self();

	ScopeLock lock(BLKC_ReceiveControl::mMutex);

	BLKT_RECEIVE_THREAD_MAP_T::iterator it = mThreadMap.find( threadId );
	BLKT_RECEIVE_THREAD_MAP_T::iterator it_end = mThreadMap.end();
	if(it == it_end) {
		return 0;
	}
	ReciveThreadInfo& rInfo = (*it).second;
	return rInfo.mSeqId;
}

void BLKC_ReceiveControl::exitAndDeleteInstance(pid_t peer_pid, int sfd[])
{

	BLKC_ReceiveControl* pReceiveControl = 0;
	int32_t reference = 0;
	{
		ScopeLock lock( BLKC_ReceiveControl::mMutex );

		BLKT_CTRL_MAP_T::iterator it = mCtrlMap.find( peer_pid );
		BLKT_CTRL_MAP_T::iterator it_end = mCtrlMap.end();
		if(it == it_end) {
			return;
		}
		pReceiveControl = it->second.pReceiveControl;
		reference = it->second.reference;
	}

	BLKD_SOCKID sockid;
	for(sockid = 0; sockid < BLKD_SOCKID_MAX; sockid++) {
		pReceiveControl->exitThreadForFd(sfd[sockid]);
	}

	if((reference == 1) || (reference == BLKD_SOCKID_MAX)) {
		pReceiveControl->exit();
	}

	ScopeLock lock( BLKC_ReceiveControl::mMutex );

	BLKT_CTRL_MAP_T::iterator it = mCtrlMap.find( peer_pid );
	BLKT_CTRL_MAP_T::iterator it_end = mCtrlMap.end();
	if(it == it_end) {
		return;
	}

	BLKS_CTRL_T& rData = (*it).second;

	pReceiveControl = rData.pReceiveControl;

	for(sockid = 0; sockid < BLKD_SOCKID_MAX; sockid++) {
		rData.reference--;

		pReceiveControl->mFDMap.erase( sfd[sockid] );

		pReceiveControl->deleteThreadInfoForFd( sfd[sockid] );
	}

	if(rData.reference == 0) {
		pReceiveControl->exit();

		delete pReceiveControl;
		mCtrlMap.erase( it );
	}
}

void BLKC_ReceiveControl::exit()
{
	if(mRunning) {
		setRxControl(-1,BLKD_RXCTRL_ENDREQ);
		while(mRunning == true){
			Thread::nanosleepThread(0, 100*1000);	// 100ms wait
		}

		if(mProxy) {
			// BLKC_LogMessage::DestroyProxyComponentTable( BLKC_LogMessage::Component().ProxyPid( mPid ) );
		} else {
			// BLKC_LogMessage::DestroyStubComponentTable( BLKC_LogMessage::Component().ProxyPid( mPid ) );
		}

	}
}

void BLKC_ReceiveControl::exitThreadForFd(int sfd)
{
	ReciveThreadInfo* pInfo = 0;
	uint32_t num = 0;

	for(;;) {
		num = 0;
		{
			ScopeLock lock(BLKC_ReceiveControl::mMutex);
			num = 0;
			BLKT_RECEIVE_THREAD_MAP_T::iterator it = mThreadMap.begin();
			BLKT_RECEIVE_THREAD_MAP_T::iterator it_end = mThreadMap.end();
			for(; it != it_end;++ it ) {
				//threadId = (*it).first ;
				pInfo = &(it->second);
				if((pInfo->mMode == MODE_RECEIVE) || (pInfo->mMode == MODE_RECEIVEASYNC)) {
					;
				} else {
					if(pInfo->mSfd == sfd) {
						num++;
					}
				}
			}
		}
		if(num == 0) {
			break;
		}
		Thread::nanosleepThread(0, 100*1000);	// 100ms wait
	}
}

void BLKC_ReceiveControl::deleteThreadInfoForFd(int sfd)
{
	ScopeLock lock(BLKC_ReceiveControl::mMutex);


	BLKT_RECEIVE_THREAD_MAP_T::iterator it;
	BLKT_RECEIVE_THREAD_MAP_T::iterator it_end;

	it = mThreadMap.begin();
	it_end = mThreadMap.end();
	while (it != it_end) {
		if(it->second.mSfd == sfd) {
			mThreadMap.erase( it++ );
		} else {
			it++;
		}
	}
}