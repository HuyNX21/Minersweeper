#include "ButtonsSelectMode.h"

ButtonsSelectMode::ButtonsSelectMode(QWidget* parent)
    : QWidget(parent)
{
    auto *grid = new QGridLayout(this);
    grid->setContentsMargins(0, 0, 0, 0);
    grid->setSpacing(5);

    constexpr int buttonSize = 180;

    int fontSize = 15;
    QFont f;
    f.setBold(true);
    f.setWeight(QFont::Bold);
    f.setPixelSize(fontSize);

    auto *btn8 = new QPushButton(QObject::tr("8 x 8\n 10 mines"), this);
    auto *btn16 = new QPushButton(QObject::tr("16 x 16\n 40 mines"), this);
    auto *btn32 = new QPushButton(QObject::tr("32 x 32\n 199 mines"), this);
    auto *btnQ = new QPushButton(QObject::tr("?\n custom"), this);

    for (auto* b : {btn8, btn16, btn32, btnQ})
    {
        b->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        b->setFont(f);
        b->setStyleSheet("color: #333333;");
        b->setFixedSize(buttonSize, buttonSize);
    }

    grid->addWidget(btn8,  0, 0);
    grid->addWidget(btn16, 0, 1);
    grid->addWidget(btn32, 1, 0);
    grid->addWidget(btnQ,  1, 1);

    // ===== Intent only =====
    connect(btn8,  &QPushButton::clicked, this, &ButtonsSelectMode::mode8Requested);
    connect(btn16, &QPushButton::clicked, this, &ButtonsSelectMode::mode16Requested);
    connect(btn32, &QPushButton::clicked, this, &ButtonsSelectMode::mode32Requested);
    connect(btnQ,  &QPushButton::clicked, this, &ButtonsSelectMode::modeCustomRequested);
}