#include "BoardSellectModeWidget.h"
#include "ButtonsSelectMode.h"

BoardSellectModeWidget::BoardSellectModeWidget(QWidget* parent)
    : QWidget(parent)
{
    setupBoardSelect();

    // ===== Aggregate UI intent =====
    connect(m_button, &ButtonsSelectMode::mode8Requested,
            this,     [this]() { emit modeSelected(8, 10); });

    connect(m_button, &ButtonsSelectMode::mode16Requested,
            this,     [this]() { emit modeSelected(16, 40); });

    connect(m_button, &ButtonsSelectMode::mode32Requested,
            this,     [this]() { emit modeSelected(32, 99); });
}

void BoardSellectModeWidget::setupBoardSelect()
{
    m_button = new ButtonsSelectMode();

    auto *centerLayout = new QVBoxLayout(this);
    centerLayout->setContentsMargins(0, 0, 0, 0);

    auto *rowLayout = new QHBoxLayout;
    rowLayout->setContentsMargins(0, 0, 0, 0);
    rowLayout->addStretch();

    rowLayout->addWidget(m_button);
    rowLayout->addStretch();

    centerLayout->addStretch();
    centerLayout->addLayout(rowLayout);
    centerLayout->addStretch();
}