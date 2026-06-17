
#include "pch.h"
#include "unmarsahling.h"
#include "BLKC_UnmarshalWrapperProxy.h"

//#define BLK_UNMARSHAL_WRAPPER_PROXY_DEBUG (1)
#if defined(BLK_UNMARSHAL_WRAPPER_PROXY_DEBUG)
#define DEBUG_PRINT_UNMARSHAL_WRAPPER_PROXY std::cout << __FILE__<<":"<<__LINE__<<"    "<<__PRETTY_FUNCTION__ << std::endl;
#else
#define DEBUG_PRINT_UNMARSHAL_WRAPPER_PROXY
#endif

void* BLKC_UnmarshalWrapperProxy::getInstance(uint32_t instanceId)
{
    DEBUG_PRINT_UNMARSHAL_WRAPPER_PROXY

	if( instanceId == 0 ) {
		return NULL;
	}

	BLKC_ProxyManager* c_proxyMgr = BLKC_ProxyManager::getInstance();
	void* instance = NULL;

	instance = c_proxyMgr->getObject(instanceId);
	
	return instance;
}

void* BLKC_UnmarshalWrapperProxy::unmarshal( uchar* buf, BLKC_CallbackPointerContainer& data, short* datasize, short num )
{
	DEBUG_PRINT_UNMARSHAL_WRAPPER_PROXY
	uint32_t funcId = 0;
	return unmarshal_unsigned_int32_t( buf, (void*)&funcId, datasize, num );
}