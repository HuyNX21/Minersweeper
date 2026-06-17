#include "pch.h"
#include "BLKC_ProxyManager.h"
#include "BLKC_ProxyMethodTemplate.h"
#include "BLKC_ProxyCallBackTypedef.h"
#include "BLKC_ProxyMessageHandler.h"

#include "unmarsahling.h"

// APIC_Call::req_funcCallback()
typedef void(*BLKF_PROXY__APIC_Call__req_funcCallback__4)(bool);
// APIC_MineModel::req_openCell()
typedef void(*BLKF_PROXY__APIC_MineModel__req_openCell__3)(std::vector<PointCellOpened>, bool);
// APIC_MineModel::req_toggleFlag()
typedef void(*BLKF_PROXY__APIC_MineModel__req_toggleFlag__7)(int, int, bool, int, int, bool);


void BLKC_ProxyManager::init_Map()
{
    mCallbackFuncArgTbl.clear();

    mCallbackFuncTbl.insert(std::make_pair( BLKD_PROXY_CBID__APIC_Call__req_funcCallback__4, &BLKC_ProxyManager::ANS__APIC_Call__req_funcCallback__4 ) );
	mCallbackFuncTbl.insert(std::make_pair( BLKD_PROXY_CBID__APIC_MineModel__req_openCell__3, &BLKC_ProxyManager::ANS__APIC_MineModel__req_openCell__3 ) );
	mCallbackFuncTbl.insert(std::make_pair( BLKD_PROXY_CBID__APIC_MineModel__req_toggleFlag__7, &BLKC_ProxyManager::ANS__APIC_MineModel__req_toggleFlag__7 ) );
}

void BLKC_ProxyManager::ANS__APIC_Call__req_funcCallback__4( unsigned char *buf, MESSAGE_SIZE_T len, SEQUENS_ID_T seqId )
{
	BLKF_PROXY__APIC_Call__req_funcCallback__4 callbackFP = NULL;
	BLKS_COMMONID type_id;
	uint32_t CallbackID = 0;

	bool arg1 = false;

	BLKC_ProxyMethodTemplate::BLKD_ProxyCallBack_pre( &type_id, &CallbackID, &callbackFP, buf, 
			arg1, mMarshalDummy, mMarshalDummy, mMarshalDummy, mMarshalDummy, mMarshalDummy);
    
	if(callbackFP != NULL) {
		callbackFP( arg1 );
	}

	BLKC_ProxyMethodTemplate::BLKD_ProxyCallBack_post( &type_id, CallbackID, buf, 
			arg1, mMarshalDummy, mMarshalDummy, mMarshalDummy, mMarshalDummy, mMarshalDummy);
}

void BLKC_ProxyManager::ANS__APIC_MineModel__req_openCell__3( unsigned char *buf, MESSAGE_SIZE_T len, SEQUENS_ID_T seqId )
{
	BLKF_PROXY__APIC_MineModel__req_openCell__3 callbackFP = NULL;
	BLKS_COMMONID type_id;
	uint32_t CallbackID = 0;

	std::vector<PointCellOpened> arg1;
	bool arg2 = false;

	BLKC_ProxyMethodTemplate::BLKD_ProxyCallBack_pre( &type_id, &CallbackID, &callbackFP, buf, 
			arg1, arg2, mMarshalDummy, mMarshalDummy, mMarshalDummy, mMarshalDummy);
	
	if(callbackFP != NULL) {
		callbackFP( arg1, arg2 );
	}

	BLKC_ProxyMethodTemplate::BLKD_ProxyCallBack_post( &type_id, CallbackID, buf, 
			arg1, arg2, mMarshalDummy, mMarshalDummy, mMarshalDummy, mMarshalDummy);
}

void BLKC_ProxyManager::ANS__APIC_MineModel__req_toggleFlag__7( unsigned char *buf, MESSAGE_SIZE_T len, SEQUENS_ID_T seqId )
{
	BLKF_PROXY__APIC_MineModel__req_toggleFlag__7 callbackFP = NULL;
	BLKS_COMMONID type_id;
	uint32_t CallbackID = 0;

	int 	arg1 = 0;
	int 	arg2 = 0;
	bool 	arg3 = false;
	int 	arg4 = 0;
	int 	arg5 = 0;
	bool 	arg6 = false;

	BLKC_ProxyMethodTemplate::BLKD_ProxyCallBack_pre( &type_id, &CallbackID, &callbackFP, buf, 
			arg1, arg2, arg3, arg4, arg5, arg6);
	
	if(callbackFP != NULL) {
		callbackFP( arg1, arg2, arg3, arg4, arg5, arg6 );
	}

	BLKC_ProxyMethodTemplate::BLKD_ProxyCallBack_post( &type_id, CallbackID, buf, 
			arg1, arg2, arg3, arg4, arg5, arg6);
}

void BLKC_ProxyManager::callBackExec( unsigned char *buf , MESSAGE_SIZE_T len, SEQUENS_ID_T seqId, void *object_pt, BLKC_ReceiveThreadContext* context )
{
	uint32_t ClassMethodID = 0;
	uint32_t InstanceID = 0;
	uint32_t SessionID = 0;
	uint32_t callBackID = 0;
	uint32_t apic_instanceId = 0;
	unsigned char *workbuf = buf;

	workbuf = (unsigned char*)unmarshal_ClassMethodID( workbuf, &ClassMethodID );
	workbuf = (unsigned char*)unmarshal_InstanceID( workbuf, &InstanceID );
	workbuf = (unsigned char*)unmarshal_SessionID( workbuf, &SessionID );
	workbuf = (unsigned char*)unmarshal_unsigned_int32_t( workbuf, &callBackID );

	uint32_t maskedID = callBackID & BLKD_PROXY_CBID_FRAG;
	CALLBACK_TBL::iterator itr= mCallbackFuncTbl.find( maskedID );
	CALLBACK_TBL::iterator itr_end = mCallbackFuncTbl.end();

	if(itr != itr_end ){

		(this->*(*itr).second)(buf, len, seqId);

		return;
	}
	else{
		LOG_ERROR("Not found CallBack Function. callBackID = %u\n", callBackID);
	}

}