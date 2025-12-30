#include "mineboard.h"
#include "../../Model/CellButton.h"

#include <QGridLayout>
#include <QPushButton>
#include <QResizeEvent>
#include <QtMath>
#include <QStyle>
#include <QSizePolicy>
#include <QDebug>
#include <QPainter>
#include <QLabel>

namespace {

const char* BOARD_STYLE = R"(

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
    border: 1px solid #a0a0a0;
}

/* Background by value */
QPushButton:disabled[cellValue="0"]    { background-color: #F0F0F0; }
QPushButton:disabled[cellValue="1"]    { background-color: #D7F7CB; }
QPushButton:disabled[cellValue="2"]    { background-color: #F0F7CB; }
QPushButton:disabled[cellValue="3"]    { background-color: #F7F0C3; }
QPushButton:disabled[cellValue="4"]    { background-color: #F7E7B1; }
QPushButton:disabled[cellValue="5"]    { background-color: #F7D89F; }
QPushButton:disabled[cellValue="6"]    { background-color: #F7A87F; }
QPushButton:disabled[cellValue="7"]    { background-color: #F77070; }
QPushButton:disabled[cellValue="8"]    { background-color: #FF3B3B; }
QPushButton:disabled[cellValue="bomb"] { background-color: #787574; }
QPushButton:disabled[cellValue="trig"] { background-color: #ABABAB; }

)";

}

MineBoard::MineBoard(QWidget* parent)
    : QWidget(parent)
{
    setStyleSheet(BOARD_STYLE);

    m_grid = new QGridLayout(this);
    m_grid->setSpacing(1);
    m_grid->setContentsMargins(0, 0, 0, 0);

    setBoardSize(8);

    // ===== PAUSE OVERLAY =====
    m_pauseOverlay = new QWidget(this);
    m_pauseOverlay->hide();
    m_pauseOverlay->setAttribute(Qt::WA_TransparentForMouseEvents, false);

    m_pauseOverlay->setStyleSheet(
        "background-color: #7f7f7f;"   // xám đặc
    );

    auto* label = new QLabel("Paused", m_pauseOverlay);
    label->setAlignment(Qt::AlignCenter);
    label->setStyleSheet(
        "color: white;"
        "font-size: 36px;"
        "font-weight: bold;"
        "letter-spacing: 4px;"
        );

    auto* layout = new QVBoxLayout(m_pauseOverlay);
    layout->addStretch();
    layout->addWidget(label, 0, Qt::AlignCenter);
    layout->addStretch();
}

void MineBoard::setBoardSize(int size)
{
    if (size <= 0 || size == m_boardSize)
        return;

    m_boardSize = size;
    rebuildBoard();

    const int minSide = MinButtonSize * m_boardSize;
    setMinimumSize(minSide, minSide);

    updateCellFont();

    updateGeometry();
}

void MineBoard::rebuildBoard()
{
    // Clear old layout
    while (QLayoutItem* item = m_grid->takeAt(0)) {
        delete item->widget();
        delete item;
    }

    m_buttons.resize(m_boardSize);

    for (int r = 0; r < m_boardSize; ++r) {
        m_buttons[r].resize(m_boardSize);

        for (int c = 0; c < m_boardSize; ++c) {
            //auto* btn = new QPushButton(this);
            auto* btn = new CellButton(this);

            btn->setSizePolicy(QSizePolicy::Ignored,
                               QSizePolicy::Ignored);

            btn->setProperty("cellValue", QVariant());

            connect(btn, &CellButton::leftClicked,
                    this, [this, r, c]() {
                        emit cellClicked(r, c);
                    });

            connect(btn, &CellButton::rightClicked,
                    this, [this, r, c]() {
                        emit cellRightClicked(r, c);
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

    auto* cell = qobject_cast<CellButton*>(btn);
    if (cell && cell->isFlagged())
        return;

    // Set state
    btn->setEnabled(false);
    btn->setProperty("cellValue", value);

    // Text
    if (value > 0)
        btn->setText(QString::number(value));
    else
        btn->setText("");

    // Refresh style
    btn->style()->unpolish(btn);
    btn->style()->polish(btn);
}

void MineBoard::revealMine(int row, int col, bool flagMineTriggered)
{
    if (row < 0 || row >= m_boardSize ||
        col < 0 || col >= m_boardSize)
        return;

    QPushButton* btn = m_buttons[row][col];
    if (!btn)
        return;

    btn->setEnabled(false);

    if(flagMineTriggered)
    {
        btn->setText("💥");
        btn->setProperty("cellValue", "trig");
    }
    else
    {
        btn->setText("💣");
        btn->setProperty("cellValue", "bomb");
    }

    btn->style()->unpolish(btn);
    btn->style()->polish(btn);
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
            btn->setProperty("cellValue", QVariant());

            btn->style()->unpolish(btn);
            btn->style()->polish(btn);
        }
    }
}

void MineBoard::updateCellFont()
{
    if (m_boardSize <= 0)
        return;

    const int boardSide = qMin(width(), height());
    const int cellSize  = boardSide / m_boardSize;

    int fontSize = qBound(12, static_cast<int>(cellSize * 0.6), 48);

    QFont f;
    f.setBold(true);
    f.setWeight(QFont::Bold);
    f.setPixelSize(fontSize);

    for (auto& row : m_buttons) {
        for (QPushButton* btn : row) {
            if (!btn) continue;
            btn->setFont(f);
            btn->setStyleSheet("color: #333333;");
        }
    }
}

void MineBoard::showPausedOverlay(bool show)
{
    if (!m_pauseOverlay)
        return;

    m_pauseOverlay->setVisible(show);
    m_pauseOverlay->raise(); // đảm bảo nằm trên cùng
}

void MineBoard::setFlag(int row, int col, bool flagged)
{
    auto* btn = qobject_cast<CellButton*>(m_buttons[row][col]);
    if (!btn)
        return;

    btn->setFlagged(flagged);

    if (flagged) {
        btn->setText("🏴");
    } else {
        btn->setText("");
    }

    btn->style()->unpolish(btn);
    btn->style()->polish(btn);
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

    if (m_pauseOverlay)
        m_pauseOverlay->setGeometry(rect());

    updateCellFont();
}


