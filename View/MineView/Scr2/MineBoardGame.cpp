#include "MineBoardGame.h"

#include "CellButton.h"

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

MineBoardGame::MineBoardGame(QWidget* parent)
    : QWidget(parent)
{
    setStyleSheet(BOARD_STYLE);

    m_grid = new QGridLayout(this);
    m_grid->setContentsMargins(0, 0, 0, 0);
    m_grid->setSpacing(1);

    setBoardSize(8);

    // ===== PAUSE OVERLAY =====
    m_pauseOverlay = new QWidget(this);
    m_pauseOverlay->hide();
    m_pauseOverlay->setAttribute(Qt::WA_TransparentForMouseEvents, false);

    m_pauseOverlay->setStyleSheet(
        "background-color: #7f7f7f;"
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

void MineBoardGame::setBoardSize(int size)
{
    if (size <= 0)
        return;

    m_boardSize = size;

    if(size <= 8)
        m_buttonCellSize = 45;
    else if(size <= 16)
        m_buttonCellSize = 35;
    else if(size <= 32)
        m_buttonCellSize = 25;
    else
        m_buttonCellSize = 25;
    
    rebuildBoard();
}

void MineBoardGame::rebuildBoard()
{
    while (QLayoutItem* item = m_grid->takeAt(0)) {
        delete item->widget();
        delete item;
    }

    m_buttons.resize(m_boardSize);

    for (int r = 0; r < m_boardSize; ++r) {
        m_buttons[r].resize(m_boardSize);

        for (int c = 0; c < m_boardSize; ++c) {

            auto* btn = new CellButton(this);

            btn->setFixedSize(m_buttonCellSize, m_buttonCellSize);

            btn->setProperty("cellValue", QVariant());
            btn->setFlagged(false);

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

    this->setFixedSize(((m_buttonCellSize * m_boardSize) + 7), ((m_buttonCellSize * m_boardSize) + 7));
}

void MineBoardGame::openCell(int row, int col, int value)
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
    {
        btn->setText(QString::number(value));

        QFont font = btn->font();
        font.setBold(true);
        font.setPixelSize(m_buttonCellSize * 0.60);
        btn->setFont(font);

        btn->setStyleSheet(R"(
        QPushButton {
            color: #3f4141;
        }
        )");
    }
    else
        btn->setText("");

    // Refresh style
    btn->style()->unpolish(btn);
    btn->style()->polish(btn);
}

void MineBoardGame::resetBoard()
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

void MineBoardGame::revealMine(int row, int col, bool flagMineTriggered)
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
        btn->setText("X");
        btn->setProperty("cellValue", "trig");
    }
    else
    {
        btn->setText("*");
        btn->setProperty("cellValue", "bomb");
    }

    btn->style()->unpolish(btn);
    btn->style()->polish(btn);
}

void MineBoardGame::showPausedOverlay(bool show)
{
    if (!m_pauseOverlay)
        return;

    m_pauseOverlay->setGeometry(rect());
    m_pauseOverlay->setVisible(show);
    m_pauseOverlay->raise();
}

void MineBoardGame::setFlag(int row, int col, bool flagged)
{
    auto* btn = qobject_cast<CellButton*>(m_buttons[row][col]);
    if (!btn)
        return;

    btn->setFlagged(flagged);

    if (flagged) {
        btn->setText("P");
    } else {
        btn->setText("");
    }

    btn->style()->unpolish(btn);
    btn->style()->polish(btn);
}