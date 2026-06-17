#ifndef __CLASS_BLKC_MESSAGEHANDLERBASE_H_
#define __CLASS_BLKC_MESSAGEHANDLERBASE_H_

#include "BLKC_Common.h"

class BLKC_ReceiveThreadContext
{
	public :
		BLKC_ReceiveThreadContext();
		virtual ~BLKC_ReceiveThreadContext();
};

class BLKC_MessageHandlerBase
{
	public :
		BLKC_MessageHandlerBase();
		virtual ~BLKC_MessageHandlerBase();
		void setMessage(SEQUENS_ID_T seqnsId, unsigned char* message, unsigned int message_lenght);
		virtual void exec();
		virtual void exec(BLKC_ReceiveThreadContext* context);
		BLKC_MessageHandlerBase* clone();
	
	protected:
		unsigned char* getPayload();
		unsigned int   getPayloadLength();
		SEQUENS_ID_T   getSequenseID();
		unsigned char* mMessage;
	
	private :
		BLKC_MessageHandlerBase(BLKC_MessageHandlerBase&);
		virtual BLKC_MessageHandlerBase* doClone();
		SEQUENS_ID_T   mSequenseID;
		unsigned int   mMessageLength;

};

#endif