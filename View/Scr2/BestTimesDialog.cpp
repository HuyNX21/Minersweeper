#include "BestTimesDialog.h"

BestTimesDialog::BestTimesDialog(QWidget* parent)
    : QDialog(parent)
{
    setWindowTitle(tr("Best Times"));
    setModal(true);
    resize(520, 360);

    auto* mainLayout = new QVBoxLayout(this);
    mainLayout->setContentsMargins(12, 12, 12, 12);
    mainLayout->setSpacing(8);

    // ===== Title =====
    auto* title = new QLabel(tr("Best Times"), this);
    QFont titleFont = title->font();
    titleFont.setBold(true);
    titleFont.setPointSize(titleFont.pointSize() + 2);
    title->setFont(titleFont);
    title->setAlignment(Qt::AlignCenter);

    mainLayout->addWidget(title);

    // ===== Table =====
    m_table = new QTableWidget(this);
    m_table->setColumnCount(4);
    m_table->setHorizontalHeaderLabels(
        { tr("Rank"), tr("Time"), tr("Minefield"), tr("Player") });

    m_table->horizontalHeader()->setStretchLastSection(true);
    m_table->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    m_table->verticalHeader()->setVisible(false);
    m_table->setSelectionMode(QAbstractItemView::NoSelection);
    m_table->setEditTriggers(QAbstractItemView::NoEditTriggers);

    mainLayout->addWidget(m_table, 1);

    // ===== Bottom Bar =====
    auto* bottomLayout = new QHBoxLayout;
    bottomLayout->addStretch();

    m_actionButton = new QPushButton(tr("Exit"), this);
    m_actionButton->setFixedWidth(80);

    bottomLayout->addWidget(m_actionButton);
    mainLayout->addLayout(bottomLayout);

    connect(m_actionButton, &QPushButton::clicked,
            this, &BestTimesDialog::onDoneClicked);
}

inline QString formatTime(int seconds)
{
    int min = seconds / 60;
    int sec = seconds % 60;
    return QString("%1 minutes %2 seconds").arg(min).arg(sec);
}

static int parseTime(const QString& text)
{
    const QStringList parts = text.split(':');
    if (parts.size() != 2)
        return 0;

    const int minutes = parts[0].toInt();
    const int seconds = parts[1].toInt();

    return minutes * 60 + seconds;
}

void BestTimesDialog::showBestTimes(const QVector<BestTimeEntry>& times)
{
    m_table->setRowCount(0);

    for (int i = 0; i < times.size(); ++i)
    {
        const auto& t = times[i];
        const int row = m_table->rowCount();
        m_table->insertRow(row);

        auto* rankItem = new QTableWidgetItem(QString::number(row + 1));
        auto* timeItem = new QTableWidgetItem(formatTime(t.seconds));
        auto* mineItem = new QTableWidgetItem(t.minefield);
        auto* playItem = new QTableWidgetItem(t.playerName);

        rankItem->setTextAlignment(Qt::AlignCenter);
        timeItem->setTextAlignment(Qt::AlignCenter);
        mineItem->setTextAlignment(Qt::AlignCenter);
        playItem->setTextAlignment(Qt::AlignCenter);

        m_table->setItem(row, 0, rankItem);
        m_table->setItem(row, 1, timeItem);
        m_table->setItem(row, 2, mineItem);
        m_table->setItem(row, 3, playItem);
    }

    m_mode = Mode::View;
    m_entryRow = -1;
    updateUiForMode();
}

void BestTimesDialog::enterWinMode(const BestTimeEntry& entry)
{
    m_mode = Mode::Entry;

    const int row = m_table->rowCount();
    m_entryRow = row;
    m_table->insertRow(row);

    auto* rankItem = new QTableWidgetItem(QString::number(row + 1));
    auto* timeItem = new QTableWidgetItem(formatTime(entry.seconds));
    auto* mineItem = new QTableWidgetItem(entry.minefield);

    rankItem->setTextAlignment(Qt::AlignCenter);
    timeItem->setTextAlignment(Qt::AlignCenter);
    mineItem->setTextAlignment(Qt::AlignCenter);

    auto* playerEdit = new QLineEdit(this);
    playerEdit->setPlaceholderText(tr("Enter your name"));
    playerEdit->setMaxLength(16);

    m_table->setItem(row, 0, rankItem);
    m_table->setItem(row, 1, timeItem);
    m_table->setItem(row, 2, mineItem);
    m_table->setCellWidget(row, 3, playerEdit);

    m_table->scrollToBottom();
    playerEdit->setFocus();

    updateUiForMode();
}

void BestTimesDialog::updateUiForMode()
{
    if (m_mode == Mode::Entry)
    {
        m_actionButton->setText(tr("Done"));
    }
    else
    {
        m_actionButton->setText(tr("Exit"));
    }
}

void BestTimesDialog::onDoneClicked()
{
    if (m_mode == Mode::View)
    {
        reject();
        return;
    }

    auto* editor = qobject_cast<QLineEdit*>(
        m_table->cellWidget(m_entryRow, 3));

    if (!editor)
        return;

    const QString playerName = editor->text().trimmed();
    if (playerName.isEmpty())
        return;

    BestTimeEntry entry;
    entry.seconds    = parseTime(m_table->item(m_entryRow, 1)->text());
    entry.minefield  = m_table->item(m_entryRow, 2)->text();
    entry.playerName = playerName;

    emit entryConfirmed(entry);
    accept();
}





