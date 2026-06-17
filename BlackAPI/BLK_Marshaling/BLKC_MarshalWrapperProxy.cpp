
#include "pch.h"
#include "marsahling.h"
#include "BLKC_MarshalWrapperProxy.h"

//#define BLK_MARSHAL_WRAPPER_PROXY_DEBUG (1)
#if defined(BLK_MARSHAL_WRAPPER_PROXY_DEBUG)
#define DEBUG_PRINT_MARSHAL_WRAPPER_PROXY std::cout << __FILE__<<":"<<__LINE__<<"    "<<__PRETTY_FUNCTION__ << std::endl;
#else
#define DEBUG_PRINT_MARSHAL_WRAPPER_PROXY
#endif

uint32_t BLKC_MarshalWrapperProxy::getInstanceId(void* instance)
{
    DEBUG_PRINT_MARSHAL_WRAPPER_PROXY

    BLKC_ProxyManager* c_proxyMgr = BLKC_ProxyManager::getInstance();
	uint32_t instanceId = 0;

	instanceId = c_proxyMgr->getInstanceId(instance);
	
	return instanceId;
}

void* BLKC_MarshalWrapperProxy::marshal( uchar* buf, BLKC_CallbackPointerContainer& data, short* datasize, short num )
{
	DEBUG_PRINT_MARSHAL_WRAPPER_PROXY

	BLKC_ProxyManager* c_proxyMgr = BLKC_ProxyManager::getInstance();
	uint32_t funcId = 0;

	funcId =  c_proxyMgr->getCallBackFPId( data.getCbid() );
	c_proxyMgr->setCallBackFP( funcId, data.getFunc() );
	data.setFullCbid( funcId );
    
	return marshal_unsigned_int32_t( buf, (void*)&funcId, datasize, num );
}