
#include "pch.h"
#include "BLKC_MarshalWrapperStub.h"
#include "marsahling.h"
#include "BLKC_ConnectManager.h"

//#define BLK_MARSHAL_WRAPPER_STUB_DEBUG (1)
#if defined(BLK_MARSHAL_WRAPPER_STUB_DEBUG)
#define DEBUG_PRINT_MARSHAL_WRAPPER_STUB std::cout << __FILE__<<":"<<__LINE__<<"    "<<__PRETTY_FUNCTION__ << std::endl;
#else
#define DEBUG_PRINT_MARSHAL_WRAPPER_STUB
#endif

uint32_t BLKC_MarshalWrapperStub::getInstanceId(void* instance)
{
	DEBUG_PRINT_MARSHAL_WRAPPER_STUB

	uint32_t instanceId = 0;

	instanceId = BLKC_ConnectManager::getNewInstanceID(instance);
	
	return instanceId;
}

uint32_t BLKC_MarshalWrapperStub::findInstanceId(void* instance)
{
	DEBUG_PRINT_MARSHAL_WRAPPER_STUB

	uint32_t instanceId = 0;

	instanceId = BLKC_ConnectManager::findInstanceId(instance);
	
	return instanceId;
}

void* BLKC_MarshalWrapperStub::marshal( uchar* buf, BLKC_CallbackPointerContainer& data, short* datasize, short num )
{
	DEBUG_PRINT_MARSHAL_WRAPPER_STUB

	uint32_t funcId = 0;
	return marshal_unsigned_int32_t( buf, (void*)&funcId, datasize, num );
}