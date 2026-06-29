
#ifndef MDLC_MINE_MODEL_H
#define MDLC_MINE_MODEL_H

#include "BLKC_Common.h"
#include "APIC_MineModel.h"
#include "LIBC_List.h"
#include "BestTimesStorage.h"

#include "GameState.h"

class MineSetting;

class MDLC_MineModel : public APIC_MineModel
{
    public:
        static MDLC_MineModel* newInstance();
        
        void startGame(int row, int col);

        virtual void setup(int rows, int cols, int mineCount);
        virtual void req_openCell(int row, int col, void (*ans_cellOpened)(std::vector<PointCellOpened>, bool));
        virtual void attachObserver(APIC_MineModelObserver* observer);
        virtual void detachObserver(APIC_MineModelObserver* observer);
        virtual void obs_gameStateChanged(GameState state);
        virtual void req_toggleFlag(int row, int col, void (*ans_flagChanged)(int, int, bool, int, int, bool));
        virtual GameState getState() const;
        virtual void setState(GameState state);
        virtual void obs_minesRevealed(int rowMineTriggered, int colMineTriggered, std::vector<std::pair<int,int>> mines);
        virtual void obs_gameOver(bool win);
    
        virtual std::vector<BestTimeEntry> getEntries() const;
        virtual int getCurrentSizeField() const;
        virtual int getCurrentMinesField() const;
        void setBestTime(BestTimeEntry);

    private:
        MDLC_MineModel();
        ~MDLC_MineModel();

    private:
        int m_rows      = 0;
        int m_cols      = 0;
        int m_mineCount = 0;

        MineSetting* m_mineSetting;
        GameState m_state;
        static LIBC_List<APIC_MineModelObserver>  	m_pc_MineModelList;
        BestTimesStorage* m_bestTimesStorage;
        bool m_bestTimesLoaded = false;
};

#endif // MDLC_MINE_MODEL_H