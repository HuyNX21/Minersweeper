#include "CustomGameDialog.h"

#include <QFormLayout>
#include <QPushButton>
#include <QSpinBox>
#include <QVBoxLayout>
#include <QLabel>

CustomGameDialog::CustomGameDialog(QWidget *parent)
    : QDialog(parent)
{
    setupUi();

    updateMinePercentLimit(m_sizeSpin->value());

    if (parent)
    {
        move(parent->geometry().center() - rect().center());
    }
}

void CustomGameDialog::setupUi()
{
    setWindowTitle("Custom Game");
    setModal(true);
    setFixedSize(360, 220);

    setStyleSheet(
        "QDialog {"
        "    background:white;"
        "    border:1px solid #909090;"
        "}"
    );

    m_sizeLabel = new QLabel("Width && Height");
    m_percentLabel = new QLabel("Number of mines");
    m_percentLabel->setContentsMargins(0, 5, 0, 0);

    m_sizeSpin = new QSpinBox;
    m_sizeSpin->setRange(5, 32);
    m_sizeSpin->setValue(8);

    m_percentSpin = new QSpinBox;

    // m_sizeSpin->setFixedWidth(160);
    // m_percentSpin->setFixedWidth(160);

    m_mineHintLabel = new QLabel;
    QFont hintFont = m_mineHintLabel->font();
    hintFont.setPointSize(9);
    m_mineHintLabel->setFont(hintFont);
    m_mineHintLabel->setStyleSheet("color: gray;");

    m_playButton = new QPushButton("Play Game");
    m_cancelButton = new QPushButton("Cancel");

    m_playButton->setMinimumHeight(34);
    m_cancelButton->setMinimumHeight(34);

    m_playButton->setStyleSheet(
        "background:#18A62B;"
        "color:white;"
        "border:1px solid #11851f;"
        "border-radius:3px;"
    );

    //-------------------------------------------------
    // Left column
    //-------------------------------------------------

    auto *labelLayout = new QVBoxLayout;
    labelLayout->setSpacing(20);

    labelLayout->addWidget(m_sizeLabel);
    labelLayout->addSpacing(6);
    labelLayout->addWidget(m_percentLabel);
    labelLayout->addStretch();

    //-------------------------------------------------
    // Right column
    //-------------------------------------------------

    auto *editLayout = new QVBoxLayout;
    editLayout->setSpacing(6);

    editLayout->addWidget(m_sizeSpin);

    editLayout->addWidget(m_percentSpin);
    editLayout->addWidget(m_mineHintLabel);

    editLayout->addStretch();

    //-------------------------------------------------
    // Form
    //-------------------------------------------------

    auto *formLayout = new QGridLayout;
    formLayout->setContentsMargins(0, 0, 0, 0);
    formLayout->setHorizontalSpacing(15);
    formLayout->setVerticalSpacing(6);

    formLayout->setColumnMinimumWidth(0, 130);

    m_sizeSpin->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    m_percentSpin->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);

    formLayout->addWidget(m_sizeLabel,      0, 0, Qt::AlignLeft | Qt::AlignVCenter);
    formLayout->addWidget(m_sizeSpin,       0, 1);

    formLayout->addWidget(m_percentLabel,   1, 0, Qt::AlignLeft | Qt::AlignTop);
    formLayout->addWidget(m_percentSpin,    1, 1);
    formLayout->addWidget(m_mineHintLabel,  2, 1, Qt::AlignLeft);

    //-------------------------------------------------
    // Main
    //-------------------------------------------------

    auto *mainLayout = new QVBoxLayout(this);

    mainLayout->setContentsMargins(20, 20, 20, 20);
    mainLayout->setSpacing(10);

    mainLayout->addLayout(formLayout);

    mainLayout->addSpacing(10);

    m_playButton->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    m_cancelButton->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);

    mainLayout->addWidget(m_playButton);
    mainLayout->addWidget(m_cancelButton);

    connect(m_playButton, &QPushButton::clicked,
            this, &QDialog::accept);

    connect(m_cancelButton, &QPushButton::clicked,
            this, &QDialog::reject);

    connect(m_sizeSpin,
            QOverload<int>::of(&QSpinBox::valueChanged),
            this,
            &CustomGameDialog::updateMinePercentLimit);

    updateMinePercentLimit(m_sizeSpin->value());
}

int CustomGameDialog::boardWidthHeight() const
{
    return m_sizeSpin->value();
}

int CustomGameDialog::minePercent() const
{
    return m_percentSpin->value();
}

void CustomGameDialog::setBoardSize(int size)
{
    m_sizeSpin->setValue(size);
}

void CustomGameDialog::setMinePercent(int percent)
{
    m_percentSpin->setValue(percent);
}

void CustomGameDialog::updateMinePercentLimit(int boardSize)
{
    int maxMine = ((boardSize * boardSize - 1) - (boardSize * 2));
    int minMine = 10;

    if (boardSize <= 8)
    {
        minMine = 10;
    }
    else if (boardSize <= 16)
    {
        minMine = 40;
    }
    else
    {
        minMine = 80;
    }

    m_percentSpin->setRange(minMine, maxMine);

    if (m_percentSpin->value() < minMine)
    {
        m_percentSpin->setValue(minMine);
    }

    m_mineHintLabel->setText(
        QString("Allowed: %1 ~ %2 mines")
            .arg(minMine)
            .arg(maxMine));
}