#include "pch.h"
#include "BLKC_StubApicExecutor.h"

#include "BLKC_ConnectManager.h"
#include "stub_method.h"
#include "stub_class.h"
#include "BLKC_StubMessageHandler.h"
#include "ClassIDMethodID.h"

using namespace std;

const struct BLKC_StubApicExecutor::DispatchFuncTbl BLKC_StubApicExecutor::mDispatchFunctiontbl[] = {
    { UISEP__APIC_Call__BASE__                         , BLKC_StubApicExecutor::dispatchClass<Stub_APIC_Call>  } ,
	{ UISEP__APIC_MineModel__BASE__                    , BLKC_StubApicExecutor::dispatchClass<Stub_APIC_MineModel>  } ,
};

BLKC_StubApicExecutor::BLKC_StubApicExecutor()
{

	for(uint32_t i = 0; i < sizeof( mDispatchFunctiontbl ) / sizeof( mDispatchFunctiontbl[0] );i++){
		mStubApicFuncTable.insert( make_pair( mDispatchFunctiontbl[i].mClassMethodID, mDispatchFunctiontbl[i].mFunction ));
	}
}

BLKC_StubApicExecutor::~BLKC_StubApicExecutor()
{
}

void BLKC_StubApicExecutor::execApicCall(BLKS_COMMONID* type_id, void *pt, BLKC_ReceiveThreadContext* context)
{
    uint32_t class_id = ClassMethodID_toClassID( type_id->ClassMethodID );
	
	STUB_FUNC_TBL::const_iterator it = mStubApicFuncTable.find( class_id );
	STUB_FUNC_TBL::const_iterator it_end = mStubApicFuncTable.end();

    if( it == it_end ){
		// BLKC_ConnectManager::DummyResetData( type_id, pt );
		// BLKC_ConnectManager::dispatchError( type_id, pt,  __FILE__, __LINE__, __PRETTY_FUNCTION__);
		LOG_ERROR("Error call api");
		return;
	}

    void* instance = NULL;

    if ((( type_id->ClassMethodID & 0x0000FFF0) != 0x0000FFF0 ) && ( type_id->InstanceID != BLKD_STATIC_METHOD_ID )){

		instance = BLKC_ConnectManager::getObjectPt( type_id->InstanceID );
		if( instance == NULL )
		{
			// BLKC_ConnectManager::DummyResetData(type_id,pt);
            LOG_ERROR("Error call api");
			return;
		}
	}

    (*it).second( type_id, instance, pt );

}