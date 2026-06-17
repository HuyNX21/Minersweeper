#include "pch.h"
#include "Observable_APIC_CallObserver.h"
#include "ClassIDMethodIDObservable.h"
#include "BLKC_Common.h"
#include "BLKC_ProxyManager.h"
#include "BLKC_ProxyMethodTemplate.h"
#include "marsahling.h"
#include "unmarsahling.h"

Observable_APIC_CallObserver::Observable_APIC_CallObserver()
{
    static const FUNC_CONTAINER::FUNC_TBL_T tbl[] = { 
		{ UISEP__APIC_CallObserver__obs_funcCallObserver__1, &Observable_APIC_CallObserver::obs_funcCallObserver },
    };
	mFuncPtContainer.registFunction( tbl, FUNC_TBL_LENGTH(tbl) );
}

void Observable_APIC_CallObserver::doExec( BLKS_COMMONID* type_id , void* ObjectPt, void* pt )
{
	mFuncPtContainer.exec( this, type_id, ObjectPt, pt );
}

void Observable_APIC_CallObserver::obs_funcCallObserver( BLKS_COMMONID* type_id, Proxy_APIC_CallObserver* ObjectPt, void* pt )
{
	bool b_result = false;

	// Notify pre.
	BLKC_ProxyMethodTemplate::BLKD_ProxyNotify_pre( type_id, ObjectPt, pt,
			 b_result, mMarshalDummy, mMarshalDummy, mMarshalDummy );

	// Call the implementation method.
	ObjectPt->obs_funcCallObserver( b_result );

	// Notify post.
	BLKC_ProxyMethodTemplate::BLKD_ProxyNotify_post( type_id, ObjectPt, pt, 
			b_result, mMarshalDummy, mMarshalDummy, mMarshalDummy );
}