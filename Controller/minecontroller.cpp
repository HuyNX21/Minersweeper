#include "MineController.h"
#include "../View/mineview.h"
#include "../View/Scr2/mineboard.h"

MineController::MineController(MineView* view)
    : m_view(view)
{
    connect(m_view, &MineView::modeSelected,
            this,   &MineController::onModeSelected);

    connect(m_view, &MineView::backRequested,
            this,   &MineController::onBackRequested);

    connect(m_view->board(), &MineBoard::cellClicked,
            this,  &MineController::onCellClicked);
}

void MineController::onModeSelected(int size)
{
    m_view->setBoardSize(size);
    m_view->showBoardScreen();
}

void MineController::onBackRequested()
{
    m_view->showSelectScreen();
}

void MineController::onCellClicked(int row, int col)
{
    qDebug() << "Cell clicked:" << row << col;
}
