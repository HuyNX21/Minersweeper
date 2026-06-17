#ifndef APIC_MINE_MODEL_H
#define APIC_MINE_MODEL_H

#include "BLKC_Common.h"
#include "GameState.h"

class APIC_MineModelObserver{
    public:
        virtual void obs_gameStateChanged(GameState state) = 0;
        virtual void obs_minesRevealed(int rowMineTriggered, int colMineTriggered, std::vector<std::pair<int,int>> mines) = 0;
        virtual void obs_gameOver(bool win) = 0;
};

class APIC_MineModel
{
    public:
        APIC_MineModel();
        ~APIC_MineModel();
        static APIC_MineModel* newInstance();
        virtual void setup(int rows, int cols, int mineCount) = 0;
        virtual void req_openCell(int row, int col, void (*ans_cellOpened)(std::vector<PointCellOpened>, bool)) = 0;
        virtual void attachObserver(APIC_MineModelObserver* observer) = 0;
        virtual void detachObserver(APIC_MineModelObserver* observer) = 0;
        virtual void obs_gameStateChanged(GameState state) = 0;
        virtual void req_toggleFlag(int row, int col, void (*ans_flagChanged)(int, int, bool, int, int, bool)) = 0;
        virtual GameState getState() const = 0;
        virtual void setState(GameState state) = 0;
        virtual void obs_minesRevealed(int rowMineTriggered, int colMineTriggered, std::vector<std::pair<int,int>> mines) = 0;
        virtual void obs_gameOver(bool win) = 0;
};

#endif