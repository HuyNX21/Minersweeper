#include "pch.h"
#include "MDLC_MineModel.h"
#include "MineSetting.h"

LIBC_List<APIC_MineModelObserver>   MDLC_MineModel::m_pc_MineModelList;

MDLC_MineModel::MDLC_MineModel()
{
    m_mineSetting = new MineSetting();
    m_bestTimesStorage= new BestTimesStorage();
}

MDLC_MineModel::~MDLC_MineModel()
{
    delete m_mineSetting;
    delete m_bestTimesStorage;
}

MDLC_MineModel* MDLC_MineModel::newInstance()
{
    static MDLC_MineModel c_Model;
    return &c_Model;
}

void MDLC_MineModel::setup(int rows, int cols, int mineCount)
{
    m_rows      = rows;
    m_cols      = cols;
    m_mineCount = mineCount;

    m_mineSetting->init(rows, cols);
    m_bestTimesStorage->load();

    m_state = GameState::NotStarted;
}

void MDLC_MineModel::startGame(int row, int col)
{
    m_mineSetting->calculateSafeZone(row, col, m_mineCount);
    m_mineSetting->placeMines(m_mineCount);
    m_mineSetting->calculateNumbers();

    setState(GameState::Running);
}

void MDLC_MineModel::setState(GameState state)
{
    if (m_state == state)
        return;

    m_state = state;
    APIC_MineModel::newInstance()->obs_gameStateChanged(m_state);
}

void MDLC_MineModel::req_openCell(int row, int col, void (*ans_cellOpened)(std::vector<PointCellOpened>, bool))
{
    if( ans_cellOpened != NULL )
    {
        void(*p)(std::vector<PointCellOpened>, bool) = reinterpret_cast< void(*)( std::vector<PointCellOpened>, bool ) >(ans_cellOpened);
        std::vector<PointCellOpened> openedCells;
        openedCells.clear();
        if (m_state == GameState::Lose || m_state == GameState::Win){
            (*p)(openedCells, false);
            return;
        }

        if (m_state == GameState::NotStarted) {
            startGame(row, col);
        }

        bool hitMine = m_mineSetting->openCell(row, col, openedCells);

        if (hitMine) {
            APIC_MineModel::newInstance()->obs_minesRevealed(row, col, m_mineSetting->allMines());
            setState(GameState::Lose);
            APIC_MineModel::newInstance()->obs_gameOver(false);
            (*p)(openedCells, false);
            return;
        }

        if (m_mineSetting->checkWin()) {
            setState(GameState::Win);
            APIC_MineModel::newInstance()->obs_gameOver(true);
            (*p)(openedCells, false);
            return;
        }

        (*p)(openedCells, true);
    }
    else
    {
        LOG_ERROR("ans_cellOpened is NULL");
    }
    
}

void MDLC_MineModel::attachObserver(APIC_MineModelObserver* pc_obs)
{
    if(NULL == pc_obs){
		LOG_ERROR("Assert Failed!");
	}

    m_pc_MineModelList.Lock();
	m_pc_MineModelList.add( pc_obs );
	m_pc_MineModelList.UnLock();
}

void MDLC_MineModel::detachObserver(APIC_MineModelObserver* pc_obs)
{
    if(NULL == pc_obs){
		LOG_ERROR("Assert Failed!");
	}

    m_pc_MineModelList.Lock();
	m_pc_MineModelList.del( pc_obs );
	m_pc_MineModelList.UnLock();
}

void MDLC_MineModel::obs_gameStateChanged(GameState state)
{
    m_pc_MineModelList.Lock();
	APIC_MineModelObserver* pc_MineModelObserver = m_pc_MineModelList.findFirst();
	while(NULL != pc_MineModelObserver){
		pc_MineModelObserver->obs_gameStateChanged(state);
		pc_MineModelObserver = m_pc_MineModelList.findNext();
	}
	m_pc_MineModelList.UnLock();
}

void MDLC_MineModel::req_toggleFlag(int row, int col, void (*ans_flagChanged)(int, int, bool, int, int, bool))
{
    if( ans_flagChanged != NULL )
    {
        void(*p)(int, int, bool, int, int, bool) = reinterpret_cast< void(*)(int, int, bool, int, int, bool) >(ans_flagChanged);
    
        if ((m_state == GameState::Lose || m_state == GameState::Win || m_state == GameState::Paused) ||
            (m_mineSetting->flagCount() + 1 > m_mineCount && !m_mineSetting->isFlagged(row, col)))
            {
                (*p)(row, col, false, m_mineSetting->flagCount(), m_mineCount, false);
                return;
            }

        bool flagged = m_mineSetting->toggleFlag(row, col);

        (*p)(row, col, flagged, m_mineSetting->flagCount(), m_mineCount, true);

    }
    else
    {
        LOG_ERROR("ans_flagChanged is NULL");
    }
}

GameState MDLC_MineModel::getState() const
{
    return m_state;
}

void MDLC_MineModel::obs_minesRevealed(int rowMineTriggered, int colMineTriggered, std::vector<std::pair<int,int>> mines)
{
    m_pc_MineModelList.Lock();
    APIC_MineModelObserver* pc_MineModelObserver = m_pc_MineModelList.findFirst();
    while(NULL != pc_MineModelObserver){
        pc_MineModelObserver->obs_minesRevealed(rowMineTriggered, colMineTriggered, mines);
        pc_MineModelObserver = m_pc_MineModelList.findNext();
    }
    m_pc_MineModelList.UnLock();
}

void MDLC_MineModel::obs_gameOver(bool win)
{
    m_pc_MineModelList.Lock();
    APIC_MineModelObserver* pc_MineModelObserver = m_pc_MineModelList.findFirst();
    while(NULL != pc_MineModelObserver){
        pc_MineModelObserver->obs_gameOver(win);
        pc_MineModelObserver = m_pc_MineModelList.findNext();
    }
    m_pc_MineModelList.UnLock();
}

std::vector<BestTimeEntry> MDLC_MineModel::getEntries() const
{
    return m_bestTimesStorage->entries();
}

void MDLC_MineModel::setBestTime(BestTimeEntry entry)
{
    m_bestTimesStorage->addEntry(entry);
    m_bestTimesStorage->sortEntries();
    m_bestTimesStorage->save();
}

int MDLC_MineModel::getCurrentSizeField() const
{
    return m_rows;
}

int MDLC_MineModel::getCurrentMinesField() const
{
    return m_mineCount;
}