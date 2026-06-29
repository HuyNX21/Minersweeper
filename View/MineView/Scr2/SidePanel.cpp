#include "SidePanel.h"


SidePanel::SidePanel(QWidget* parent)
    : QWidget(parent)
{
    auto* layout = new QVBoxLayout(this);
    layout->setContentsMargins(5, 10, 5, 0);
    layout->setSpacing(5);

    // ===== BLOCK FLAG =====
    auto *flagBlock = new QVBoxLayout;
    flagBlock->setSpacing(0);

    // ===== FLAG =====
    m_flagLabel = new QLabel("Flag", this);
    m_flagLabel->setAlignment(Qt::AlignHCenter);
    m_flagLabel->setStyleSheet("font-size: 25px;");

    // ===== FLAG COUNT =====
    m_flagCountLabel   = new QLabel("0 / 0", this);
    m_flagCountLabel->setAlignment(Qt::AlignHCenter);
    m_flagCountLabel->setStyleSheet("font-size: 15px;");

    flagBlock->addWidget(m_flagLabel);
    flagBlock->addWidget(m_flagCountLabel);

    // ===== BLOCK TIMER =====
    auto *timerBlock = new QVBoxLayout;
    timerBlock->setSpacing(0);

    // ===== CLOCK ICON =====
    m_clockIcon = new QLabel("Timer", this);
    m_clockIcon->setAlignment(Qt::AlignHCenter);
    m_clockIcon->setStyleSheet("font-size: 25px;");

    // ===== TIME LABEL =====
    m_timeLabel   = new QLabel("00:00", this);
    m_timeLabel->setAlignment(Qt::AlignHCenter);
    m_timeLabel->setStyleSheet("font-size: 15px;");

    timerBlock->addWidget(m_clockIcon);
    timerBlock->addWidget(m_timeLabel);

    auto *widgetContainer = new QWidget(this);
    auto *layoutContainer = new QVBoxLayout(widgetContainer);
    layoutContainer->setContentsMargins(0, 0, 0, 0);
    layoutContainer->setSpacing(10);
    layoutContainer->addLayout(flagBlock);
    layoutContainer->addLayout(timerBlock);

    layout->addWidget(widgetContainer);
    layout->addStretch();

    // ===== BUTTONS =====
    const int sizeButtonWidth = 140;
    const int sizeButtonHeight = 65;

    m_btnStartOver          = new QPushButton("Start Over", this);
    m_btnChangeDifficulty   = new QPushButton("Change Diffculty", this);
    m_btnPause              = new QPushButton("Pause", this);

    for (auto* b : {m_btnStartOver, m_btnChangeDifficulty, m_btnPause}) {
        b->setFixedSize(sizeButtonWidth, sizeButtonHeight);
    }

    auto *buttonsLayout = new QVBoxLayout;
    buttonsLayout->setContentsMargins(0, 0, 0, 0);
    buttonsLayout->setSpacing(10);
    buttonsLayout->addWidget(m_btnStartOver);
    buttonsLayout->addWidget(m_btnChangeDifficulty);
    buttonsLayout->addWidget(m_btnPause);

    layout->addLayout(buttonsLayout);
    setLayout(layout);
    setFixedWidth(150);

    connect(m_btnStartOver,             &QPushButton::clicked,
            this,                       &SidePanel::startOverRequest);

    connect(m_btnChangeDifficulty,      &QPushButton::clicked,
            this,                       &SidePanel::changeDifficultyRequested);

    connect(m_btnPause,                 &QPushButton::clicked,
            this,                       &SidePanel::pauseRequested);

    // ===== TIMER =====
    connect(&m_timer, &QTimer::timeout, this, [this]() {
        ++m_elapsedSec;
        int min = m_elapsedSec / 60;
        int sec = m_elapsedSec % 60;
        m_timeLabel->setText(
            QString("%1:%2")
                .arg(min, 2, 10, QChar('0'))
                .arg(sec, 2, 10, QChar('0'))
            );
    });

}

void SidePanel::setPauseEnabled(bool enabled)
{
    m_btnPause->setEnabled(enabled);
}

void SidePanel::setStartOverEnabled(bool enabled)
{
    m_btnStartOver->setEnabled(enabled);
}

void SidePanel::setPauseButtonText(const QString& text)
{
    m_btnPause->setText(text);
}

void SidePanel::setStartOverButtonText(const QString& text)
{
    m_btnStartOver->setText(text);
}

void SidePanel::setChangeDifficultyButtonText(const QString& text)
{
    m_btnChangeDifficulty->setText(text);
}

int SidePanel::getFinalTime()
{
    return m_elapsedSec;
}

void SidePanel::startClock()
{
    m_elapsedSec = 0;
    m_timeLabel->setText("00:00");
    m_timer.start(1000);
}

void SidePanel::pauseClock()
{
    m_timer.stop();
}

void SidePanel::resumeClock()
{
    if (!m_timer.isActive())
        m_timer.start(1000);
}

void SidePanel::resetClock()
{
    m_timer.stop();
    m_elapsedSec = 0;
    m_timeLabel->setText("00:00");
}

void SidePanel::resetFlagCount(int mines)
{
    m_flagCountLabel->setText(
        QString("0 / %1").arg(mines)
        );
}

void SidePanel::setFlagCount(int used, int total)
{
    m_flagCountLabel->setText(
        QString("%1 / %2").arg(used).arg(total)
        );
}

bool SidePanel::showConfirmNewGameDialog()
{
    QMessageBox msgBox(window());
    msgBox.setWindowTitle("Start New Game");
    msgBox.setText("Do you want to start a new game?");
    msgBox.setInformativeText(
        "If you start a new game, your current progress will be lost."
        );
    msgBox.setIcon(QMessageBox::Question);

    QPushButton* keepBtn =
        msgBox.addButton("Keep Current Game", QMessageBox::RejectRole);
    QPushButton* newBtn =
        msgBox.addButton("Start New Game", QMessageBox::AcceptRole);

    msgBox.setDefaultButton(keepBtn);

    msgBox.exec();

    if (msgBox.clickedButton() == newBtn) {
        qDebug() << "START NEW GAME";
        return true;
    }

    return false;
}