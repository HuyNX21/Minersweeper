#include "MineModel.h"
#include "BoardModel.h"

MineModel::MineModel(QObject* parent)
    : QObject(parent)
{
    m_board = new BoardModel();
}

MineModel::~MineModel()
{
    delete m_board;
}

void MineModel::setup(int rows, int cols, int mineCount)
{
    m_rows      = rows;
    m_cols      = cols;
    m_mineCount = mineCount;

    m_board->init(rows, cols);

    m_state = GameState::NotStarted;
}

MineModel::GameState MineModel::state() const
{
    return m_state;
}

void MineModel::startGame(int safeRow, int safeCol)
{
    m_board->placeMines(m_mineCount, safeRow, safeCol);
    m_board->calculateNumbers();

    m_state = GameState::Running;
}

void MineModel::openCell(int row, int col)
{
    if (m_state == GameState::Finished)
        return;

    if (m_state == GameState::NotStarted) {
        startGame(row, col);
    }

    QVector<QPoint> openedCells;
    bool hitMine = m_board->openCell(row, col, openedCells);

    if (hitMine) {
        m_state = GameState::Finished;

        // NEW
        emit minesRevealed(row, col, m_board->allMines());
        emit gameOver(false);
        return;
    }

    for (const QPoint& p : openedCells) {
        int value = m_board->adjacentMines(p.x(), p.y());
        emit cellOpened(p.x(), p.y(), value);
    }

    if (m_board->checkWin()) {
        m_state = GameState::Finished;
        emit gameOver(true);
    }
}
