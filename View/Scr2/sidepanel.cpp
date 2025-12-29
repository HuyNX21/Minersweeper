#include "sidepanel.h"
#include <QGridLayout>
#include <QPushButton>
#include <QVBoxLayout>

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

    // ===== CLOCK ICON =====
    m_clockIcon = new QLabel("🕐", this);
    m_clockIcon->setAlignment(Qt::AlignCenter);
    m_clockIcon->setStyleSheet("font-size: 28px;");

    // ===== TIME LABEL =====
    m_timeLabel = new QLabel("00:00", this);
    m_timeLabel->setAlignment(Qt::AlignCenter);
    m_timeLabel->setStyleSheet("font-size: 20px;");

    layout->addWidget(m_flagLabel);
    layout->addSpacing(8);
    layout->addWidget(m_clockIcon);
    layout->addWidget(m_timeLabel);

    layout->addStretch();

    // ===== BUTTONS =====
    const int sizeButton = 75;

    b1          = new QPushButton("x", this);
    m_btnBack   = new QPushButton("Back", this);
    m_pauseBtn  = new QPushButton("Pause", this);

    for (auto* b : {b1, m_btnBack, m_pauseBtn}) {
        b->setMinimumSize(sizeButton, sizeButton);
        b->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
        layout->addWidget(b);
    }

    connect(m_btnBack,  &QPushButton::clicked,
            this,       &SidePanel::backRequested);

    connect(m_pauseBtn, &QPushButton::clicked,
            this,       &SidePanel::pauseRequested);

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

void SidePanel::setPauseButtonText(const QString& text)
{
    m_pauseBtn->setText(text);
}

void SidePanel::setPauseEnabled(bool enabled)
{
    m_pauseBtn->setEnabled(enabled);
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

