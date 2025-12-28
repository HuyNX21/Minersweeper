#include "CentralWidget.h"
#include "MineBoard.h"
#include "sidepanel.h"

#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPushButton>

CentralWidget::CentralWidget(QWidget* parent)
    : QWidget(parent)
{
    auto* mainLayout = new QHBoxLayout(this);
    mainLayout->setContentsMargins(8, 8, 8, 8);
    mainLayout->setSpacing(8);

    // ===== Left: Board =====
    m_board = new MineBoard(this);
    m_board->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    // ===== Right: Side panel =====
    m_side = new SidePanel(this);

    // Forward intent
    connect(m_side, &SidePanel::backRequested,
            this,   &CentralWidget::backRequested);

    // ===== Assemble =====
    mainLayout->addWidget(m_board, 1);
    mainLayout->addWidget(m_side);
}

void CentralWidget::setBoardSize(int size)
{
    m_board->setBoardSize(size);
}

MineBoard* CentralWidget::board() const
{
    return m_board;
}
