#ifndef STUB_APIC_MINEMODEL_OBSERVER_H
#define STUB_APIC_MINEMODEL_OBSERVER_H

#include "BLKC_Common.h"
#include "APIC_MineModel.h"
#include "ObserverDestructor.h"

class Stub_APIC_MineModelObserver :  public APIC_MineModelObserver, public ObserverDestructor
{
    public:
        Stub_APIC_MineModelObserver( uint32_t session_id );
        ~Stub_APIC_MineModelObserver();
        void setSubject( APIC_MineModel* );
        void deleteSubject( APIC_MineModel* );
        void dataChanged();
        void obs_gameStateChanged(GameState state);
        void obs_minesRevealed(int rowMineTriggered, int colMineTriggered, std::vector<std::pair<int,int>> mines);
        void obs_gameOver(bool win);

        uint32_t SessionID;

    private:
        Stub_APIC_MineModelObserver();

        AttachedObserverList<APIC_MineModel,void (APIC_MineModel::*)(APIC_MineModelObserver*),APIC_MineModelObserver> *m_AttachedObserverList;
};

#endif // STUB_APIC_MINEMODEL_OBSERVER_H