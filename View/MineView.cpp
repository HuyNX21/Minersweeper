#include "mineview.h"
#include "Scr1/modeselectwidget.h"
#include "Scr2/centralwidget.h"
#include "../Model/BestTimeEntry.h"

MineView::MineView(QWidget* parent)
    : QMainWindow(parent)
{
    resize(900, 700);
    m_stack = new QStackedWidget(this);
    setCentralWidget(m_stack);

    m_selectScreen = new ModeSelectWidget(this);
    m_boardScreen  = new CentralWidget(this);

    m_stack->addWidget(m_selectScreen); // index 0
    m_stack->addWidget(m_boardScreen);  // index 1

    showSelectScreen();

    // ===== Forward intent =====
    connect(m_selectScreen, &ModeSelectWidget::modeSelected,
            this,           &MineView::modeSelected);

    connect(m_boardScreen, &CentralWidget::changeDifficultyRequested,
            this,          &MineView::changeDifficultyRequested);
}

void MineView::showSelectScreen()
{
    m_stack->setCurrentIndex(0);
}

void MineView::showBoardScreen()
{
    m_stack->setCurrentIndex(1);
}

void MineView::setBoardSize(int size)
{
    m_boardScreen->setBoardSize(size);
}

MineBoard* MineView::mineBoard() const
{
    return m_boardScreen->mineBoard();
}

SidePanel* MineView::sidePanel() const
{
    return m_boardScreen->sidePanel();
}

void MineView::showBestTimesRequested(const QVector<BestTimeEntry>& entry)
{
    m_boardScreen->showBestTimesRequested(entry);
}
