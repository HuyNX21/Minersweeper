#ifndef PROXY_MDLC_MINEMODEL_H
#define PROXY_MDLC_MINEMODEL_H

#include "BLKC_Common.h"
#include "proxy_APIC_MineModel.h"

class Proxy_MDLC_MineModel : public Proxy_APIC_MineModel
{
    public: 
        Proxy_MDLC_MineModel();
        ~Proxy_MDLC_MineModel();
        static Proxy_MDLC_MineModel* newInstance();
        virtual void setup(int rows, int cols, int mineCount);
        virtual void req_openCell(int row, int col, void (*ans_cellOpened)(std::vector<PointCellOpened>, bool));
        virtual void attachObserver(Proxy_APIC_MineModelObserver* pc_obs);
        virtual void detachObserver(Proxy_APIC_MineModelObserver* pc_obs);
        virtual void obs_gameStateChanged(GameState state);
        virtual void req_toggleFlag(int row, int col, void (*ans_flagChanged)(int, int, bool, int, int, bool));
        virtual void setState(GameState state);
        virtual GameState getState() const;
        virtual void obs_minesRevealed(int rowMineTriggered, int colMineTriggered, std::vector<std::pair<int,int>> mines);
        virtual void obs_gameOver(bool win);
};  

#endif // PROXY_MDLC_MINEMODEL_H