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
}

void MineController::onModeSelected(int size, int mines)
{
    m_model->setup(size, size, mines);

    m_view->setBoardSize(size);
    m_view->mineBoard()->resetBoard();
    m_view->sidePanel()->resetClock();
    m_view->sidePanel()->setPauseButtonText("Pause");
    m_view->sidePanel()->setPauseEnabled(false);
    m_view->showBoardScreen();
}


void MineController::onBackRequested()
{
    m_view->showSelectScreen();
    m_view->mineBoard()->showPausedOverlay(false);
}

void MineController::onCellClicked(int row, int col)
{
    if (m_model->state() == MineModel::GameState::NotStarted) {
        m_view->sidePanel()->startClock();
        m_view->sidePanel()->setPauseEnabled(true);
    }

    if (m_model->state() == MineModel::GameState::Paused)
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
    if (m_model->state() == MineModel::GameState::Running) {
        m_model->setState(MineModel::GameState::Paused);
        m_view->sidePanel()->pauseClock();
        m_view->mineBoard()->showPausedOverlay(true);
        m_view->sidePanel()->setPauseButtonText("Resume");
    }
    else if (m_model->state() == MineModel::GameState::Paused) {
        m_model->setState(MineModel::GameState::Running);
        m_view->sidePanel()->resumeClock();
        m_view->mineBoard()->showPausedOverlay(false);
        m_view->sidePanel()->setPauseButtonText("Pause");
    }
}
