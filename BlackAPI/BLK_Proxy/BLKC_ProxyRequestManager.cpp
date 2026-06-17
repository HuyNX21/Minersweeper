#include "pch.h"
#include "BLKC_ProxyManager.h"

class BLKC_ProxyManager;

#include "BLKC_ProxyRequestManager.h"

BLKC_ProxyRequestManager::BLKC_ProxyRequestManager( pid_t connectTid )
 : BLKC_RequestManager( true, connectTid )
{
}

BLKC_ProxyRequestManager::~BLKC_ProxyRequestManager()
{
}

void BLKC_ProxyRequestManager::releaseBuffer(unsigned char *buf)
{
	
	BLKC_ProxyManager::getInstance()->releaseBuffer( buf );
}

int BLKC_ProxyRequestManager::sendRequestData( uint32_t seqId, unsigned char* buf, MESSAGE_SIZE_T len, LARGE_PARAM_ARRY* param_arry)
{
	BLKC_ProxyManager::getInstance()->sendRequestData( seqId, buf, len, param_arry);
	return 0;
}

