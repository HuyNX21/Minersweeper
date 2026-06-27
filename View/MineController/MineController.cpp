#include "MineController.h"
#include "MineView.h"
#include "MineBoardGame.h"
#include "SidePanel.h"
#include "BoardSellectModeWidget.h"
#include "BestTimesDialog.h"

MineController* MineController::s_instance = nullptr;

MineController* MineController::initInstance(MineView* view, QObject* parent)
{
    if (s_instance == nullptr) {
        s_instance = new MineController(view, parent);
    }
    return s_instance;
}

MineController* MineController::getInstance()
{
    return s_instance;
}

void MineController::deleteInstance()
{
    delete s_instance;
    s_instance = nullptr;
}

MineController::MineController(MineView* view, QObject* parent)
    : QObject(parent)
    , m_view(view)
{
    m_observer.initClass();

    // ===== View -> Controller =====
    connect(m_view->sellectBoard(), &BoardSellectModeWidget::modeSelected,
            this,   &MineController::onModeSelected);

    connect(m_view->mineBoard(), &MineBoardGame::cellClicked,
            this, &MineController::onCellClicked);

    connect(m_view->mineBoard(), &MineBoardGame::cellRightClicked,
            this, &MineController::onCellRightClicked);

    connect(m_view->sidePanel(), &SidePanel::startOverRequest,
            this, &MineController::onStartOverRequested);

    connect(m_view->sidePanel(), &SidePanel::changeDifficultyRequested,
            this,   &MineController::onChangeDifficultyRequested);

    connect(m_view->sidePanel(), &SidePanel::pauseRequested,
            this, &MineController::onPauseRequested);

    connect(m_view->bestTimesDialog(), &BestTimesDialog::entryConfirmed,
            this, &MineController::onBestTimeConfirmed);

    // ===== Model -> Controller =====

    
}

MineController::~MineController()
{
}

void MineController::onModeSelected(int size, int mines)
{
    this->setOldInfo(size, mines);
    Proxy_APIC_MineModel::newInstance()->setup(size, size, mines);

    m_view->clearFixedSize();
    m_view->setBoardSize(size);
    m_view->mineBoard()->resetBoard();
    m_view->sidePanel()->resetClock();
    m_view->sidePanel()->setPauseButtonText("Pause");
    m_view->sidePanel()->setPauseEnabled(false);
    m_view->sidePanel()->setStartOverButtonText("Start Over");
    m_view->sidePanel()->setStartOverEnabled(false);
    m_view->sidePanel()->setChangeDifficultyButtonText("Change Difficulty");
    m_view->sidePanel()->resetFlagCount(mines);

    m_view->showBoardScreen();
}

void MineController::onStartOverRequested()
{
    GameState state = Proxy_APIC_MineModel::newInstance()->getState();

    if(state == GameState::Running || state == GameState::Paused)
    {
        if(m_view->sidePanel()->showConfirmNewGameDialog())
        {
            onModeSelected(m_sizeOld, m_minesOld);

            if(state == GameState::Paused)
            {
                m_view->mineBoard()->showPausedOverlay(false);
            }
        }
    }
    else if(state == GameState::Win || state == GameState::Lose)
    {
        onModeSelected(m_sizeOld, m_minesOld);
    }
}

void MineController::onChangeDifficultyRequested()
{
    GameState state = Proxy_APIC_MineModel::newInstance()->getState();

    if (state == GameState::Running || state == GameState::Paused)
    {
        if(m_view->sidePanel()->showConfirmNewGameDialog())
        {
            m_view->showSelectScreen();

            if (state == GameState::Paused)
                m_view->mineBoard()->showPausedOverlay(false);
        }
    }
    else if (state == GameState::NotStarted)
    {
        m_view->showSelectScreen();
    }
    else
    {
        //GameState::Finished
        m_view->showBestTimesRequested(Proxy_APIC_MineModel::newInstance()->getEntries());
    }
}

void MineController::onPauseRequested()
{
    switch (Proxy_APIC_MineModel::newInstance()->getState()) {

    case GameState::Running:
        Proxy_APIC_MineModel::newInstance()->setState(GameState::Paused);
        m_view->sidePanel()->pauseClock();
        m_view->mineBoard()->showPausedOverlay(true);
        break;

    case GameState::Paused:
        Proxy_APIC_MineModel::newInstance()->setState(GameState::Running);
        m_view->sidePanel()->resumeClock();
        m_view->mineBoard()->showPausedOverlay(false);
        break;

    case GameState::Lose:
        m_view->showSelectScreen();
        m_view->mineBoard()->showPausedOverlay(false);
        break;

    case GameState::Win:
        m_view->showSelectScreen();
        m_view->mineBoard()->showPausedOverlay(false);
        break;

    default:
        break;
    }
}

void MineController::onCellClicked(int row, int col)
{
    if (Proxy_APIC_MineModel::newInstance()->getState() == GameState::NotStarted) {
        m_view->sidePanel()->startClock();
        m_view->sidePanel()->setPauseEnabled(true);
        m_view->sidePanel()->setStartOverEnabled(true);
    }

    if (Proxy_APIC_MineModel::newInstance()->getState() == GameState::Paused)
        return;

    Proxy_APIC_MineModel::newInstance()->req_openCell(row, col, ans_cellOpened);
}

void MineController::ans_cellOpened(std::vector<PointCellOpened> openedCells, bool stateGameOver)
{
    if(stateGameOver)
    {
        for (const auto& cell : openedCells) {
            MineController::getInstance()->m_view->mineBoard()->openCell(cell.x, cell.y, cell.adjacentValue);
        }
    }
    else
    {
        // Do nothing
    }
    
}

void MineController::MCC_MineControllerObserver::initClass()
{
    Proxy_APIC_MineModel::newInstance()->attachObserver(this);
}

void MineController::MCC_MineControllerObserver::obs_gameStateChanged(GameState state)
{
    switch (state) {
    case GameState::Running:
        MineController::getInstance()->m_view->sidePanel()->setPauseButtonText("Pause");
        MineController::getInstance()->m_view->sidePanel()->setPauseEnabled(true);
        break;

    case GameState::Paused:
        MineController::getInstance()->m_view->sidePanel()->setPauseButtonText("Resume");
        MineController::getInstance()->m_view->sidePanel()->setPauseEnabled(true);
        break;

    case GameState::Lose:
        MineController::getInstance()->m_view->sidePanel()->setPauseButtonText("Change Difficulty");
        MineController::getInstance()->m_view->sidePanel()->setPauseEnabled(true);
        MineController::getInstance()->m_view->sidePanel()->setStartOverButtonText("Play Again");
        MineController::getInstance()->m_view->sidePanel()->setStartOverEnabled(true);
        MineController::getInstance()->m_view->sidePanel()->setChangeDifficultyButtonText("Best Times");
        break;

    case GameState::Win:
        MineController::getInstance()->m_view->sidePanel()->setPauseButtonText("Change Difficulty");
        MineController::getInstance()->m_view->sidePanel()->setPauseEnabled(true);
        MineController::getInstance()->m_view->sidePanel()->setStartOverButtonText("Play Again");
        MineController::getInstance()->m_view->sidePanel()->setStartOverEnabled(true);
        MineController::getInstance()->m_view->sidePanel()->setChangeDifficultyButtonText("Best Times");
        break;

    case GameState::NotStarted:
        MineController::getInstance()->m_view->sidePanel()->setPauseButtonText("Pause");
        MineController::getInstance()->m_view->sidePanel()->setPauseEnabled(false);
        break;
    }
}

void MineController::onCellRightClicked(int row, int col)
{
    Proxy_APIC_MineModel::newInstance()->req_toggleFlag(row, col, ans_flagChanged);
}

void MineController::ans_flagChanged(int row, int col, bool flagged, int flagUsed, int totalMines, bool b_result)
{
    if(b_result)
    {
        MineController::getInstance()->m_view->mineBoard()->setFlag(row, col, flagged);
        MineController::getInstance()->m_view->sidePanel()->setFlagCount(flagUsed, totalMines);
    }
}

void MineController::setOldInfo(int size, int mines)
{
    m_sizeOld = size;
    m_minesOld = mines;
}

void MineController::MCC_MineControllerObserver::obs_minesRevealed(int rowMineTriggered, int colMineTriggered, std::vector<std::pair<int,int>> mines)
{
    auto* board = MineController::getInstance()->m_view->mineBoard();

    for (const std::pair<int,int>& p : mines)
    {
        if(rowMineTriggered == p.first && colMineTriggered == p.second)
        {
            board->revealMine(p.first, p.second, true);
        }
        else
        {
            board->revealMine(p.first, p.second, false);
        }
    }
}

void MineController::MCC_MineControllerObserver::obs_gameOver(bool win)
{
    MineController::getInstance()->m_view->sidePanel()->pauseClock();

    if(win)
    {
        int finalTime = MineController::getInstance()->m_view->sidePanel()->getFinalTime();

        BestTimeEntry entry;
        entry.seconds    = finalTime;
        entry.size       = Proxy_APIC_MineModel::newInstance()->getCurrentSizeField();
        entry.mines      = Proxy_APIC_MineModel::newInstance()->getCurrentMinesField();

        MineController::getInstance()->m_view->showWinMode(entry);
    }
}

void MineController::onBestTimeConfirmed(const BestTimeEntry entry)
{
    Proxy_APIC_MineModel::newInstance()->setBestTime(entry);
}