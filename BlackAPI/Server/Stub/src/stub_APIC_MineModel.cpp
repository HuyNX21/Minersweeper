#include "pch.h"
#include "stub_method.h"
#include "ClassIDMethodID.h"
#include "BLKC_ProxyManager.h"
#include "BLKC_ConnectManager.h"
#include "BLKC_ProxyCallBackTypedef.h"

#include "APIC_MineModel.h"
#include "Server/Stub/include/stub_APIC_MineModel.h"
#include "stub_APIC_MineModelObserver.h"
#include "ObserverAttachDetachStub.h"
#include "BestTimeEntry.h"

void Stub_APIC_MineModel::dispatch( BLKS_COMMONID* type_id , void* ObjectPt, void* pt )
{
    APIC_MineModel* pc_APIC_MineModel = (APIC_MineModel *)ObjectPt;

    switch( type_id->ClassMethodID )
    {
        case UISEP__APIC_MineModel__newInstance__1:
            Stub_APIC_MineModel_newInstance_01(type_id, pc_APIC_MineModel, pt);
            break;
        case UISEP__APIC_MineModel__setup__2:
            Stub_APIC_MineModel_setup_02(type_id, pc_APIC_MineModel, pt);
            break;
        case UISEP__APIC_MineModel__req_openCell__3:
            Stub_APIC_MineModel_req_openCell_03(type_id, pc_APIC_MineModel, pt);
            break;
        case UISEP__APIC_MineModel__attachObserver__4:
            Stub_APIC_MineModel_attachObserver_04(type_id, pc_APIC_MineModel, pt);
            break;
        case UISEP__APIC_MineModel__detachObserver__5:
            Stub_APIC_MineModel_detachObserver_05(type_id, pc_APIC_MineModel, pt);
            break;
        case UISEP__APIC_MineModel__obs_gameStateChanged__6:
            Stub_APIC_MineModel_obs_gameStateChanged_06(type_id, pc_APIC_MineModel, pt);
            break;
        case UISEP__APIC_MineModel__req_toggleFlag__7:
            Stub_APIC_MineModel_req_toggleFlag_07(type_id, pc_APIC_MineModel, pt);
            break;
        case UISEP__APIC_MineModel__getState__8:
            Stub_APIC_MineModel_getState_08(type_id, pc_APIC_MineModel, pt);
            break;
        case UISEP__APIC_MineModel__setState__9:
            Stub_APIC_MineModel_setState_09(type_id, pc_APIC_MineModel, pt);
            break;
        case UISEP__APIC_MineModel__obs_minesRevealed__10:
            Stub_APIC_MineModel_obs_minesRevealed_10(type_id, pc_APIC_MineModel, pt);
            break;
        case UISEP__APIC_MineModel__obs_gameOver__11:
            Stub_APIC_MineModel_obs_gameOver_11(type_id, pc_APIC_MineModel, pt);
            break;
        case UISEP__APIC_MineModel__getEntries__12:
            Stub_APIC_MineModel_getEntries_12(type_id, pc_APIC_MineModel, pt);
            break;
        case UISEP__APIC_MineModel__getCurrentSizeField__13:
            Stub_APIC_MineModel_getCurrentSizeField_13(type_id, pc_APIC_MineModel, pt);
            break;
        case UISEP__APIC_MineModel__getCurrentMinesField__14:
            Stub_APIC_MineModel_getCurrentMinesField_14(type_id, pc_APIC_MineModel, pt);
            break;
        case UISEP__APIC_MineModel__setBestTime__15:
            Stub_APIC_MineModel_setBestTime_15(type_id, pc_APIC_MineModel, pt);
            break;
        default:
            LOG_ERROR("ClassMethodID: %d not found", type_id->ClassMethodID);
            // BLKC_ConnectManager::dispatchError( type_id, pt,  __FILE__, __LINE__, __PRETTY_FUNCTION__);
            break;
    }
}

Stub_APIC_MineModel* Stub_APIC_MineModel::newInstance()
{
    static Stub_APIC_MineModel c_Stub_APIC_MineModel;
    return &c_Stub_APIC_MineModel;
}

void Stub_APIC_MineModel::Stub_APIC_MineModel_newInstance_01( BLKS_COMMONID* type_id , APIC_MineModel* pc_APIC_MineModel, void* pt )
{
    // Param.

    RENEW_FUNC_INFO();

    // Base Pre.
    BLKC_StubMethodTemplate::BLKD_StubNewinstance_pre(type_id, pc_APIC_MineModel, pt, mMarshalDummy, mMarshalDummy, mMarshalDummy, mMarshalDummy, mMarshalDummy, mMarshalDummy );

    // APIC_MineModel::newInstance().
    pc_APIC_MineModel = APIC_MineModel::newInstance( );

    // Base Post.
    BLKC_StubMethodTemplate::BLKD_StubNewinstance_post(type_id, pc_APIC_MineModel, pt, mMarshalDummy , mMarshalDummy , mMarshalDummy, mMarshalDummy, mMarshalDummy, mMarshalDummy);

}

void Stub_APIC_MineModel::Stub_APIC_MineModel_setup_02( BLKS_COMMONID* type_id , APIC_MineModel* pc_APIC_MineModel, void* pt )
{
    // Param.
    int rows = 0;
    int cols = 0;
    int mineCount = 0;

    RENEW_FUNC_INFO();

    // Base Pre.
    BLKC_StubMethodTemplate::BLKD_StubParaType_pre( type_id , pc_APIC_MineModel , pt,
                                                    rows,cols,mineCount,mMarshalDummy,mMarshalDummy,
                                                    mMarshalDummy,mMarshalDummy,mMarshalDummy,mMarshalDummy,mMarshalDummy,
                                                    mMarshalDummy,mMarshalDummy,mMarshalDummy,mMarshalDummy,mMarshalDummy,
                                                    mMarshalDummy );

    // APIC_MineModel::setup().
    pc_APIC_MineModel->setup( rows, cols, mineCount );

    // Base Post.
    BLKC_StubMethodTemplate::BLKD_StubParaType_post( type_id , pc_APIC_MineModel , pt,
                                                    rows,cols,mineCount,mMarshalDummy,mMarshalDummy,
                                                    mMarshalDummy,mMarshalDummy,mMarshalDummy,mMarshalDummy,mMarshalDummy,
                                                    mMarshalDummy,mMarshalDummy,mMarshalDummy,mMarshalDummy,mMarshalDummy,
                                                    mMarshalDummy );
}

void Stub_APIC_MineModel::Stub_APIC_MineModel_req_openCell_03( BLKS_COMMONID* type_id , APIC_MineModel* pc_APIC_MineModel, void* pt )
{
    // Param.
    int row = 0;
    int col = 0;
    BLKC_CallbackPointerContainer c_CallbackContainer;
	c_CallbackContainer.setSessionID( type_id->SessionID );

    RENEW_FUNC_INFO();

    // Base Pre.
    BLKC_StubMethodTemplate::BLKD_StubParaType_pre( type_id , pc_APIC_MineModel , pt,
                                                    row,col,c_CallbackContainer,mMarshalDummy,mMarshalDummy,
                                                    mMarshalDummy,mMarshalDummy,mMarshalDummy,mMarshalDummy,mMarshalDummy,
                                                    mMarshalDummy,mMarshalDummy,mMarshalDummy,mMarshalDummy,mMarshalDummy,
                                                    mMarshalDummy );

    // APIC_MineModel::req_openCell().
    if( c_CallbackContainer.getRegist() == true ){
        pc_APIC_MineModel->req_openCell( row, col, Stub_ans_openCell__99 );
    }

    // Base Post.
    BLKC_StubMethodTemplate::BLKD_StubParaType_post( type_id , pc_APIC_MineModel , pt,
                                                    row,col,c_CallbackContainer,mMarshalDummy,mMarshalDummy,
                                                    mMarshalDummy,mMarshalDummy,mMarshalDummy,mMarshalDummy,mMarshalDummy,
                                                    mMarshalDummy,mMarshalDummy,mMarshalDummy,mMarshalDummy,mMarshalDummy,
                                                    mMarshalDummy );
}

void Stub_APIC_MineModel::Stub_ans_openCell__99(std::vector<PointCellOpened> openedCells, bool stateGameOver)
{
    uint32_t callbackID = BLKD_PROXY_CBID__APIC_MineModel__req_openCell__3;

    BLKC_StubMethodTemplate::BLKD_StubCallBack( callbackID, openedCells ,stateGameOver,mMarshalDummy,mMarshalDummy,mMarshalDummy,mMarshalDummy );
    return;
}

void Stub_APIC_MineModel::Stub_APIC_MineModel_attachObserver_04( BLKS_COMMONID* type_id , APIC_MineModel* pc_APIC_MineModel, void* pt )
{
	RENEW_FUNC_INFO();

	StubCommon::ObserverAttachDettachFunc<APIC_MineModel, Stub_APIC_MineModelObserver, APIC_MineModelObserver>::attach(type_id, pc_APIC_MineModel, pt, &APIC_MineModel::attachObserver);
}

void Stub_APIC_MineModel::Stub_APIC_MineModel_detachObserver_05( BLKS_COMMONID* type_id , APIC_MineModel* pc_APIC_MineModel, void* pt )
{
	RENEW_FUNC_INFO();

	StubCommon::ObserverAttachDettachFunc<APIC_MineModel, Stub_APIC_MineModelObserver, APIC_MineModelObserver>::detach(type_id, pc_APIC_MineModel, pt, &APIC_MineModel::detachObserver);
}

void Stub_APIC_MineModel::Stub_APIC_MineModel_obs_gameStateChanged_06( BLKS_COMMONID* type_id , APIC_MineModel* pc_APIC_MineModel, void* pt )
{
    // Param.
    GameState state;

    RENEW_FUNC_INFO();

    // Base Pre.
    BLKC_StubMethodTemplate::BLKD_StubParaType_pre( type_id , pc_APIC_MineModel , pt,
                                                    state,mMarshalDummy,mMarshalDummy,mMarshalDummy,mMarshalDummy,
                                                    mMarshalDummy,mMarshalDummy,mMarshalDummy,mMarshalDummy,mMarshalDummy,
                                                    mMarshalDummy,mMarshalDummy,mMarshalDummy,mMarshalDummy,mMarshalDummy,
                                                    mMarshalDummy );

    // APIC_MineModel::obs_gameStateChanged().
    pc_APIC_MineModel->obs_gameStateChanged( state );

    // Base Post.
    BLKC_StubMethodTemplate::BLKD_StubParaType_post( type_id , pc_APIC_MineModel , pt,
                                                    state,mMarshalDummy,mMarshalDummy,mMarshalDummy,mMarshalDummy,
                                                    mMarshalDummy,mMarshalDummy,mMarshalDummy,mMarshalDummy,mMarshalDummy,
                                                    mMarshalDummy,mMarshalDummy,mMarshalDummy,mMarshalDummy,mMarshalDummy,
                                                    mMarshalDummy );
}

void Stub_APIC_MineModel::Stub_APIC_MineModel_req_toggleFlag_07( BLKS_COMMONID* type_id , APIC_MineModel* pc_APIC_MineModel, void* pt )
{
    // Param.
    int row = 0;
    int col = 0;
    BLKC_CallbackPointerContainer c_CallbackContainer;
    c_CallbackContainer.setSessionID( type_id->SessionID );

    RENEW_FUNC_INFO();

    // Base Pre.
    BLKC_StubMethodTemplate::BLKD_StubParaType_pre( type_id , pc_APIC_MineModel , pt,
                                                    row,col,c_CallbackContainer,mMarshalDummy,mMarshalDummy,
                                                    mMarshalDummy,mMarshalDummy,mMarshalDummy,mMarshalDummy,mMarshalDummy,
                                                    mMarshalDummy,mMarshalDummy,mMarshalDummy,mMarshalDummy,mMarshalDummy,
                                                    mMarshalDummy );

    // APIC_MineModel::req_toggleFlag().
    if( c_CallbackContainer.getRegist() == true ){
        pc_APIC_MineModel->req_toggleFlag( row, col, Stub_ans_toggleFlag__99 );
    }

    // Base Post.
    BLKC_StubMethodTemplate::BLKD_StubParaType_post( type_id , pc_APIC_MineModel , pt,
                                                    row,col,c_CallbackContainer,mMarshalDummy,mMarshalDummy,
                                                    mMarshalDummy,mMarshalDummy,mMarshalDummy,mMarshalDummy,mMarshalDummy,
                                                    mMarshalDummy,mMarshalDummy,mMarshalDummy,mMarshalDummy,mMarshalDummy,
                                                    mMarshalDummy );
}

void Stub_APIC_MineModel::Stub_ans_toggleFlag__99(int row, int col, bool flag, int flagUsed, int totalMines, bool b_result)
{
    uint32_t callbackID = BLKD_PROXY_CBID__APIC_MineModel__req_toggleFlag__7;

    BLKC_StubMethodTemplate::BLKD_StubCallBack( callbackID, row, col, flag, flagUsed, totalMines, b_result );
    return;
}

GameState Stub_APIC_MineModel::Stub_APIC_MineModel_getState_08( BLKS_COMMONID* type_id , APIC_MineModel* pc_APIC_MineModel, void* pt )
{
    // Param.
    GameState ret = GameState::NotStarted;

    RENEW_FUNC_INFO();

    // Base Pre.
    BLKC_StubMethodTemplate::BLKD_StubParaType_pre( type_id , pc_APIC_MineModel , pt,
                                                    mMarshalDummy,mMarshalDummy,mMarshalDummy,mMarshalDummy,mMarshalDummy,
                                                    mMarshalDummy,mMarshalDummy,mMarshalDummy,mMarshalDummy,mMarshalDummy,
                                                    mMarshalDummy,mMarshalDummy,mMarshalDummy,mMarshalDummy,mMarshalDummy,
                                                    mMarshalDummy );

    // APIC_MineModel::getState().
    ret = pc_APIC_MineModel->getState( );

    // Base Post.
    BLKC_StubMethodTemplate::BLKD_StubParaType_post( type_id , pc_APIC_MineModel , pt, ret,
                                                    mMarshalDummy,mMarshalDummy,mMarshalDummy,mMarshalDummy,mMarshalDummy,
                                                    mMarshalDummy,mMarshalDummy,mMarshalDummy,mMarshalDummy,mMarshalDummy,
                                                    mMarshalDummy,mMarshalDummy,mMarshalDummy,mMarshalDummy,mMarshalDummy,
                                                    mMarshalDummy );
    return ret;
}

void Stub_APIC_MineModel::Stub_APIC_MineModel_setState_09( BLKS_COMMONID* type_id , APIC_MineModel* pc_APIC_MineModel, void* pt )
{
    // Param.
    GameState state = GameState::NotStarted;

    RENEW_FUNC_INFO();

    // Base Pre.
    BLKC_StubMethodTemplate::BLKD_StubParaType_pre( type_id , pc_APIC_MineModel , pt,
                                                    state,mMarshalDummy,mMarshalDummy,mMarshalDummy,mMarshalDummy,
                                                    mMarshalDummy,mMarshalDummy,mMarshalDummy,mMarshalDummy,mMarshalDummy,
                                                    mMarshalDummy,mMarshalDummy,mMarshalDummy,mMarshalDummy,mMarshalDummy,
                                                    mMarshalDummy );

    // APIC_MineModel::setState().
    pc_APIC_MineModel->setState( state );

    // Base Post.
    BLKC_StubMethodTemplate::BLKD_StubParaType_post( type_id , pc_APIC_MineModel , pt,
                                                    state,mMarshalDummy,mMarshalDummy,mMarshalDummy,mMarshalDummy,
                                                    mMarshalDummy,mMarshalDummy,mMarshalDummy,mMarshalDummy,mMarshalDummy,
                                                    mMarshalDummy,mMarshalDummy,mMarshalDummy,mMarshalDummy,mMarshalDummy,
                                                    mMarshalDummy );
}

void Stub_APIC_MineModel::Stub_APIC_MineModel_obs_minesRevealed_10( BLKS_COMMONID* type_id , APIC_MineModel* pc_APIC_MineModel, void* pt )
{
    // Param.
    int rowMineTriggered = 0;
    int colMineTriggered = 0;
    std::vector<std::pair<int,int>> mines;

    RENEW_FUNC_INFO();

    // Base Pre.
    BLKC_StubMethodTemplate::BLKD_StubParaType_pre( type_id , pc_APIC_MineModel , pt,
                                                    rowMineTriggered,colMineTriggered,mines,mMarshalDummy,mMarshalDummy,
                                                    mMarshalDummy,mMarshalDummy,mMarshalDummy,mMarshalDummy,mMarshalDummy,
                                                    mMarshalDummy,mMarshalDummy,mMarshalDummy,mMarshalDummy,mMarshalDummy,
                                                    mMarshalDummy );

    // APIC_MineModel::obs_minesRevealed().
    pc_APIC_MineModel->obs_minesRevealed( rowMineTriggered, colMineTriggered, mines );

    // Base Post.
    BLKC_StubMethodTemplate::BLKD_StubParaType_post( type_id , pc_APIC_MineModel , pt,
                                                    rowMineTriggered,colMineTriggered,mines,mMarshalDummy,mMarshalDummy,
                                                    mMarshalDummy,mMarshalDummy,mMarshalDummy,mMarshalDummy,mMarshalDummy,
                                                    mMarshalDummy,mMarshalDummy,mMarshalDummy,mMarshalDummy,mMarshalDummy,
                                                    mMarshalDummy );
}

void Stub_APIC_MineModel::Stub_APIC_MineModel_obs_gameOver_11( BLKS_COMMONID* type_id , APIC_MineModel* pc_APIC_MineModel, void* pt )
{
    // Param.
    bool win = false;

    RENEW_FUNC_INFO();

    // Base Pre.
    BLKC_StubMethodTemplate::BLKD_StubParaType_pre( type_id , pc_APIC_MineModel , pt,
                                                    win,mMarshalDummy,mMarshalDummy,mMarshalDummy,mMarshalDummy,
                                                    mMarshalDummy,mMarshalDummy,mMarshalDummy,mMarshalDummy,mMarshalDummy,
                                                    mMarshalDummy,mMarshalDummy,mMarshalDummy,mMarshalDummy,mMarshalDummy,
                                                    mMarshalDummy );

    // APIC_MineModel::obs_gameOver().
    pc_APIC_MineModel->obs_gameOver( win );

    // Base Post.
    BLKC_StubMethodTemplate::BLKD_StubParaType_post( type_id , pc_APIC_MineModel , pt,
                                                    win,mMarshalDummy,mMarshalDummy,mMarshalDummy,mMarshalDummy,
                                                    mMarshalDummy,mMarshalDummy,mMarshalDummy,mMarshalDummy,mMarshalDummy,
                                                    mMarshalDummy,mMarshalDummy,mMarshalDummy,mMarshalDummy,mMarshalDummy,
                                                    mMarshalDummy );
}

std::vector<BestTimeEntry> Stub_APIC_MineModel::Stub_APIC_MineModel_getEntries_12( BLKS_COMMONID* type_id , APIC_MineModel* pc_APIC_MineModel, void* pt )
{
    // Param.
    std::vector<BestTimeEntry> ret;

    RENEW_FUNC_INFO();

    // Base Pre.
    BLKC_StubMethodTemplate::BLKD_StubParaType_pre( type_id , pc_APIC_MineModel , pt,
                                                    ret,mMarshalDummy,mMarshalDummy,mMarshalDummy,mMarshalDummy,
                                                    mMarshalDummy,mMarshalDummy,mMarshalDummy,mMarshalDummy,mMarshalDummy,
                                                    mMarshalDummy,mMarshalDummy,mMarshalDummy,mMarshalDummy,mMarshalDummy,
                                                    mMarshalDummy );

    // APIC_MineModel::getEntries().
    ret = pc_APIC_MineModel->getEntries( );

    // Base Post.
    BLKC_StubMethodTemplate::BLKD_StubParaType_post( type_id , pc_APIC_MineModel , pt, ret,
                                                    mMarshalDummy,mMarshalDummy,mMarshalDummy,mMarshalDummy,mMarshalDummy,
                                                    mMarshalDummy,mMarshalDummy,mMarshalDummy,mMarshalDummy,mMarshalDummy,
                                                    mMarshalDummy,mMarshalDummy,mMarshalDummy,mMarshalDummy,mMarshalDummy,
                                                    mMarshalDummy );
    return ret;
}

int Stub_APIC_MineModel::Stub_APIC_MineModel_getCurrentSizeField_13( BLKS_COMMONID* type_id , APIC_MineModel* pc_APIC_MineModel, void* pt )
{
    // Param.
    int ret = 0;

    RENEW_FUNC_INFO();

    // Base Pre.
    BLKC_StubMethodTemplate::BLKD_StubParaType_pre( type_id , pc_APIC_MineModel , pt,
                                                    mMarshalDummy,mMarshalDummy,mMarshalDummy,mMarshalDummy,mMarshalDummy,
                                                    mMarshalDummy,mMarshalDummy,mMarshalDummy,mMarshalDummy,mMarshalDummy,
                                                    mMarshalDummy,mMarshalDummy,mMarshalDummy,mMarshalDummy,mMarshalDummy,
                                                    mMarshalDummy );

    // APIC_MineModel::getCurrentSizeField().
    ret = pc_APIC_MineModel->getCurrentSizeField( );

    // Base Post.
    BLKC_StubMethodTemplate::BLKD_StubParaType_post( type_id , pc_APIC_MineModel , pt, ret,
                                                    mMarshalDummy,mMarshalDummy,mMarshalDummy,mMarshalDummy,mMarshalDummy,
                                                    mMarshalDummy,mMarshalDummy,mMarshalDummy,mMarshalDummy,mMarshalDummy,
                                                    mMarshalDummy,mMarshalDummy,mMarshalDummy,mMarshalDummy,mMarshalDummy,
                                                    mMarshalDummy );
    return ret;
}

int Stub_APIC_MineModel::Stub_APIC_MineModel_getCurrentMinesField_14( BLKS_COMMONID* type_id , APIC_MineModel* pc_APIC_MineModel, void* pt )
{
    // Param.
    int ret = 0;

    RENEW_FUNC_INFO();

    // Base Pre.
    BLKC_StubMethodTemplate::BLKD_StubParaType_pre( type_id , pc_APIC_MineModel , pt,
                                                    mMarshalDummy,mMarshalDummy,mMarshalDummy,mMarshalDummy,mMarshalDummy,
                                                    mMarshalDummy,mMarshalDummy,mMarshalDummy,mMarshalDummy,mMarshalDummy,
                                                    mMarshalDummy,mMarshalDummy,mMarshalDummy,mMarshalDummy,mMarshalDummy,
                                                    mMarshalDummy );

    // APIC_MineModel::getCurrentMinesField().
    ret = pc_APIC_MineModel->getCurrentMinesField( );

    // Base Post.
    BLKC_StubMethodTemplate::BLKD_StubParaType_post( type_id , pc_APIC_MineModel , pt, ret,
                                                    mMarshalDummy,mMarshalDummy,mMarshalDummy,mMarshalDummy,mMarshalDummy,
                                                    mMarshalDummy,mMarshalDummy,mMarshalDummy,mMarshalDummy,mMarshalDummy,
                                                    mMarshalDummy,mMarshalDummy,mMarshalDummy,mMarshalDummy,mMarshalDummy,
                                                    mMarshalDummy );
    return ret;
}

void Stub_APIC_MineModel::Stub_APIC_MineModel_setBestTime_15( BLKS_COMMONID* type_id , APIC_MineModel* pc_APIC_MineModel, void* pt )
{
    // Param.
    BestTimeEntry entry;

    RENEW_FUNC_INFO();

    // Base Pre.
    BLKC_StubMethodTemplate::BLKD_StubParaType_pre( type_id , pc_APIC_MineModel , pt,
                                                    entry,mMarshalDummy,mMarshalDummy,mMarshalDummy,mMarshalDummy,
                                                    mMarshalDummy,mMarshalDummy,mMarshalDummy,mMarshalDummy,mMarshalDummy,
                                                    mMarshalDummy,mMarshalDummy,mMarshalDummy,mMarshalDummy,mMarshalDummy,
                                                    mMarshalDummy );

    // APIC_MineModel::setBestTime().
    pc_APIC_MineModel->setBestTime( entry );

    // Base Post.
    BLKC_StubMethodTemplate::BLKD_StubParaType_post( type_id , pc_APIC_MineModel , pt,
                                                    entry,mMarshalDummy,mMarshalDummy,mMarshalDummy,mMarshalDummy,
                                                    mMarshalDummy,mMarshalDummy,mMarshalDummy,mMarshalDummy,mMarshalDummy,
                                                    mMarshalDummy,mMarshalDummy,mMarshalDummy,mMarshalDummy,mMarshalDummy,
                                                    mMarshalDummy );
}