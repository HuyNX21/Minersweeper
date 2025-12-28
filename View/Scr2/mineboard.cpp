#include "mineboard.h"

#include <QGridLayout>
#include <QPushButton>
#include <QResizeEvent>
#include <QtMath>
#include <QDebug>

MineBoard::MineBoard(QWidget* parent)
    : QWidget(parent)
{
    m_grid = new QGridLayout(this);
    m_grid->setSpacing(0);
    m_grid->setContentsMargins(0, 0, 0, 0);

    setBoardSize(8);
}

void MineBoard::setBoardSize(int size)
{
    if (size <= 0 || size == m_boardSize)
        return;

    m_boardSize = size;
    rebuildBoard();

    const int minSide = MinButtonSize * m_boardSize;
    setMinimumSize(minSide, minSide);

    updateGeometry();
}

void MineBoard::rebuildBoard()
{
    while (QLayoutItem* item = m_grid->takeAt(0))
    {
        delete item->widget();
        delete item;
    }
    qDebug() << m_boardSize;
    m_buttons.resize(m_boardSize);
    for (int r = 0; r < m_boardSize; ++r)
    {
        m_buttons[r].resize(m_boardSize);
        for (int c = 0; c < m_boardSize; ++c)
        {
            auto* btn = new QPushButton(this);

            btn->setSizePolicy(QSizePolicy::Ignored,
                               QSizePolicy::Ignored);

            connect(btn, &QPushButton::clicked,
                    this, [this, r, c]() {
                        emit cellClicked(r, c);
                    });

            m_grid->addWidget(btn, r, c);

            m_buttons[r][c] = btn;
        }
    }
}

// ===== Qt layout contract =====

bool MineBoard::hasHeightForWidth() const
{
    return true;
}

int MineBoard::heightForWidth(int w) const
{
    const int minSide = MinButtonSize * m_boardSize;
    return qMax(w, minSide);
}

QSize MineBoard::sizeHint() const
{
    const int side = MinButtonSize * m_boardSize;
    return QSize(side, side);
}

QSize MineBoard::minimumSizeHint() const
{
    const int side = MinButtonSize * m_boardSize;
    return QSize(side, side);
}

void MineBoard::resizeEvent(QResizeEvent* event)
{
    QWidget::resizeEvent(event);
}

