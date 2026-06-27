#include "pch.h"
#include "proxy_MDLC_MineModel.h"
#include "ClassIDMethodID.h"
#include "BLKC_ProxyMethodTemplate.h"
#include "BLKC_MarshalParamaterWrapper.h"
#include "BLKC_ProxyCallBackTypedef.h"
#include "BLKC_CallbackPointerContainer.h"
#include "ObserverAttachDetachProxy.h"

Proxy_MDLC_MineModel::Proxy_MDLC_MineModel(){}
Proxy_MDLC_MineModel::~Proxy_MDLC_MineModel(){}

Proxy_MDLC_MineModel* Proxy_MDLC_MineModel::newInstance()
{
    Proxy_MDLC_MineModel* p_ret = NULL;

    uint32_t ClassMethodID = UISEP__APIC_MineModel__newInstance__1;

    BLKC_ProxyMethodTemplate::BLKD_ProxyNewinstance_Singleton( ClassMethodID, p_ret, 
            mMarshalDummy, mMarshalDummy, mMarshalDummy, mMarshalDummy, mMarshalDummy, mMarshalDummy );

    return p_ret;
}

void Proxy_MDLC_MineModel::setup(int rows, int cols, int mineCount)
{
    uint32_t ClassMethodID = UISEP__APIC_MineModel__setup__2;

    BLKC_ProxyMethodTemplate::BLKD_ProxyParaType( ClassMethodID, this, 
            rows, mMarshalDummy, mMarshalDummy, mMarshalDummy, mMarshalDummy, mMarshalDummy,
            cols, mMarshalDummy, mMarshalDummy, mMarshalDummy, mMarshalDummy,
            mineCount, mMarshalDummy, mMarshalDummy, mMarshalDummy, mMarshalDummy );
}

void Proxy_MDLC_MineModel::req_openCell(int row, int col, void (*ans_cellOpened)(std::vector<PointCellOpened>, bool))
{
    uint32_t ClassMethodID = UISEP__APIC_MineModel__req_openCell__3;
    uint32_t CallbackID = BLKD_PROXY_CBID__APIC_MineModel__req_openCell__3;

    BLKC_CallbackPointerContainer c_CallbackContainer;
    c_CallbackContainer.setCbid( CallbackID );
    c_CallbackContainer.setFunc( (void*)ans_cellOpened );

    BLKC_ProxyMethodTemplate::BLKD_ProxyParaType( ClassMethodID, this, 
        row, col, c_CallbackContainer, mMarshalDummy, mMarshalDummy, mMarshalDummy,
        mMarshalDummy, mMarshalDummy, mMarshalDummy, mMarshalDummy, mMarshalDummy,
        mMarshalDummy, mMarshalDummy, mMarshalDummy, mMarshalDummy, mMarshalDummy );
}

void Proxy_MDLC_MineModel::req_toggleFlag(int row, int col, void (*ans_flagChanged)(int, int, bool, int, int, bool))
{
    uint32_t ClassMethodID = UISEP__APIC_MineModel__req_toggleFlag__7;
    uint32_t CallbackID = BLKD_PROXY_CBID__APIC_MineModel__req_toggleFlag__7;

    BLKC_CallbackPointerContainer c_CallbackContainer;
    c_CallbackContainer.setCbid( CallbackID );
    c_CallbackContainer.setFunc( (void*)ans_flagChanged );

    BLKC_ProxyMethodTemplate::BLKD_ProxyParaType( ClassMethodID, this, 
        row, col, c_CallbackContainer, mMarshalDummy, mMarshalDummy, mMarshalDummy,
        mMarshalDummy, mMarshalDummy, mMarshalDummy, mMarshalDummy, mMarshalDummy,
        mMarshalDummy, mMarshalDummy, mMarshalDummy, mMarshalDummy, mMarshalDummy );
}

void Proxy_MDLC_MineModel::attachObserver(Proxy_APIC_MineModelObserver* pc_obs)
{
    BLKS_COMMONID id;

	toCommonIDStruct(id, UISEP__APIC_MineModel__attachObserver__4, this->InstanceID, this->SessionID);
	
	ProxyCommon::attachObserver(&id, pc_obs);
	
	fromCommonIDStruct(id, id.ClassMethodID, this->InstanceID, this->SessionID);
}

void Proxy_MDLC_MineModel::detachObserver(Proxy_APIC_MineModelObserver* pc_obs)
{
    BLKS_COMMONID id;

    toCommonIDStruct(id, UISEP__APIC_MineModel__detachObserver__5, this->InstanceID, this->SessionID);
    
    ProxyCommon::detachObserver(&id, pc_obs);
    
    fromCommonIDStruct(id, id.ClassMethodID, this->InstanceID, this->SessionID);
}

void Proxy_MDLC_MineModel::obs_gameStateChanged(GameState state)
{
    uint32_t ClassMethodID = UISEP__APIC_MineModel__obs_gameStateChanged__6;

    BLKC_ProxyMethodTemplate::BLKD_ProxyParaType( ClassMethodID, this, 
            state, mMarshalDummy, mMarshalDummy, mMarshalDummy, mMarshalDummy, mMarshalDummy,
            mMarshalDummy, mMarshalDummy, mMarshalDummy, mMarshalDummy, mMarshalDummy,
            mMarshalDummy, mMarshalDummy, mMarshalDummy, mMarshalDummy, mMarshalDummy );
}

GameState Proxy_MDLC_MineModel::getState() const
{
    GameState e_ret;

    uint32_t ClassMethodID = UISEP__APIC_MineModel__getState__8;

    BLKC_ProxyMethodTemplate::BLKD_ProxyParaType( ClassMethodID, this, 
            e_ret, mMarshalDummy, mMarshalDummy, mMarshalDummy, mMarshalDummy, mMarshalDummy,
            mMarshalDummy, mMarshalDummy, mMarshalDummy, mMarshalDummy, mMarshalDummy,
            mMarshalDummy, mMarshalDummy, mMarshalDummy, mMarshalDummy, mMarshalDummy );

    return e_ret;
}

void Proxy_MDLC_MineModel::setState(GameState state)
{
    uint32_t ClassMethodID = UISEP__APIC_MineModel__setState__9;

    BLKC_ProxyMethodTemplate::BLKD_ProxyParaType( ClassMethodID, this, 
            state, mMarshalDummy, mMarshalDummy, mMarshalDummy, mMarshalDummy, mMarshalDummy,
            mMarshalDummy, mMarshalDummy, mMarshalDummy, mMarshalDummy, mMarshalDummy,
            mMarshalDummy, mMarshalDummy, mMarshalDummy, mMarshalDummy, mMarshalDummy );
}

void Proxy_MDLC_MineModel::obs_minesRevealed(int rowMineTriggered, int colMineTriggered, std::vector<std::pair<int,int>> mines)
{
    uint32_t ClassMethodID = UISEP__APIC_MineModel__obs_minesRevealed__10;

    BLKC_ProxyMethodTemplate::BLKD_ProxyParaType( ClassMethodID, this, 
            rowMineTriggered, colMineTriggered, mines, mMarshalDummy, mMarshalDummy, mMarshalDummy,
            mMarshalDummy, mMarshalDummy, mMarshalDummy, mMarshalDummy, mMarshalDummy,
            mMarshalDummy, mMarshalDummy, mMarshalDummy, mMarshalDummy, mMarshalDummy );
}

void Proxy_MDLC_MineModel::obs_gameOver(bool win)
{
    uint32_t ClassMethodID = UISEP__APIC_MineModel__obs_gameOver__11;

    BLKC_ProxyMethodTemplate::BLKD_ProxyParaType( ClassMethodID, this, 
            win, mMarshalDummy, mMarshalDummy, mMarshalDummy, mMarshalDummy, mMarshalDummy,
            mMarshalDummy, mMarshalDummy, mMarshalDummy, mMarshalDummy, mMarshalDummy,
            mMarshalDummy, mMarshalDummy, mMarshalDummy, mMarshalDummy, mMarshalDummy );
}

std::vector<BestTimeEntry> Proxy_MDLC_MineModel::getEntries() const
{
    std::vector<BestTimeEntry> v_ret;

    uint32_t ClassMethodID = UISEP__APIC_MineModel__getEntries__12;

    BLKC_ProxyMethodTemplate::BLKD_ProxyParaType( ClassMethodID, this, 
            v_ret, mMarshalDummy, mMarshalDummy, mMarshalDummy, mMarshalDummy, mMarshalDummy,
            mMarshalDummy, mMarshalDummy, mMarshalDummy, mMarshalDummy, mMarshalDummy,
            mMarshalDummy, mMarshalDummy, mMarshalDummy, mMarshalDummy, mMarshalDummy );

    return v_ret;
}

int Proxy_MDLC_MineModel::getCurrentSizeField() const
{
    int i_ret;

    uint32_t ClassMethodID = UISEP__APIC_MineModel__getCurrentSizeField__13;

    BLKC_ProxyMethodTemplate::BLKD_ProxyParaType( ClassMethodID, this, 
            i_ret, mMarshalDummy, mMarshalDummy, mMarshalDummy, mMarshalDummy, mMarshalDummy,
            mMarshalDummy, mMarshalDummy, mMarshalDummy, mMarshalDummy, mMarshalDummy,
            mMarshalDummy, mMarshalDummy, mMarshalDummy, mMarshalDummy, mMarshalDummy );

    return i_ret;
}

int Proxy_MDLC_MineModel::getCurrentMinesField() const
{
    int i_ret;

    uint32_t ClassMethodID = UISEP__APIC_MineModel__getCurrentMinesField__14;

    BLKC_ProxyMethodTemplate::BLKD_ProxyParaType( ClassMethodID, this, 
            i_ret, mMarshalDummy, mMarshalDummy, mMarshalDummy, mMarshalDummy, mMarshalDummy,
            mMarshalDummy, mMarshalDummy, mMarshalDummy, mMarshalDummy, mMarshalDummy,
            mMarshalDummy, mMarshalDummy, mMarshalDummy, mMarshalDummy, mMarshalDummy );

    return i_ret;
}

void Proxy_MDLC_MineModel::setBestTime(BestTimeEntry entry)
{
    uint32_t ClassMethodID = UISEP__APIC_MineModel__setBestTime__15;

    BLKC_ProxyMethodTemplate::BLKD_ProxyParaType( ClassMethodID, this, 
            entry, mMarshalDummy, mMarshalDummy, mMarshalDummy, mMarshalDummy, mMarshalDummy,
            mMarshalDummy, mMarshalDummy, mMarshalDummy, mMarshalDummy, mMarshalDummy,
            mMarshalDummy, mMarshalDummy, mMarshalDummy, mMarshalDummy, mMarshalDummy );
}