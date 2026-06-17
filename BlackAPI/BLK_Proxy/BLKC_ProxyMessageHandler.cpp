#include "pch.h"
#include "BLKC_ProxyMessageHandler.h"

BLKC_ProxyRequestMessageHandler::BLKC_ProxyRequestMessageHandler(BLKC_ProxyRequestManager& requestManager,BLKC_ProxyManager& proxyManager)
:mProxyRequestManager(requestManager), mProxyManager(proxyManager)
{
}

BLKC_ProxyRequestMessageHandler::~BLKC_ProxyRequestMessageHandler()
{
}

void BLKC_ProxyRequestMessageHandler::exec(BLKC_ReceiveThreadContext* context)
{
	mProxyManager.NotifyReplyMessage(
	                                    getPayload(),
	                                    getPayloadLength(),
	                                    getSequenseID()
	                                  );
}
		
BLKC_MessageHandlerBase* BLKC_ProxyRequestMessageHandler::doClone()
{	
	return new BLKC_ProxyRequestMessageHandler( mProxyRequestManager, mProxyManager );
}

BLKC_ProxyCallBackMessageHandler::BLKC_ProxyCallBackMessageHandler(BLKC_ProxyManager& proxyManager)
:mProxyManager(proxyManager)
{
}


BLKC_ProxyCallBackMessageHandler::~BLKC_ProxyCallBackMessageHandler()
{
}

void BLKC_ProxyCallBackMessageHandler::exec(BLKC_ReceiveThreadContext* context)
{
	mProxyManager.NotifyCallBackMessage(
	                                    getPayload(),
	                                    getPayloadLength(),
	                                    getSequenseID(),
	                                    context
	                                  );
}

BLKC_MessageHandlerBase* BLKC_ProxyCallBackMessageHandler::doClone()
{
	return new BLKC_ProxyCallBackMessageHandler( mProxyManager );
}

BLKC_ProxyObseverNotifyMessageHandler::BLKC_ProxyObseverNotifyMessageHandler(BLKC_ProxyManager& proxyManager)
:mProxyManager(proxyManager)
{
}


BLKC_ProxyObseverNotifyMessageHandler::~BLKC_ProxyObseverNotifyMessageHandler()
{
}

void BLKC_ProxyObseverNotifyMessageHandler::exec(BLKC_ReceiveThreadContext* context)
{
	mProxyManager.NotifyObserverMessage(
	                                    getPayload(),
	                                    getPayloadLength(),
	                                    getSequenseID(),
	                                    context
	                                  );
}

BLKC_MessageHandlerBase* BLKC_ProxyObseverNotifyMessageHandler::doClone()
{
	return new BLKC_ProxyObseverNotifyMessageHandler( mProxyManager );
}

BLKC_ProxyHelthCheckMessageHandler::BLKC_ProxyHelthCheckMessageHandler(BLKC_ProxyManager& proxyManager)
:mProxyManager(proxyManager)
{
}

BLKC_ProxyHelthCheckMessageHandler::~BLKC_ProxyHelthCheckMessageHandler()
{
}

		
void BLKC_ProxyHelthCheckMessageHandler::exec(BLKC_ReceiveThreadContext* context)
{
}
		
BLKC_MessageHandlerBase* BLKC_ProxyHelthCheckMessageHandler::doClone()
{
	return new BLKC_ProxyHelthCheckMessageHandler( mProxyManager );
}

BLKC_ProxyErrorMessageHandler::BLKC_ProxyErrorMessageHandler(BLKC_ProxyManager& proxyManager, BLKD_SOCKID sockid)
:mProxyManager(proxyManager), mSockId(sockid)
{
}

BLKC_ProxyErrorMessageHandler::~BLKC_ProxyErrorMessageHandler()
{
}

void BLKC_ProxyErrorMessageHandler::exec(BLKC_ReceiveThreadContext* context)
{
	mProxyManager.notifyConnectError(mSockId);
}
		
BLKC_MessageHandlerBase* BLKC_ProxyErrorMessageHandler::doClone()
{
	return new BLKC_ProxyErrorMessageHandler( mProxyManager, mSockId );
}

BLKC_ProxyReceiveThreadContext::BLKC_ProxyReceiveThreadContext()
{
}

BLKC_ProxyReceiveThreadContext::~BLKC_ProxyReceiveThreadContext()
{
}