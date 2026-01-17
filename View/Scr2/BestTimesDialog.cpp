#include "BestTimesDialog.h"

BestTimesDialog::BestTimesDialog(QWidget* parent)
    : QDialog(parent)
{
    setFixedSize(520, 520);
    setWindowFlags(Qt::Dialog | Qt::FramelessWindowHint);

    auto* rootLayout = new QVBoxLayout(this);
    rootLayout->setContentsMargins(0, 0, 0, 0);
    rootLayout->setSpacing(0);

    // ===== Header =====
    auto* headerWidget = new QWidget(this);
    headerWidget->setFixedHeight(44);
    headerWidget->setStyleSheet("background-color: #2b2b2b;");

    auto* headerLayout = new QHBoxLayout(headerWidget);
    headerLayout->setContentsMargins(12, 0, 12, 0);

    m_titleLabel = new QLabel("Best Times", headerWidget);
    m_titleLabel->setStyleSheet("color: white; font-weight: bold;");

    m_closeButton = new QPushButton("✕", headerWidget);
    m_closeButton->setFixedSize(24, 24);
    m_closeButton->setStyleSheet(
        "QPushButton { background: #e95420; color: white; border-radius: 12px; }"
        "QPushButton:hover { background: #ff6a3d; }"
        );

    connect(m_closeButton, &QPushButton::clicked,
            this, &QDialog::close);

    headerLayout->addWidget(m_titleLabel);
    headerLayout->addStretch();
    headerLayout->addWidget(m_closeButton);

    // ===== Separator =====
    auto* separator = new QFrame(this);
    separator->setFrameShape(QFrame::HLine);
    separator->setFrameShadow(QFrame::Sunken);

    // ===== Table =====
    m_table = new QTableWidget(0, 4, this);
    m_table->setHorizontalHeaderLabels(
        {"Rank", "Time", "Minefield", "Player"}
        );

    m_table->verticalHeader()->setVisible(false);
    m_table->horizontalHeader()->setStretchLastSection(true);
    m_table->horizontalHeader()->setDefaultAlignment(Qt::AlignCenter);
    m_table->setShowGrid(false);
    m_table->setEditTriggers(QAbstractItemView::NoEditTriggers);
    m_table->setSelectionMode(QAbstractItemView::NoSelection);
    m_table->setFocusPolicy(Qt::NoFocus);

    m_table->setStyleSheet(
        "QHeaderView::section { background: transparent; font-weight: bold; }"
        "QTableWidget { background: white; }"
        );

    // ===== Assemble =====
    rootLayout->addWidget(headerWidget);
    rootLayout->addWidget(separator);
    rootLayout->addWidget(m_table);
}


inline QString formatTime(int seconds)
{
    int min = seconds / 60;
    int sec = seconds % 60;
    return QString("%1 minutes %2 seconds").arg(min).arg(sec);
}

void BestTimesDialog::setBestTimes(const QVector<BestTimeEntry>& times)
{
    qDebug() << "times addr:" << &times;
    qDebug() << "times size:" << times.size();
    if (!m_table)
        return;

    m_table->clearContents();
    int a = times.size();
    m_table->setRowCount(times.size());

    for (int i = 0; i < times.size(); ++i)
    {
        const auto& t = times[i];

        auto* rankItem      = new QTableWidgetItem(QString::number(i + 1));
        auto* timeItem      = new QTableWidgetItem(formatTime(t.seconds));
        auto* minefieldItem = new QTableWidgetItem(t.minefield);
        auto* playerItem    = new QTableWidgetItem(t.playerName);

        rankItem->setTextAlignment(Qt::AlignCenter);
        timeItem->setTextAlignment(Qt::AlignCenter);
        minefieldItem->setTextAlignment(Qt::AlignCenter);
        playerItem->setTextAlignment(Qt::AlignCenter);

        m_table->setItem(i, 0, rankItem);
        m_table->setItem(i, 1, timeItem);
        m_table->setItem(i, 2, minefieldItem);
        m_table->setItem(i, 3, playerItem);
    }
}





