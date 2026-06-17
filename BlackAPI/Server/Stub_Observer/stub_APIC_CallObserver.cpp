#include "pch.h"
#include "ClassIDMethodIDObservable.h"
#include "BLKC_ConnectManager.h"
#include "BLKC_StubManager.h"
#include "AllocateMemory.h"
#include "BLKC_StubMethodTemplate.h"
#include "marsahling.h"
#include "unmarsahling.h"

#include "stub_APIC_CallObserver.h"

Stub_APIC_CallObserver::Stub_APIC_CallObserver( uint32_t session_id )
	: ObserverDestructor(session_id)
{
	SessionID = session_id;
	m_AttachedObserverList = new AttachedObserverList< APIC_Call, void ( APIC_Call::* )( APIC_CallObserver* ), APIC_CallObserver >( &APIC_Call::detachObserver, this );
}

Stub_APIC_CallObserver::Stub_APIC_CallObserver()
{
	SessionID = 0;
	m_AttachedObserverList = NULL;
}

Stub_APIC_CallObserver::~Stub_APIC_CallObserver()
{
	delete m_AttachedObserverList;
}

void Stub_APIC_CallObserver::setSubject( APIC_Call* pc_APIC_Call )
{
	m_AttachedObserverList->setSubject( pc_APIC_Call );
	return;
}

void Stub_APIC_CallObserver::deleteSubject( APIC_Call* pc_APIC_Call )
{
	m_AttachedObserverList->deleteSubject( pc_APIC_Call );
	return;
}

void Stub_APIC_CallObserver::obs_funcCallObserver( bool b_result )
{
	uint32_t ClassMethodID = UISEP__APIC_CallObserver__obs_funcCallObserver__1;

	RENEW_FUNC_INFO();

	BLKC_StubMethodTemplate::BLKD_StubNotify(ClassMethodID, this, b_result , mMarshalDummy , mMarshalDummy , mMarshalDummy );
}