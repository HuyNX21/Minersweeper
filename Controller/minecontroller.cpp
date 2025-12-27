#include "MineController.h"
#include "../View/mineview.h"

MineController::MineController(MineView* view)
    : m_view(view)
{
    connect(m_view, &MineView::modeSelected,
            this,   &MineController::onModeSelected);

    connect(m_view, &MineView::backRequested,
            this,   &MineController::onBackRequested);
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
