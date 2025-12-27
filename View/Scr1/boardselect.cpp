#include "BoardSelect.h"
#include <QGridLayout>
#include <QPushButton>

BoardSelect::BoardSelect(QWidget* parent)
    : QWidget(parent)
{
    auto* grid = new QGridLayout(this);
    grid->setSpacing(5);
    grid->setContentsMargins(0, 0, 0, 0);

    auto* btn8  = new QPushButton(tr("8x8"), this);
    auto* btn16 = new QPushButton(tr("16x16"), this);
    auto* btn32 = new QPushButton(tr("32x32"), this);
    auto* btnQ  = new QPushButton(tr("?"), this);

    for (auto* b : {btn8, btn16, btn32, btnQ})
        b->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    grid->addWidget(btn8,  0, 0);
    grid->addWidget(btn16, 0, 1);
    grid->addWidget(btn32, 1, 0);
    grid->addWidget(btnQ,  1, 1);

    grid->setRowStretch(0, 1);
    grid->setRowStretch(1, 1);
    grid->setColumnStretch(0, 1);
    grid->setColumnStretch(1, 1);

    // ===== Intent only =====
    connect(btn8,  &QPushButton::clicked, this, &BoardSelect::mode8Requested);
    connect(btn16, &QPushButton::clicked, this, &BoardSelect::mode16Requested);
    connect(btn32, &QPushButton::clicked, this, &BoardSelect::mode32Requested);
}
