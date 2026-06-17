#include "BLKC_Common.h"

class APIC_MineModel;

class Stub_APIC_MineModel{
    public:
        Stub_APIC_MineModel(){}
        ~Stub_APIC_MineModel(){}
        static Stub_APIC_MineModel* newInstance();
	    void dispatch( BLKS_COMMONID* type_id , void* ObjectPt, void* pt );
        void Stub_APIC_MineModel_newInstance_01( BLKS_COMMONID* type_id , APIC_MineModel* pc_APIC_MineModel, void* pt );
        void Stub_APIC_MineModel_setup_02( BLKS_COMMONID* type_id , APIC_MineModel* pc_APIC_MineModel, void* pt );
        void Stub_APIC_MineModel_req_openCell_03( BLKS_COMMONID* type_id , APIC_MineModel* pc_APIC_MineModel, void* pt );
        void Stub_APIC_MineModel_attachObserver_04( BLKS_COMMONID* type_id , APIC_MineModel* pc_APIC_MineModel, void* pt );
        void Stub_APIC_MineModel_detachObserver_05( BLKS_COMMONID* type_id , APIC_MineModel* pc_APIC_MineModel, void* pt );
        void Stub_APIC_MineModel_obs_gameStateChanged_06( BLKS_COMMONID* type_id , APIC_MineModel* pc_APIC_MineModel, void* pt );
        void Stub_APIC_MineModel_req_toggleFlag_07( BLKS_COMMONID* type_id , APIC_MineModel* pc_APIC_MineModel, void* pt );
        GameState Stub_APIC_MineModel_getState_08( BLKS_COMMONID* type_id , APIC_MineModel* pc_APIC_MineModel, void* pt );
        void Stub_APIC_MineModel_setState_09( BLKS_COMMONID* type_id , APIC_MineModel* pc_APIC_MineModel, void* pt );
        void Stub_APIC_MineModel_obs_minesRevealed_10( BLKS_COMMONID* type_id , APIC_MineModel* pc_APIC_MineModel, void* pt );
        void Stub_APIC_MineModel_obs_gameOver_11( BLKS_COMMONID* type_id , APIC_MineModel* pc_APIC_MineModel, void* pt );

        static void Stub_ans_openCell__99(std::vector<PointCellOpened> openedCells, bool gameState);
        static void Stub_ans_toggleFlag__99(int row, int col, bool flag, int flagUsed, int totalMines, bool b_result);
};