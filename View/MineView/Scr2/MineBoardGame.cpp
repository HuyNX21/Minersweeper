#include "MineBoardGame.h"

#include "CellButton.h"

#include <QIcon>
#include <QPixmap>

namespace {

QIcon makeColorPreservedIcon(const QString& resourcePath)
{
    QIcon icon;
    QPixmap pix(resourcePath);
    icon.addPixmap(pix, QIcon::Normal, QIcon::Off);
    icon.addPixmap(pix, QIcon::Disabled, QIcon::Off);
    return icon;
}

void applyDefaultCellVisual(QPushButton* btn, int buttonCellSize)
{
    btn->setStyleSheet("");

    QFont font = btn->font();
    font.setBold(true);
    font.setPixelSize(qMax(12, static_cast<int>(buttonCellSize * 0.60)));
    btn->setFont(font);
}

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

    int nextButtonCellSize = 25;

    if(size <= 8)
        nextButtonCellSize = 45;
    else if(size <= 16)
        nextButtonCellSize = 35;
    else if(size <= 32)
        nextButtonCellSize = 25;
    else
        nextButtonCellSize = 25;

    const bool boardChanged =
        (m_boardSize != size) ||
        (m_buttonCellSize != nextButtonCellSize) ||
        m_buttons.isEmpty();

    if (!boardChanged)
        return;

    m_boardSize = size;
    m_buttonCellSize = nextButtonCellSize;
    
    rebuildBoard();
}

void MineBoardGame::rebuildBoard()
{
    setUpdatesEnabled(false);

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
            applyDefaultCellVisual(btn, m_buttonCellSize);

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

    const int spacing = m_grid->spacing();
    const QMargins margins = m_grid->contentsMargins();
    const int boardPixel = (m_buttonCellSize * m_boardSize)
                         + (spacing * (m_boardSize - 1));

    this->setFixedSize(boardPixel + margins.left() + margins.right(),
                       boardPixel + margins.top() + margins.bottom());
    this->updateGeometry();

    setUpdatesEnabled(true);
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
    btn->setIcon(QIcon());
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
    setUpdatesEnabled(false);

    for (int r = 0; r < m_boardSize; ++r) {
        for (int c = 0; c < m_boardSize; ++c) {
            QPushButton* btn = m_buttons[r][c];
            if (!btn)
                continue;

            auto* cell = qobject_cast<CellButton*>(btn);
            if (cell)
                cell->setFlagged(false);

            btn->setEnabled(true);
            btn->setText("");
            btn->setIcon(QIcon());
            btn->setProperty("cellValue", QVariant());
            applyDefaultCellVisual(btn, m_buttonCellSize);
        }
    }

    setUpdatesEnabled(true);
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
    const int iconPx = qMax(14, static_cast<int>(m_buttonCellSize * 0.70));
    btn->setIconSize(QSize(iconPx, iconPx));

    if(flagMineTriggered)
    {
        btn->setIcon(makeColorPreservedIcon(":/icons/collision.png"));
        btn->setText("");
        btn->setProperty("cellValue", "trig");
    }
    else
    {
        btn->setIcon(makeColorPreservedIcon(":/icons/bomb.png"));
        btn->setText("");
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
    if (row < 0 || row >= m_boardSize ||
        col < 0 || col >= m_boardSize)
        return;

    auto* btn = qobject_cast<CellButton*>(m_buttons[row][col]);
    if (!btn)
        return;

    btn->setFlagged(flagged);
    applyDefaultCellVisual(btn, m_buttonCellSize);

    if (flagged) {
        const int iconPx = qMax(14, static_cast<int>(m_buttonCellSize * 0.70));
        btn->setIcon(makeColorPreservedIcon(":/icons/flag.png"));
        btn->setIconSize(QSize(iconPx, iconPx));
        btn->setText("");
    } else {
        btn->setIcon(QIcon());
        btn->setText("");
    }

    btn->style()->unpolish(btn);
    btn->style()->polish(btn);
}