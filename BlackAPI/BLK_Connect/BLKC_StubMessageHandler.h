#ifndef __CLASS_BLKC_STUBMESSAGEHANDLER_H_
#define __CLASS_BLKC_STUBMESSAGEHANDLER_H_

#include "BLKC_Common.h"
#include "BLKC_MessageHandlerBase.h"
#include "BLKC_ConnectManager.h"

class BLKC_StubRequestMessageHandler : public BLKC_MessageHandlerBase
{
	public :
		BLKC_StubRequestMessageHandler(BLKC_ConnectManager& connectManager);
		virtual ~BLKC_StubRequestMessageHandler();
		void exec();
		void exec(BLKC_ReceiveThreadContext* context);

	protected:
	private :
		BLKC_MessageHandlerBase* doClone();
		BLKC_ConnectManager& mConnectManager;

};

class BLKC_StubCallBackMessageHandler : public BLKC_MessageHandlerBase
{
	public :
		BLKC_StubCallBackMessageHandler(BLKC_ConnectManager& connectManager);
		virtual ~BLKC_StubCallBackMessageHandler();
		void exec();
		void exec(BLKC_ReceiveThreadContext* context);

	protected:
	private :
		BLKC_MessageHandlerBase* doClone();
		BLKC_ConnectManager& mConnectManager;

};


class BLKC_StubOseverNotifyMessageHandler : public BLKC_MessageHandlerBase
{
	public :
		BLKC_StubOseverNotifyMessageHandler(BLKC_ConnectManager& connectManager);
		virtual ~BLKC_StubOseverNotifyMessageHandler();
		void exec();
		void exec(BLKC_ReceiveThreadContext* context);
	protected:
	private :
		BLKC_MessageHandlerBase* doClone();
		BLKC_ConnectManager& mConnectManager;

};


class BLKC_StubHelthCheckMessageHandler : public BLKC_MessageHandlerBase
{
	public :
		BLKC_StubHelthCheckMessageHandler(BLKC_ConnectManager& connectManager);
		virtual ~BLKC_StubHelthCheckMessageHandler();
		void exec();
		void exec(BLKC_ReceiveThreadContext* context);

	protected:
	private :
		BLKC_MessageHandlerBase* doClone();
		BLKC_ConnectManager& mConnectManager;
	
};

class BLKC_StubErrorMessageHandler : public BLKC_MessageHandlerBase
{
	public :
		BLKC_StubErrorMessageHandler(BLKC_ConnectManager& connectManager);
		virtual ~BLKC_StubErrorMessageHandler();
		void exec();
		void exec(BLKC_ReceiveThreadContext* context);

	protected:
	private :
		BLKC_MessageHandlerBase* doClone();
		BLKC_ConnectManager& mConnectManager;
	
};

class BLKC_StubTimeOutHandler : public BLKC_MessageHandlerBase
{
	public :
		BLKC_StubTimeOutHandler(BLKC_ConnectManager& connectManager);
		virtual ~BLKC_StubTimeOutHandler();
		void exec();
		void exec(BLKC_ReceiveThreadContext* context);

	protected:
	private :
		BLKC_MessageHandlerBase* doClone();
		BLKC_ConnectManager& mConnectManager;

};

class BLKC_StubReceiveThreadContext : public BLKC_ReceiveThreadContext
{
	public :
		BLKC_StubReceiveThreadContext();
		virtual ~BLKC_StubReceiveThreadContext();
		
	public:
		pid_t						mPeerSysTid;

};

#endif