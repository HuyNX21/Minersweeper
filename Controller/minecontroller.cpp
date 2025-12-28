#include "MineController.h"
#include "../View/mineview.h"
#include "../View/Scr2/mineboard.h"
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

    connect(m_view->board(), &MineBoard::cellClicked,
            this, &MineController::onCellClicked);

    // ===== Model → Controller =====
    connect(m_model, &MineModel::cellOpened,
            this,    &MineController::onCellOpened);

    connect(m_model, &MineModel::gameOver,
            this,    &MineController::onGameOver);

    connect(m_model, &MineModel::minesRevealed,
            this,    &MineController::onMinesRevealed);
}

void MineController::onModeSelected(int size, int mines)
{
    m_model->setup(size, size, mines);

    m_view->setBoardSize(size);
    m_view->board()->resetBoard();
    m_view->showBoardScreen();
}


void MineController::onBackRequested()
{
    m_view->showSelectScreen();
}

void MineController::onCellClicked(int row, int col)
{
    m_model->openCell(row, col);
}

void MineController::onCellOpened(int row, int col, int value)
{
    // value = số mìn xung quanh (0..8)
    m_view->board()->openCell(row, col, value);
}

void MineController::onGameOver(bool win)
{
    //m_view->showGameOverDialog(win);
}

void MineController::onMinesRevealed(int rowMineTriggered, int colMineTriggered, const QVector<QPoint>& mines)
{
    auto* board = m_view->board();

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
