#include "pch.h"
#include "ClassIDMethodIDObservable.h"
#include "BLKC_ConnectManager.h"
#include "BLKC_StubManager.h"
#include "AllocateMemory.h"
#include "BLKC_StubMethodTemplate.h"
#include "marsahling.h"
#include "unmarsahling.h"

#include "stub_APIC_MineModelObserver.h"

Stub_APIC_MineModelObserver::Stub_APIC_MineModelObserver( uint32_t session_id )
	: ObserverDestructor(session_id)
{
	SessionID = session_id;
	m_AttachedObserverList = new AttachedObserverList< APIC_MineModel, void ( APIC_MineModel::* )( APIC_MineModelObserver* ), APIC_MineModelObserver >( &APIC_MineModel::detachObserver, this );
}

Stub_APIC_MineModelObserver::Stub_APIC_MineModelObserver()
{
	SessionID = 0;
	m_AttachedObserverList = NULL;
}

Stub_APIC_MineModelObserver::~Stub_APIC_MineModelObserver()
{
	delete m_AttachedObserverList;
}

void Stub_APIC_MineModelObserver::setSubject( APIC_MineModel* pc_APIC_MineModel )
{
	m_AttachedObserverList->setSubject( pc_APIC_MineModel );
	return;
}

void Stub_APIC_MineModelObserver::deleteSubject( APIC_MineModel* pc_APIC_MineModel )
{
	m_AttachedObserverList->deleteSubject( pc_APIC_MineModel );
	return;
}

void Stub_APIC_MineModelObserver::obs_gameStateChanged( GameState state )
{
	uint32_t ClassMethodID = UISEP__APIC_MineModelObserver__obs_gameStateChanged__1;

	RENEW_FUNC_INFO();

	BLKC_StubMethodTemplate::BLKD_StubNotify(ClassMethodID, this, state , mMarshalDummy , mMarshalDummy , mMarshalDummy );
}

void Stub_APIC_MineModelObserver::obs_minesRevealed(int rowMineTriggered, int colMineTriggered, std::vector<std::pair<int,int>> mines)
{
	uint32_t ClassMethodID = UISEP__APIC_MineModelObserver__obs_minesRevealed__2;

	RENEW_FUNC_INFO();

	BLKC_StubMethodTemplate::BLKD_StubNotify(ClassMethodID, this, rowMineTriggered, colMineTriggered, mines, mMarshalDummy , mMarshalDummy , mMarshalDummy );
}

void Stub_APIC_MineModelObserver::obs_gameOver(bool win)
{
	uint32_t ClassMethodID = UISEP__APIC_MineModelObserver__obs_gameOver__3;

	RENEW_FUNC_INFO();

	BLKC_StubMethodTemplate::BLKD_StubNotify(ClassMethodID, this, win, mMarshalDummy , mMarshalDummy , mMarshalDummy );
}