#include "pch.h"
#include "BLKC_UnmarshalWrapperStub.h"
#include "unmarsahling.h"
#include "BLKC_ConnectManager.h"
#include "BLKC_CallBackContainer.h"

//#define BLK_UNMARSHAL_WRAPPER_STUB_DEBUG (1)
#if defined(BLK_UNMARSHAL_WRAPPER_STUB_DEBUG)
#define DEBUG_PRINT_UNMARSHAL_WRAPPER_STUB std::cout << __FILE__<<":"<<__LINE__<<"    "<<__PRETTY_FUNCTION__ << std::endl;
#else
#define DEBUG_PRINT_UNMARSHAL_WRAPPER_STUB
#endif

void* BLKC_UnmarshalWrapperStub::getInstance(uint32_t instanceId)
{
	DEBUG_PRINT_UNMARSHAL_WRAPPER_STUB

	if ( instanceId == 0 ) {
		return NULL;
	}
	
	void* instance = NULL;

	instance = BLKC_ConnectManager::getObjectPt(instanceId);
	
	return instance;
}

uint32_t BLKC_UnmarshalWrapperStub::getInstanceId(void* instance)
{
	DEBUG_PRINT_UNMARSHAL_WRAPPER_STUB
	
	uint32_t instanceId = 0;
	instanceId = BLKC_ConnectManager::getNewInstanceID(instance);
	
	return instanceId;
}

void* BLKC_UnmarshalWrapperStub::unmarshal( uchar* buf, BLKC_CallbackPointerContainer& data, short* datasize, short num )
{
	DEBUG_PRINT_UNMARSHAL_WRAPPER_STUB

	uint32_t wcbid = 0;
	void* data_pt = unmarshal_unsigned_int32_t( buf, (void*)&wcbid, datasize, num );

	CallBackContainer& callback_container = BLKC_ConnectManager::getCallBackContainer();

	bool b_regist = callback_container.regist( wcbid, data.getSessionID() );
	data.setRegist( b_regist );
	data.setFullCbid( wcbid );

	return data_pt;
}