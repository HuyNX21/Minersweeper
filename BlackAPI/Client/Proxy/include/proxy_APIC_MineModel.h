#ifndef PROXY_APIC_MINEMODEL_H
#define PROXY_APIC_MINEMODEL_H

#include "BLKC_Common.h"

#include "GameState.h"
#include "BestTimeEntry.h"

class Proxy_APIC_MineModelObserver
{
    public:
        Proxy_APIC_MineModelObserver();
        ~Proxy_APIC_MineModelObserver();
        virtual void obs_gameStateChanged(GameState state);
        virtual void obs_minesRevealed(int rowMineTriggered, int colMineTriggered, std::vector<std::pair<int,int>> mines);
        virtual void obs_gameOver(bool win);
};

class Proxy_APIC_MineModel
{
    public:
        uint32_t InstanceID;
    protected: 
        uint32_t SessionID;
    public: 
        Proxy_APIC_MineModel();
        ~Proxy_APIC_MineModel();
        static Proxy_APIC_MineModel* newInstance();
        virtual void setup(int rows, int cols, int mineCount) = 0;
        virtual void req_openCell(int row, int col, void (*ans_cellOpened)(std::vector<PointCellOpened>, bool stateGameOver)) = 0;
        virtual void attachObserver(Proxy_APIC_MineModelObserver* pc_obs) = 0;
        virtual void detachObserver(Proxy_APIC_MineModelObserver* pc_obs) = 0;
        virtual void obs_gameStateChanged(GameState state) = 0;
        virtual void req_toggleFlag(int row, int col, void (*ans_flagChanged)(int, int, bool, int, int, bool)) = 0;
        virtual void setState(GameState state) = 0;
        virtual GameState getState() const = 0;
        virtual void obs_minesRevealed(int rowMineTriggered, int colMineTriggered, std::vector<std::pair<int,int>> mines) = 0;
        virtual void obs_gameOver(bool win) = 0;
        virtual std::vector<BestTimeEntry> getEntries() const = 0;
        virtual int getCurrentSizeField() const = 0;
        virtual int getCurrentMinesField() const = 0;
        virtual void setBestTime(BestTimeEntry entry) = 0;
};  

#endif // PROXY_APIC_MINEMODEL_H