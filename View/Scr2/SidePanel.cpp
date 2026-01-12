#include "SidePanel.h"


SidePanel::SidePanel(QWidget* parent)
    : QWidget(parent)
{
    setFixedWidth(200);

    auto* layout = new QVBoxLayout(this);
    layout->setContentsMargins(12, 12, 12, 12);
    layout->setSpacing(12);

    // ===== FLAG =====
    m_flagLabel = new QLabel("🏴", this);
    m_flagLabel->setAlignment(Qt::AlignCenter);
    m_flagLabel->setStyleSheet("font-size: 28px;");

    // ===== FLAG COUNT =====
    m_flagCountLabel = new QLabel("0 / 0", this);
    m_flagCountLabel->setAlignment(Qt::AlignCenter);
    m_flagCountLabel->setStyleSheet("font-size: 20px;");

    // ===== CLOCK ICON =====
    m_clockIcon = new QLabel("🕐", this);
    m_clockIcon->setAlignment(Qt::AlignCenter);
    m_clockIcon->setStyleSheet("font-size: 28px;");

    // ===== TIME LABEL =====
    m_timeLabel = new QLabel("00:00", this);
    m_timeLabel->setAlignment(Qt::AlignCenter);
    m_timeLabel->setStyleSheet("font-size: 20px;");

    layout->addWidget(m_flagLabel);
    layout->addWidget(m_flagCountLabel);
    layout->addSpacing(8);
    layout->addWidget(m_clockIcon);
    layout->addWidget(m_timeLabel);

    layout->addStretch();

    // ===== BUTTONS =====
    const int sizeButton = 75;

    m_btnStartOver          = new QPushButton("Start Over", this);
    m_btnBack               = new QPushButton("Change Diffculty", this);
    m_btnPause              = new QPushButton("Pause", this);

    for (auto* b : {m_btnStartOver, m_btnBack, m_btnPause}) {
        b->setMinimumSize(sizeButton, sizeButton);
        b->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
        layout->addWidget(b);
    }

    connect(m_btnStartOver, &QPushButton::clicked,
            this,           &SidePanel::startOverRequest);

    connect(m_btnBack,      &QPushButton::clicked,
            this,           &SidePanel::backRequested);

    connect(m_btnPause,     &QPushButton::clicked,
            this,           &SidePanel::pauseRequested);

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

void SidePanel::showConfirmNewGameDialog()
{
    QMessageBox msgBox(this);
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
        //startNewGame();
        qDebug() << "START NEW GAME";
    }
}

void SidePanel::setPauseButtonText(const QString& text)
{
    m_btnPause->setText(text);
}

void SidePanel::setPauseEnabled(bool enabled)
{
    m_btnPause->setEnabled(enabled);
}

void SidePanel::setStartOverEnabled(bool enabled)
{
    m_btnStartOver->setEnabled(enabled);
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
