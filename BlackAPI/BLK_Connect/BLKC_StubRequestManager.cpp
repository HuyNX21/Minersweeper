#include "pch.h"

#include "BLKC_StubRequestManager.h"
#include "BLKC_ConnectManager.h"

BLKC_StubRequestManager::BLKC_StubRequestManager( BLKC_ConnectManager& connectManager, pid_t peerSysTid )
 : BLKC_RequestManager( false, peerSysTid ), mConnectManager(connectManager)
{
}


BLKC_StubRequestManager::~BLKC_StubRequestManager()
{
}

void BLKC_StubRequestManager::releaseBuffer(unsigned char *buf)
{
	mConnectManager.releaseBuffer( buf );
}
		

int BLKC_StubRequestManager::sendRequestData( SEQUENS_ID_T seqId, unsigned char* buf, MESSAGE_SIZE_T len, LARGE_PARAM_ARRY* param_arry)
{
	return mConnectManager.sendReqData( seqId, buf, len, param_arry);
}