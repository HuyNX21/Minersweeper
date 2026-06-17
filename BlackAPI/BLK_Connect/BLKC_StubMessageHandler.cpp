#include "pch.h"
#include "BLKC_StubMessageHandler.h"

BLKC_StubRequestMessageHandler::BLKC_StubRequestMessageHandler(BLKC_ConnectManager& connectManager)
:mConnectManager(connectManager)
{

	
}

BLKC_StubRequestMessageHandler::~BLKC_StubRequestMessageHandler()
{
	
	
}

void BLKC_StubRequestMessageHandler::exec()
{

	mConnectManager.dispatchDo(
	                                    getSequenseID(),
	                                    getPayloadLength(),
	                                    getPayload(),
	                                    NULL
	                                  );
	

}
		
void BLKC_StubRequestMessageHandler::exec(BLKC_ReceiveThreadContext* context)
{

	mConnectManager.dispatchDo(
	                                    getSequenseID(),
	                                    getPayloadLength(),
	                                    getPayload(),
	                                    context
	                                  );
	

}

BLKC_MessageHandlerBase* BLKC_StubRequestMessageHandler::doClone()
{	
	return new BLKC_StubRequestMessageHandler( mConnectManager );
}

BLKC_StubCallBackMessageHandler::BLKC_StubCallBackMessageHandler(BLKC_ConnectManager& connectManager)
:mConnectManager(connectManager)
{
	
}


BLKC_StubCallBackMessageHandler::~BLKC_StubCallBackMessageHandler()
{
	
}

void BLKC_StubCallBackMessageHandler::exec()
{

	mConnectManager.notifyReplyMessage(
	                                    getSequenseID(),
	                                    getPayload(),
	                                    getPayloadLength()
	                                  );


}

void BLKC_StubCallBackMessageHandler::exec(BLKC_ReceiveThreadContext* context)
{

	mConnectManager.notifyReplyMessage(
	                                    getSequenseID(),
	                                    getPayload(),
	                                    getPayloadLength()
	                                  );


}

BLKC_MessageHandlerBase* BLKC_StubCallBackMessageHandler::doClone()
{
	
	return new BLKC_StubCallBackMessageHandler( mConnectManager );
}

BLKC_StubOseverNotifyMessageHandler::BLKC_StubOseverNotifyMessageHandler(BLKC_ConnectManager& connectManager)
:mConnectManager(connectManager)
{
	
}


BLKC_StubOseverNotifyMessageHandler::~BLKC_StubOseverNotifyMessageHandler()
{
	
}

void BLKC_StubOseverNotifyMessageHandler::exec()
{
	mConnectManager.notifyReplyMessage(
	                                    getSequenseID(),
	                                    getPayload(),
	                                    getPayloadLength()
	                                  );

}

void BLKC_StubOseverNotifyMessageHandler::exec(BLKC_ReceiveThreadContext* context)
{
	mConnectManager.notifyReplyMessage(
	                                    getSequenseID(),
	                                    getPayload(),
	                                    getPayloadLength()
	                                  );



}

BLKC_MessageHandlerBase* BLKC_StubOseverNotifyMessageHandler::doClone()
{
	
	return new BLKC_StubOseverNotifyMessageHandler( mConnectManager );
}

BLKC_StubHelthCheckMessageHandler::BLKC_StubHelthCheckMessageHandler(BLKC_ConnectManager& connectManager)
:mConnectManager(connectManager)
{

}

BLKC_StubHelthCheckMessageHandler::~BLKC_StubHelthCheckMessageHandler()
{
}

		
void BLKC_StubHelthCheckMessageHandler::exec()
{

	
}
		
void BLKC_StubHelthCheckMessageHandler::exec(BLKC_ReceiveThreadContext* context)
{

	
}

BLKC_MessageHandlerBase* BLKC_StubHelthCheckMessageHandler::doClone()
{
	
	return new BLKC_StubHelthCheckMessageHandler( mConnectManager );

}


BLKC_StubErrorMessageHandler::BLKC_StubErrorMessageHandler(BLKC_ConnectManager& connectManager)
:mConnectManager(connectManager)
{
}

BLKC_StubErrorMessageHandler::~BLKC_StubErrorMessageHandler()
{
	
}

void BLKC_StubErrorMessageHandler::exec()
{
	mConnectManager.notifyConnectError();
}
		
void BLKC_StubErrorMessageHandler::exec(BLKC_ReceiveThreadContext* context)
{
	mConnectManager.notifyConnectError();
}

BLKC_MessageHandlerBase* BLKC_StubErrorMessageHandler::doClone()
{
	
	return new BLKC_StubErrorMessageHandler( mConnectManager );

}

BLKC_StubTimeOutHandler::BLKC_StubTimeOutHandler(BLKC_ConnectManager& connectManager)
:mConnectManager(connectManager)
{
}

BLKC_StubTimeOutHandler::~BLKC_StubTimeOutHandler()
{
	
}

void BLKC_StubTimeOutHandler::exec()
{

	mConnectManager.sendHelthCheck();

}
		
void BLKC_StubTimeOutHandler::exec(BLKC_ReceiveThreadContext* context)
{

	mConnectManager.sendHelthCheck();

}


BLKC_MessageHandlerBase* BLKC_StubTimeOutHandler::doClone()
{
	
	return new BLKC_StubTimeOutHandler( mConnectManager );

}


BLKC_StubReceiveThreadContext::BLKC_StubReceiveThreadContext()
{
}

BLKC_StubReceiveThreadContext::~BLKC_StubReceiveThreadContext()
{
}