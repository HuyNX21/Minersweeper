#include "BoardGameContainerWidget.h"
#include "MineBoardGame.h"
#include "BestTimeEntry.h"
#include "BestTimesDialog.h"
#include "SidePanel.h"
#include <QMetaObject>
#include <QThread>

BoardGameContainerWidget::BoardGameContainerWidget(QWidget* parent)
    : QWidget(parent)
{
    auto* mainLayout = new QHBoxLayout(this);
    mainLayout->setContentsMargins(5, 5, 5, 5);
    mainLayout->setSpacing(5);

    // ===== Left: Board =====
    m_board = new MineBoardGame(this);

    // ===== Right: Side panel =====
    m_side = new SidePanel(this);

    // ===== Best Times Dialog =====
    m_bestTimesDialog = new BestTimesDialog(this);

    connect(m_side, &SidePanel::changeDifficultyRequested,
            this,   &BoardGameContainerWidget::changeDifficultyRequested);

    // ===== Assemble =====
    mainLayout->addWidget(m_board, 1);
    mainLayout->addWidget(m_side,  0);
}

void BoardGameContainerWidget::setBoardSize(int size)
{
    m_board->setBoardSize(size);
}

MineBoardGame* BoardGameContainerWidget::mineBoard() const
{
    return m_board;
}

SidePanel* BoardGameContainerWidget::sidePanel() const
{
    return m_side;
}

BestTimesDialog* BoardGameContainerWidget::bestTimesDialog() const
{
    return m_bestTimesDialog;
}

void BoardGameContainerWidget::showBestTimesRequested(const std::vector<BestTimeEntry> entry)
{
    if (QThread::currentThread() != thread())
    {
        QMetaObject::invokeMethod(this,
            [this, entry]() { showBestTimesRequested(entry); },
            Qt::QueuedConnection);
        return;
    }

    if (!m_bestTimesDialog)
        return;

    m_bestTimesDialog->showBestTimes(entry);
    m_bestTimesDialog->exec();
}

void BoardGameContainerWidget::showWinMode(const BestTimeEntry entry)
{
    if (QThread::currentThread() != thread())
    {
        QMetaObject::invokeMethod(this,
            [this, entry]() { showWinMode(entry); },
            Qt::QueuedConnection);
        return;
    }

    if (!m_bestTimesDialog)
        return;

    m_bestTimesDialog->enterWinMode(entry);
    m_bestTimesDialog->exec();
}