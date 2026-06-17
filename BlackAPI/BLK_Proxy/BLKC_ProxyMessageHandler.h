#ifndef __CLASS_BLKC_PROXYMESSAGEHANDLER_H_
#define __CLASS_BLKC_PROXYMESSAGEHANDLER_H_

#include "BLKC_ProxyManager.h"
#include "BLKC_Common.h"
#include "BLKC_MessageHandlerBase.h"
#include "BLKC_ProxyRequestManager.h"

class BLKC_ProxyManager;
class BLKC_ProxyRequestManager;

class BLKC_ProxyRequestMessageHandler : public BLKC_MessageHandlerBase	
{
	public :
	
		BLKC_ProxyRequestMessageHandler(BLKC_ProxyRequestManager& requestManager,BLKC_ProxyManager& proxyManager);

		virtual ~BLKC_ProxyRequestMessageHandler();

		void exec(BLKC_ReceiveThreadContext* context);
		
	
	protected:

	private :

		BLKC_MessageHandlerBase* doClone();

		BLKC_ProxyRequestManager& mProxyRequestManager;

		BLKC_ProxyManager& mProxyManager;
	
};

class BLKC_ProxyCallBackMessageHandler : public BLKC_MessageHandlerBase
{
	public :
	
		BLKC_ProxyCallBackMessageHandler(BLKC_ProxyManager& proxyManager);

		virtual ~BLKC_ProxyCallBackMessageHandler();

		void exec(BLKC_ReceiveThreadContext* context);
	
	protected:
	
	private :
		BLKC_MessageHandlerBase* doClone();
		
		BLKC_ProxyManager& mProxyManager;

	
	
};

class BLKC_ProxyObseverNotifyMessageHandler : public BLKC_MessageHandlerBase
{
	public :
	
		BLKC_ProxyObseverNotifyMessageHandler(BLKC_ProxyManager& proxyManager);

		virtual ~BLKC_ProxyObseverNotifyMessageHandler();

		void exec(BLKC_ReceiveThreadContext* context);
	protected:

	private :
		BLKC_MessageHandlerBase* doClone();
		
		BLKC_ProxyManager& mProxyManager;

	
	
};

class BLKC_ProxyHelthCheckMessageHandler : public BLKC_MessageHandlerBase
{
	public :
	
		BLKC_ProxyHelthCheckMessageHandler(BLKC_ProxyManager& proxyManager);

		virtual ~BLKC_ProxyHelthCheckMessageHandler();

		void exec(BLKC_ReceiveThreadContext* context);
	
	protected:

	
	private :
		BLKC_MessageHandlerBase* doClone();

		BLKC_ProxyManager& mProxyManager;
		
	
};

class BLKC_ProxyErrorMessageHandler : public BLKC_MessageHandlerBase
{
	public :
	
		BLKC_ProxyErrorMessageHandler(BLKC_ProxyManager& proxyManager, BLKD_SOCKID sockid); // 2018/08/24 APF AR.1026585 BlackAPI動的スレッド生成見直し（PaperCut対応）.

		virtual ~BLKC_ProxyErrorMessageHandler();

		void exec(BLKC_ReceiveThreadContext* context);
	
	protected:

	private :
		BLKC_MessageHandlerBase* doClone();

		BLKC_ProxyManager& mProxyManager;
		
		BLKD_SOCKID mSockId;
	
};


class BLKC_ProxyReceiveThreadContext : public BLKC_ReceiveThreadContext
{
	public :
	
		BLKC_ProxyReceiveThreadContext();

		virtual ~BLKC_ProxyReceiveThreadContext();
	
	public:
	
		// BLKC_WatchNotifyContext	mWatchNotifyContext;
};

#endif