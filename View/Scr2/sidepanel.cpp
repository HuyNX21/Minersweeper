#include "sidepanel.h"
#include <QGridLayout>
#include <QPushButton>
#include <QVBoxLayout>

SidePanel::SidePanel(QWidget* parent)
    : QWidget(parent)
{
    const int sizeButton = 75;

    setFixedWidth(200);

    auto* layout = new QVBoxLayout(this);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->setSpacing(8);

    layout->addStretch();

    b1          = new QPushButton("x", this);
    m_btnBack   = new QPushButton("Back", this);
    b3          = new QPushButton("x", this);

    for (auto* b : {b1, m_btnBack, b3})
    {
        b->setMinimumSize(sizeButton, sizeButton);
        b->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
        layout->addWidget(b);
    }

    connect(m_btnBack, &QPushButton::clicked,
            this, &SidePanel::backRequested);
}
