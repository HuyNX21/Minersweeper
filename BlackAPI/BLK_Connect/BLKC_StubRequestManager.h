#ifndef  __CLASS_BLKC_STUBREQUESTMANAGER_H_
#define  __CLASS_BLKC_STUBREQUESTMANAGER_H_

#include "BLKC_Common.h"
#include "BLKC_RequestManager.h"

class BLKC_ConnectManager;

class BLKC_StubRequestManager : public BLKC_RequestManager
{
    public:
        BLKC_StubRequestManager(BLKC_ConnectManager &connectManager, pid_t peerSysTid);
        virtual ~BLKC_StubRequestManager();
        void releaseBuffer(unsigned char *buf);
        int sendRequestData( SEQUENS_ID_T seqId, unsigned char* buf, MESSAGE_SIZE_T len,  LARGE_PARAM_ARRY* param_arry);

    private:
        BLKC_ConnectManager &mConnectManager;
};

#endif