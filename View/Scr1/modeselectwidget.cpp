#include "modeselectwidget.h"
#include "boardselect.h"

#include <QResizeEvent>
#include <QDebug>

ModeSelectWidget::ModeSelectWidget(QWidget* parent)
    : QWidget(parent)
{
    m_board = new BoardSelect(this);

    const int minButtonSize = 160;
    const int minBoardSize  = minButtonSize * 2;

    setMinimumSize(minBoardSize, minBoardSize);

    // ⭐ FORWARD SIGNAL
    connect(m_board, &BoardSelect::modeSelected,
            this,    &ModeSelectWidget::modeSelected);
}

void ModeSelectWidget::resizeEvent(QResizeEvent* event)
{
    QWidget::resizeEvent(event);

    int side = qMin(width(), height());
    int minBoardSize = 160 * 2;
    side = qMax(side, minBoardSize);

    int x = (width()  - side) / 2;
    int y = (height() - side) / 2;

    m_board->setGeometry(x, y, side, side);
}
