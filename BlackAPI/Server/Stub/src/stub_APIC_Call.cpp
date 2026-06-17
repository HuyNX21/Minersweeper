
#include "stub_method.h"
#include "ClassIDMethodID.h"
#include "BLKC_ProxyManager.h"
#include "BLKC_ConnectManager.h"
#include "BLKC_ProxyCallBackTypedef.h"

#include "Server/Stub/include/stub_APIC_Call.h"
#include "stub_APIC_CallObserver.h"
#include "ObserverAttachDetachStub.h"

void Stub_APIC_Call::dispatch( BLKS_COMMONID* type_id , void* ObjectPt, void* pt )
{
    APIC_Call* pc_APIC_Call = (APIC_Call *)ObjectPt;

    switch( type_id->ClassMethodID )
    {
        case UISEP__APIC_Call__newInstance__1:
			Stub_APIC_Call_newInstance_01(type_id, pc_APIC_Call, pt);
			break;
		case UISEP__APIC_Call__funcCallNoReturn__2:
			Stub_APIC_Call_funcCallNoReturn_02(type_id, pc_APIC_Call, pt);
			break;
		case UISEP__APIC_Call__funcCallReturnBool__3:
			Stub_APIC_Call_funcCallReturnBool_03(type_id, pc_APIC_Call, pt);
			break;
		case UISEP__APIC_Call__req_funcCallback__4:
			Stub_req_funcCallback_04(type_id, pc_APIC_Call, pt);
			break;
		case UISEP__APIC_Call__attachObserver__5:
			Stub_attachObserver_05( type_id , pc_APIC_Call, pt );
			break;
		case UISEP__APIC_Call__detachObserver__6:
			Stub_detachObserver_06( type_id , pc_APIC_Call, pt );
			break;
		case UISEP__APIC_Call__obs_funcCallObserver__7:
			Stub_obs_funcCallObserver_07(type_id, pc_APIC_Call, pt);
			break;
		default:
			LOG_ERROR("ClassMethodID: %d not found", type_id->ClassMethodID);
			// BLKC_ConnectManager::dispatchError( type_id, pt,  __FILE__, __LINE__, __PRETTY_FUNCTION__);
			break;
    }
}

Stub_APIC_Call* Stub_APIC_Call::newInstance()
{
	static Stub_APIC_Call c_Stub_APIC_Call;
	return &c_Stub_APIC_Call;
}

void Stub_APIC_Call::Stub_APIC_Call_newInstance_01( BLKS_COMMONID* type_id , APIC_Call* pc_APIC_Call, void* pt )
{
    // Param.

    RENEW_FUNC_INFO();

	// Base Pre.
	BLKC_StubMethodTemplate::BLKD_StubNewinstance_pre(type_id, pc_APIC_Call, pt, mMarshalDummy, mMarshalDummy, mMarshalDummy, mMarshalDummy, mMarshalDummy, mMarshalDummy );

	// APIC_Call::newInstance().
	pc_APIC_Call = APIC_Call::newInstance( );

	// Base Post.
	BLKC_StubMethodTemplate::BLKD_StubNewinstance_post(type_id, pc_APIC_Call, pt, mMarshalDummy , mMarshalDummy , mMarshalDummy, mMarshalDummy, mMarshalDummy, mMarshalDummy);

}

void Stub_APIC_Call::Stub_APIC_Call_funcCallNoReturn_02( BLKS_COMMONID* type_id , APIC_Call* pc_APIC_Call, void* pt )
{
	// Param.
	bool param = false;

	RENEW_FUNC_INFO();

	// Base Pre.
	BLKC_StubMethodTemplate::BLKD_StubParaType_pre( type_id , pc_APIC_Call , pt,
													param,mMarshalDummy,mMarshalDummy,mMarshalDummy,mMarshalDummy,
													mMarshalDummy,mMarshalDummy,mMarshalDummy,mMarshalDummy,mMarshalDummy,
													mMarshalDummy,mMarshalDummy,mMarshalDummy,mMarshalDummy,mMarshalDummy,
													mMarshalDummy );

	// APIC_Call::funcCallNoReturn().
	pc_APIC_Call->funcCallNoReturn( param );

	// Base Post.
	BLKC_StubMethodTemplate::BLKD_StubParaType_post( type_id , pc_APIC_Call , pt,
													param,mMarshalDummy,mMarshalDummy,mMarshalDummy,mMarshalDummy,
													mMarshalDummy,mMarshalDummy,mMarshalDummy,mMarshalDummy,mMarshalDummy,
													mMarshalDummy,mMarshalDummy,mMarshalDummy,mMarshalDummy,mMarshalDummy,
													mMarshalDummy );
}

bool Stub_APIC_Call::Stub_APIC_Call_funcCallReturnBool_03( BLKS_COMMONID* type_id , APIC_Call* pc_APIC_Call, void* pt )
{
	// Param.
	bool b_ret = false;

	RENEW_FUNC_INFO();

	// Base Pre.
	BLKC_StubMethodTemplate::BLKD_StubParaType_pre( type_id , pc_APIC_Call , pt,
													mMarshalDummy,mMarshalDummy,mMarshalDummy,mMarshalDummy,mMarshalDummy,
													mMarshalDummy,mMarshalDummy,mMarshalDummy,mMarshalDummy,mMarshalDummy,
													mMarshalDummy,mMarshalDummy,mMarshalDummy,mMarshalDummy,mMarshalDummy,
													mMarshalDummy );

	// APIC_Call::funcCallReturnBool().
	b_ret = pc_APIC_Call->funcCallReturnBool( );

	// Base Post.
	BLKC_StubMethodTemplate::BLKD_StubParaType_post( type_id , pc_APIC_Call , pt, b_ret,
													mMarshalDummy,mMarshalDummy,mMarshalDummy,mMarshalDummy,mMarshalDummy,
													mMarshalDummy,mMarshalDummy,mMarshalDummy,mMarshalDummy,mMarshalDummy,
													mMarshalDummy,mMarshalDummy,mMarshalDummy,mMarshalDummy,mMarshalDummy,
													mMarshalDummy );

	return b_ret;
}

void Stub_APIC_Call::Stub_req_funcCallback_04( BLKS_COMMONID* type_id , APIC_Call* pc_APIC_Call, void* pt )
{
	BLKC_SizeArray<uchar> c_SizeArray_0;
	BLKC_CallbackPointerContainer c_CallbackContainer;
	c_CallbackContainer.setSessionID( type_id->SessionID );

	RENEW_FUNC_INFO();
	// Base Pre.
	BLKC_StubMethodTemplate::BLKD_StubParaType_pre( type_id , pc_APIC_Call , pt,
													c_SizeArray_0,c_CallbackContainer,mMarshalDummy,mMarshalDummy,mMarshalDummy,
													mMarshalDummy,mMarshalDummy,mMarshalDummy,mMarshalDummy,mMarshalDummy,
													mMarshalDummy,mMarshalDummy,mMarshalDummy,mMarshalDummy,mMarshalDummy,
													mMarshalDummy );

	// APIC_Call::req_funcCallback().
	if( c_CallbackContainer.getRegist() == true ){
		pc_APIC_Call->req_funcCallback(c_SizeArray_0.getDataptr(),Stub_ans_funcCallback__99);
	}

	// Base Post.
	BLKC_StubMethodTemplate::BLKD_StubParaType_post( type_id, pc_APIC_Call , pt,
													c_SizeArray_0,c_CallbackContainer,mMarshalDummy,mMarshalDummy,mMarshalDummy,
													mMarshalDummy,mMarshalDummy,mMarshalDummy,mMarshalDummy,mMarshalDummy,
													mMarshalDummy,mMarshalDummy,mMarshalDummy,mMarshalDummy,mMarshalDummy,
													mMarshalDummy );
}

void Stub_APIC_Call::Stub_ans_funcCallback__99(bool b_result)
{
	uint32_t callbackID = BLKD_PROXY_CBID__APIC_Call__req_funcCallback__4;

	BLKC_StubMethodTemplate::BLKD_StubCallBack( callbackID, b_result ,mMarshalDummy,mMarshalDummy,mMarshalDummy,mMarshalDummy,mMarshalDummy );
	return;
}

void Stub_APIC_Call::Stub_attachObserver_05( BLKS_COMMONID* type_id , APIC_Call* pc_APIC_Iws, void* pt )
{
	RENEW_FUNC_INFO();

	StubCommon::ObserverAttachDettachFunc<APIC_Call, Stub_APIC_CallObserver, APIC_CallObserver>::attach(type_id, pc_APIC_Iws, pt, &APIC_Call::attachObserver);
}

void Stub_APIC_Call::Stub_detachObserver_06( BLKS_COMMONID* type_id , APIC_Call* pc_APIC_Iws, void* pt )
{
	RENEW_FUNC_INFO();

	StubCommon::ObserverAttachDettachFunc<APIC_Call, Stub_APIC_CallObserver, APIC_CallObserver>::detach(type_id, pc_APIC_Iws, pt, &APIC_Call::detachObserver);
}

void Stub_APIC_Call::Stub_obs_funcCallObserver_07( BLKS_COMMONID* type_id , APIC_Call* pc_APIC_Call, void* pt )
{
	// Param.
	bool b_result = false;

	RENEW_FUNC_INFO();

	// Base Pre.
	BLKC_StubMethodTemplate::BLKD_StubParaType_pre( type_id , pc_APIC_Call , pt,
													b_result,mMarshalDummy,mMarshalDummy,mMarshalDummy,mMarshalDummy,
													mMarshalDummy,mMarshalDummy,mMarshalDummy,mMarshalDummy,mMarshalDummy,
													mMarshalDummy,mMarshalDummy,mMarshalDummy,mMarshalDummy,mMarshalDummy,
													mMarshalDummy );

	// APIC_Call::obs_funcCallObserver().
	pc_APIC_Call->obs_funcCallObserver( b_result );

	// Base Post.
	BLKC_StubMethodTemplate::BLKD_StubParaType_post( type_id , pc_APIC_Call , pt,
													b_result,mMarshalDummy,mMarshalDummy,mMarshalDummy,mMarshalDummy,
													mMarshalDummy,mMarshalDummy,mMarshalDummy,mMarshalDummy,mMarshalDummy,
													mMarshalDummy,mMarshalDummy,mMarshalDummy,mMarshalDummy,mMarshalDummy,
													mMarshalDummy );
}