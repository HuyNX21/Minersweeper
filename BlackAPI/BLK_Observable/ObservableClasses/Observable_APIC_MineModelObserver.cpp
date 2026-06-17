#include "pch.h"
#include "Observable_APIC_MineModelObserver.h"
#include "ClassIDMethodIDObservable.h"
#include "BLKC_Common.h"
#include "BLKC_ProxyManager.h"
#include "BLKC_ProxyMethodTemplate.h"
#include "marsahling.h"
#include "unmarsahling.h"

Observable_APIC_MineModelObserver::Observable_APIC_MineModelObserver()
{
    static const FUNC_CONTAINER::FUNC_TBL_T tbl[] = { 
        { UISEP__APIC_MineModelObserver__obs_gameStateChanged__1,   &Observable_APIC_MineModelObserver::obs_gameStateChanged },
        { UISEP__APIC_MineModelObserver__obs_minesRevealed__2,      &Observable_APIC_MineModelObserver::obs_minesRevealed },
        { UISEP__APIC_MineModelObserver__obs_gameOver__3,           &Observable_APIC_MineModelObserver::obs_gameOver }
    };
    mFuncPtContainer.registFunction( tbl, FUNC_TBL_LENGTH(tbl) );
}

void Observable_APIC_MineModelObserver::doExec( BLKS_COMMONID* type_id , void* ObjectPt, void* pt )
{
    mFuncPtContainer.exec( this, type_id, ObjectPt, pt );
}

void Observable_APIC_MineModelObserver::obs_gameStateChanged( BLKS_COMMONID* type_id, Proxy_APIC_MineModelObserver* ObjectPt, void* pt )
{
    GameState state;

    // Notify pre.
    BLKC_ProxyMethodTemplate::BLKD_ProxyNotify_pre( type_id, ObjectPt, pt,
             state, mMarshalDummy, mMarshalDummy, mMarshalDummy );

    // Call the implementation method.
    ObjectPt->obs_gameStateChanged( state );

    // Notify post.
    BLKC_ProxyMethodTemplate::BLKD_ProxyNotify_post( type_id, ObjectPt, pt, 
            state, mMarshalDummy, mMarshalDummy, mMarshalDummy );
}

void Observable_APIC_MineModelObserver::obs_minesRevealed( BLKS_COMMONID* type_id, Proxy_APIC_MineModelObserver* ObjectPt, void* pt )
{
    int rowMineTriggered;
    int colMineTriggered;
    std::vector<std::pair<int,int>> mines;

    // Notify pre.
    BLKC_ProxyMethodTemplate::BLKD_ProxyNotify_pre( type_id, ObjectPt, pt,
             rowMineTriggered, colMineTriggered, mines, mMarshalDummy, mMarshalDummy, mMarshalDummy );

    // Call the implementation method.
    ObjectPt->obs_minesRevealed( rowMineTriggered, colMineTriggered, mines );

    // Notify post.
    BLKC_ProxyMethodTemplate::BLKD_ProxyNotify_post( type_id, ObjectPt, pt, 
            rowMineTriggered, colMineTriggered, mines, mMarshalDummy, mMarshalDummy, mMarshalDummy );
}

void Observable_APIC_MineModelObserver::obs_gameOver( BLKS_COMMONID* type_id, Proxy_APIC_MineModelObserver* ObjectPt, void* pt )
{
    bool win;

    // Notify pre.
    BLKC_ProxyMethodTemplate::BLKD_ProxyNotify_pre( type_id, ObjectPt, pt,
             win, mMarshalDummy, mMarshalDummy, mMarshalDummy );

    // Call the implementation method.
    ObjectPt->obs_gameOver( win );

    // Notify post.
    BLKC_ProxyMethodTemplate::BLKD_ProxyNotify_post( type_id, ObjectPt, pt, 
            win, mMarshalDummy, mMarshalDummy, mMarshalDummy );
}