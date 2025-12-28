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
    m_grid->setSpacing(1);
    m_grid->setContentsMargins(0, 0, 0, 0);

    setBoardSize(8);
}

QString MineBoard::colorForValue(int value) const
{
    switch (value) {
    case 0: return "#D9D9D9"; // default
    case 1: return "#D7F7CB";
    case 2: return "#F0F7CB";
    case 3: return "#F7F0C3";
    case 4: return "#F7E7B1";
    case 5: return "#F7D89F";
    case 6: return "#F7A87F";
    case 7: return "#F77070";
    case 8: return "#FF3B3B";
    default:
        return "#D9D9D9";
    }
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

    m_buttons.resize(m_boardSize);

    QString buttonStyle = R"(
    QPushButton {
        background-color: #c0c0c0;
        border-top: 2px solid #ffffff;
        border-left: 2px solid #ffffff;
        border-bottom: 2px solid #808080;
        border-right: 2px solid #808080;
        font-weight: bold;
    }

    QPushButton:pressed {
        border-top: 2px solid #808080;
        border-left: 2px solid #808080;
        border-bottom: 2px solid #ffffff;
        border-right: 2px solid #ffffff;
    }

    QPushButton:disabled {
        background-color: #d6d6d6;
        border: 1px solid #a0a0a0;
    }
    )";

    for (int r = 0; r < m_boardSize; ++r)
    {
        m_buttons[r].resize(m_boardSize);
        for (int c = 0; c < m_boardSize; ++c)
        {
            auto* btn = new QPushButton(this);

            btn->setSizePolicy(QSizePolicy::Ignored,
                               QSizePolicy::Ignored);

            btn->setStyleSheet(buttonStyle);

            connect(btn, &QPushButton::clicked,
                    this, [this, r, c]() {
                        emit cellClicked(r, c);
                    });

            m_grid->addWidget(btn, r, c);

            m_buttons[r][c] = btn;
        }
    }
}

void MineBoard::openCell(int row, int col, int value)
{
    if (row < 0 || row >= m_boardSize ||
        col < 0 || col >= m_boardSize)
        return;

    QPushButton* btn = m_buttons[row][col];
    if (!btn || !btn->isEnabled())
        return;

    btn->setEnabled(false);

    // Set text
    if (value > 0) {
        btn->setText(QString::number(value));
    } else {
        btn->setText("");
    }

    // Set background color theo value
    const QString color = colorForValue(value);
    btn->setStyleSheet(QString(
                           "QPushButton:disabled { background-color: %1; border: 1px solid #a0a0a0; }"
                           ).arg(color));
}

void MineBoard::revealMine(int row, int col)
{
    if (row < 0 || row >= m_boardSize ||
        col < 0 || col >= m_boardSize)
        return;

    QPushButton* btn = m_buttons[row][col];
    if (!btn)
        return;

    btn->setText("X");
    btn->setEnabled(false);
}

void MineBoard::resetBoard()
{
    for (int r = 0; r < m_boardSize; ++r) {
        for (int c = 0; c < m_boardSize; ++c) {
            QPushButton* btn = m_buttons[r][c];
            if (!btn)
                continue;

            btn->setEnabled(true);
            btn->setText("");
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

