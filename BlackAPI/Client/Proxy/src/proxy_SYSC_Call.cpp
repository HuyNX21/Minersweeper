#include "pch.h"
#include "proxy_SYSC_Call.h"
#include "ClassIDMethodID.h"
#include "BLKC_ProxyMethodTemplate.h"
#include "BLKC_MarshalParamaterWrapper.h"
#include "BLKC_ProxyCallBackTypedef.h"
#include "BLKC_CallbackPointerContainer.h"
#include "ObserverAttachDetachProxy.h"

Proxy_SYSC_Call::Proxy_SYSC_Call(){}
Proxy_SYSC_Call::~Proxy_SYSC_Call(){}

// Singleton instance creation for Proxy_SYSC_Call
Proxy_SYSC_Call* Proxy_SYSC_Call::newInstance()
{
    Proxy_SYSC_Call* p_ret = NULL;

    uint32_t ClassMethodID = UISEP__APIC_Call__newInstance__1;

    BLKC_ProxyMethodTemplate::BLKD_ProxyNewinstance_Singleton( ClassMethodID, p_ret, 
			mMarshalDummy, mMarshalDummy, mMarshalDummy, mMarshalDummy, mMarshalDummy, mMarshalDummy );

	return p_ret;
}

// Method without return value implementation
void Proxy_SYSC_Call::funcCallNoReturn(bool b_param)
{
    uint32_t ClassMethodID = UISEP__APIC_Call__funcCallNoReturn__2;

    BLKC_ProxyMethodTemplate::BLKD_ProxyParaType( ClassMethodID, this, 
			b_param, mMarshalDummy, mMarshalDummy, mMarshalDummy, mMarshalDummy, mMarshalDummy,
			mMarshalDummy, mMarshalDummy, mMarshalDummy, mMarshalDummy, mMarshalDummy,
			mMarshalDummy, mMarshalDummy, mMarshalDummy, mMarshalDummy, mMarshalDummy );
}

// Method with return value implementation
bool Proxy_SYSC_Call::funcCallReturnBool()
{
    bool b_ret = 0;

    uint32_t ClassMethodID = UISEP__APIC_Call__funcCallReturnBool__3;

    BLKC_ProxyMethodTemplate::BLKD_ProxyParaType( ClassMethodID, this, b_ret,
			mMarshalDummy, mMarshalDummy, mMarshalDummy, mMarshalDummy, mMarshalDummy, mMarshalDummy,
			mMarshalDummy, mMarshalDummy, mMarshalDummy, mMarshalDummy, mMarshalDummy,
			mMarshalDummy, mMarshalDummy, mMarshalDummy, mMarshalDummy, mMarshalDummy );
    
    return b_ret;
}

// Callback method implementation
void Proxy_SYSC_Call::req_funcCallback(const uchar* puc_ParamString, void(*ans_funcCallback)(bool b_result))
{
    BLKC_SizeArray<uchar> c_SizeArray_1;
    short stringSize = (puc_ParamString != NULL) ? strlen((const char*)puc_ParamString) : 0;
    c_SizeArray_1.setDataptr( (uchar*)puc_ParamString, stringSize );

    uint32_t ClassMethodID  = UISEP__APIC_Call__req_funcCallback__4;
    uint32_t CallbackID     = BLKD_PROXY_CBID__APIC_Call__req_funcCallback__4;

    BLKC_CallbackPointerContainer c_CallbackContainer;
	c_CallbackContainer.setCbid( CallbackID );
	c_CallbackContainer.setFunc( (void*)ans_funcCallback );

    BLKC_ProxyMethodTemplate::BLKD_ProxyParaType( ClassMethodID, this, 
			c_SizeArray_1, c_CallbackContainer, mMarshalDummy, mMarshalDummy, mMarshalDummy, mMarshalDummy,
			mMarshalDummy, mMarshalDummy, mMarshalDummy, mMarshalDummy, mMarshalDummy,
			mMarshalDummy, mMarshalDummy, mMarshalDummy, mMarshalDummy, mMarshalDummy );
}

// Observer method implementation (ans_AppStart)
void Proxy_SYSC_Call::attachObserver(Proxy_APIC_CallObserver* pc_obs)
{
	BLKS_COMMONID id;

	toCommonIDStruct(id, UISEP__APIC_Call__attachObserver__5, this->InstanceID, this->SessionID);
	
	ProxyCommon::attachObserver(&id, pc_obs);
	
	fromCommonIDStruct(id, id.ClassMethodID, this->InstanceID, this->SessionID);
}

void Proxy_SYSC_Call::detachObserver(Proxy_APIC_CallObserver* pc_obs)
{
	BLKS_COMMONID id;

	toCommonIDStruct(id, UISEP__APIC_Call__detachObserver__6, this->InstanceID, this->SessionID);

	ProxyCommon::detachObserver(&id, pc_obs);

	fromCommonIDStruct(id, id.ClassMethodID, this->InstanceID, this->SessionID);
}

void Proxy_SYSC_Call::obs_funcCallObserver( bool b_result )
{
    uint32_t ClassMethodID = UISEP__APIC_Call__obs_funcCallObserver__7;

    BLKC_ProxyMethodTemplate::BLKD_ProxyParaType( ClassMethodID, this, 
            b_result, mMarshalDummy, mMarshalDummy, mMarshalDummy, mMarshalDummy, mMarshalDummy,
            mMarshalDummy, mMarshalDummy, mMarshalDummy, mMarshalDummy, mMarshalDummy,
            mMarshalDummy, mMarshalDummy, mMarshalDummy, mMarshalDummy, mMarshalDummy );
}