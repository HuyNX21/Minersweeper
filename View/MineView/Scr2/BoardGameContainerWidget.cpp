#include "BoardGameContainerWidget.h"
#include "MineBoardGame.h"
#include "SidePanel.h"

BoardGameContainerWidget::BoardGameContainerWidget(QWidget* parent)
    : QWidget(parent)
{
    auto* mainLayout = new QHBoxLayout(this);
    mainLayout->setContentsMargins(5, 5, 5, 5);
    mainLayout->setSpacing(5);

    // ===== Left: Board =====
    m_board = new MineBoardGame(this);

    // ===== Right: Side panel =====
    m_side = new SidePanel(this);

    connect(m_side, &SidePanel::changeDifficultyRequested,
            this,   &BoardGameContainerWidget::changeDifficultyRequested);

    // ===== Assemble =====
    mainLayout->addWidget(m_board, 1);
    mainLayout->addWidget(m_side,  0);
}

void BoardGameContainerWidget::setBoardSize(int size)
{
    m_board->setBoardSize(size);
}

MineBoardGame* BoardGameContainerWidget::mineBoard() const
{
    return m_board;
}

SidePanel* BoardGameContainerWidget::sidePanel() const
{
    return m_side;
}