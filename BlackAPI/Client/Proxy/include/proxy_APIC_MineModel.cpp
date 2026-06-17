#include "proxy_APIC_MineModel.h"
#include "proxy_MDLC_MineModel.h"

Proxy_APIC_MineModel::Proxy_APIC_MineModel(){}
Proxy_APIC_MineModel::~Proxy_APIC_MineModel(){}
Proxy_APIC_MineModel* Proxy_APIC_MineModel::newInstance()
{
    return	Proxy_MDLC_MineModel::newInstance();
}

Proxy_APIC_MineModelObserver::Proxy_APIC_MineModelObserver() {}
Proxy_APIC_MineModelObserver::~Proxy_APIC_MineModelObserver() {}
void Proxy_APIC_MineModelObserver::obs_gameStateChanged(GameState state) { }
void Proxy_APIC_MineModelObserver::obs_minesRevealed(int rowMineTriggered, int colMineTriggered, std::vector<std::pair<int,int>> mines) { }
void Proxy_APIC_MineModelObserver::obs_gameOver(bool win) { }