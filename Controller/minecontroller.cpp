#include "MineController.h"
#include "../View/mineview.h"
#include "../View/Scr2/mineboard.h"
#include "../View/Scr2/sidepanel.h"
#include "../Model/MineModel.h"

MineController::MineController(MineView* view, MineModel* model, QObject* parent)
    : QObject(parent)
    , m_view(view)
    , m_model(model)
{
    // ===== View → Controller =====
    connect(m_view, &MineView::modeSelected,
            this,   &MineController::onModeSelected);

    connect(m_view, &MineView::backRequested,
            this,   &MineController::onBackRequested);

    connect(m_view->mineBoard(), &MineBoard::cellClicked,
            this, &MineController::onCellClicked);

    // ===== Model → Controller =====
    connect(m_model, &MineModel::cellOpened,
            this,    &MineController::onCellOpened);

    connect(m_model, &MineModel::gameOver,
            this,    &MineController::onGameOver);

    connect(m_model, &MineModel::minesRevealed,
            this,    &MineController::onMinesRevealed);

    connect(m_view->sidePanel(), &SidePanel::pauseRequested,
            this, &MineController::onPauseRequested);

    connect(m_model, &MineModel::stateChanged,
            this,    &MineController::onGameStateChanged);

    connect(m_view->mineBoard(), &MineBoard::cellRightClicked,
            this, &MineController::onCellRightClicked);

    connect(m_model, &MineModel::flagChanged,
            this, &MineController::onFlagChanged);

    connect(m_model, &MineModel::flagCountChanged,
            this, &MineController::onFlagCountChanged);

    connect(m_view->sidePanel(), &SidePanel::startOverRequest,
            this, &MineController::onStartOverRequest);
}

void MineController::onModeSelected(int size, int mines)
{
    m_sizeOld = size;
    m_mineOld = mines;
    m_model->setup(size, size, mines);

    m_view->setBoardSize(size);
    m_view->mineBoard()->resetBoard();
    m_view->sidePanel()->resetClock();
    m_view->sidePanel()->setPauseButtonText("Pause");
    m_view->sidePanel()->setPauseEnabled(false);
    m_view->sidePanel()->setStartOverEnabled(false);
    m_view->sidePanel()->resetFlagCount(mines);
    m_view->showBoardScreen();
}


void MineController::onBackRequested()
{
    //
    if(m_model->getState() == GameState::Running || m_model->getState() == GameState::Paused)
    {
        if(m_view->sidePanel()->showConfirmNewGameDialog())
        {
            m_view->showSelectScreen();
            m_view->mineBoard()->showPausedOverlay(false);
        }
    }
    else if(m_model->getState() == GameState::NotStarted)
    {
        m_view->showSelectScreen();
        m_view->mineBoard()->showPausedOverlay(false);
    }
}

void MineController::onStartOverRequest()
{
    if(m_model->getState() == GameState::Running)
    {
        if(m_view->sidePanel()->showConfirmNewGameDialog())
        {
            onModeSelected(m_sizeOld, m_mineOld);
        }
    }
}

void MineController::onCellClicked(int row, int col)
{
    if (m_model->getState() == GameState::NotStarted) {
        m_view->sidePanel()->startClock();
        m_view->sidePanel()->setPauseEnabled(true);
        m_view->sidePanel()->setStartOverEnabled(true);
    }

    if (m_model->getState() == GameState::Paused)
        return;

    m_model->openCell(row, col);
}

void MineController::onCellOpened(int row, int col, int value)
{
    // value = số mìn xung quanh (0..8)
    m_view->mineBoard()->openCell(row, col, value);
}

void MineController::onGameOver(bool win)
{
    m_view->sidePanel()->pauseClock();

    //m_view->showGameOverDialog(win);
}

void MineController::onMinesRevealed(int rowMineTriggered, int colMineTriggered, const QVector<QPoint>& mines)
{
    auto* board = m_view->mineBoard();

    for (const QPoint& p : mines)
    {
        if(rowMineTriggered == p.x() && colMineTriggered == p.y())
        {
            board->revealMine(p.x(), p.y(), true);
        }
        else
        {
            board->revealMine(p.x(), p.y(), false);
        }
    }
}

void MineController::onPauseRequested()
{
    switch (m_model->getState()) {

    case GameState::Running:
        m_model->setState(GameState::Paused);
        m_view->sidePanel()->pauseClock();
        m_view->mineBoard()->showPausedOverlay(true);
        break;

    case GameState::Paused:
        m_model->setState(GameState::Running);
        m_view->sidePanel()->resumeClock();
        m_view->mineBoard()->showPausedOverlay(false);
        break;

    case GameState::Finished:
        m_view->showSelectScreen();
        m_view->mineBoard()->showPausedOverlay(false);
        break;

    default:
        break;
    }
}

void MineController::onGameStateChanged(GameState state)
{
    auto* side = m_view->sidePanel();

    switch (state) {
    case GameState::Running:
        side->setPauseButtonText("Pause");
        side->setPauseEnabled(true);
        break;

    case GameState::Paused:
        side->setPauseButtonText("Resume");
        side->setPauseEnabled(true);
        break;

    case GameState::Finished:
        side->setPauseButtonText("Change Difficulty");
        side->setPauseEnabled(true);
        break;

    case GameState::NotStarted:
        side->setPauseButtonText("Pause");
        side->setPauseEnabled(false);
        break;
    }
}

void MineController::onCellRightClicked(int row, int col)
{
    m_model->toggleFlag(row, col);
}

void MineController::onFlagChanged(int row, int col, bool flagged)
{
    m_view->mineBoard()->setFlag(row, col, flagged);
}

void MineController::onFlagCountChanged(int used, int total)
{
    m_view->sidePanel()->setFlagCount(used, total);
}
