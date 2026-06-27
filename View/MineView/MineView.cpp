#include "MineView.h"
#include "BoardSellectModeWidget.h"
#include "BoardGameContainerWidget.h"
#include "BestTimesDialog.h"
#include "BestTimeEntry.h"

MineView::MineView(QWidget* parent)
    : QMainWindow(parent)
{
    setWindowTitle("Minesweeper");

    setWindowFlags(windowFlags() & ~Qt::WindowMaximizeButtonHint);

    m_stack = new QStackedWidget(this);
    setCentralWidget(m_stack);

    m_selectScreen = new BoardSellectModeWidget(this);
    m_boardScreen  = new BoardGameContainerWidget(this);

    m_stack->addWidget(m_selectScreen); // index 0
    m_stack->addWidget(m_boardScreen);  // index 1

    showSelectScreen();
    // showBoardScreen();

}

void MineView::clearFixedSize()
{
    this->setMinimumSize(QSize(0, 0));
    this->setMaximumSize(QSize(QWIDGETSIZE_MAX, QWIDGETSIZE_MAX));
}

void MineView::showSelectScreen()
{
    m_stack->setCurrentIndex(0);
    this->setFixedSize(DEFAULT_SELLECT_MODE_SIZE, DEFAULT_SELLECT_MODE_SIZE);
}

void MineView::showBoardScreen()
{
    m_stack->setCurrentIndex(1);

    this->adjustSize();
    this->setFixedSize(size());
}

void MineView::setBoardSize(int size)
{
    m_boardScreen->setBoardSize(size);
}

MineBoardGame* MineView::mineBoard() const
{
    return m_boardScreen->mineBoard();
}

SidePanel* MineView::sidePanel() const
{
    return m_boardScreen->sidePanel();
}

BoardSellectModeWidget* MineView::sellectBoard() const
{
    return m_selectScreen;
}

BestTimesDialog* MineView::bestTimesDialog() const
{
    return m_boardScreen->bestTimesDialog();
}

void MineView::showBestTimesRequested(const std::vector<BestTimeEntry> entry)
{
    m_boardScreen->showBestTimesRequested(entry);
}

void MineView::showWinMode(const BestTimeEntry entry)
{
    m_boardScreen->showWinMode(entry);
}