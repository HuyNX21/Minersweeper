#ifndef  __CLASS_BLKC_PROXYREQUESTMANAGER_H_
#define  __CLASS_BLKC_PROXYREQUESTMANAGER_H_

#include "BLKC_RequestManager.h"

class BLKC_ProxyRequestManager : public BLKC_RequestManager
{
    public:
        BLKC_ProxyRequestManager( pid_t connectTid );
        virtual ~BLKC_ProxyRequestManager();
        void releaseBuffer(unsigned char *buf);
		int sendRequestData( uint32_t seqId, unsigned char* buf, MESSAGE_SIZE_T len, LARGE_PARAM_ARRY* param_arry);
};

#endif