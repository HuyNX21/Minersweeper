#include "pch.h"
#include "BLKC_MessageHandlerBase.h"

BLKC_MessageHandlerBase::BLKC_MessageHandlerBase()
{
	mMessageLength = 0;
	mSequenseID = ~0;
	mMessage = NULL;
}

BLKC_MessageHandlerBase::~BLKC_MessageHandlerBase()
{
	
}

void BLKC_MessageHandlerBase::setMessage(SEQUENS_ID_T seqnsId, unsigned char* message, unsigned int message_length)
{
	mSequenseID = seqnsId;
	mMessage = message;
	mMessageLength = message_length;
}

void BLKC_MessageHandlerBase::exec()
{
}

void BLKC_MessageHandlerBase::exec(BLKC_ReceiveThreadContext *context)
{
}


BLKC_MessageHandlerBase* BLKC_MessageHandlerBase::doClone()
{
	return new BLKC_MessageHandlerBase;
}

unsigned char* BLKC_MessageHandlerBase::getPayload()
{
	return mMessage;
}

unsigned int BLKC_MessageHandlerBase::getPayloadLength()
{
	
	return mMessageLength;
	
}

SEQUENS_ID_T BLKC_MessageHandlerBase::getSequenseID()
{
	
	return mSequenseID;
	
}

BLKC_MessageHandlerBase* BLKC_MessageHandlerBase::clone()
{

	BLKC_MessageHandlerBase* ret = doClone();
	return ret;
}

BLKC_ReceiveThreadContext::BLKC_ReceiveThreadContext()
{
}

BLKC_ReceiveThreadContext::~BLKC_ReceiveThreadContext()
{
}