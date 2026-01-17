#include "MineModel.h"
#include "BoardModel.h"
#include "BestTimeEntry.h"
#include "BestTimesStorage.h"

MineModel::MineModel(QObject* parent)
    : QObject(parent)
{
    m_board = new BoardModel();
    m_bestTimesStorage= new BestTimesStorage();
}

MineModel::~MineModel()
{
    delete m_board;
    delete m_bestTimesStorage;
}

void MineModel::setup(int rows, int cols, int mineCount)
{
    m_rows      = rows;
    m_cols      = cols;
    m_mineCount = mineCount;

    m_board->init(rows, cols);
    m_bestTimesStorage->load();

    m_state = GameState::NotStarted;
}

GameState MineModel::getState() const
{
    return m_state;
}

void MineModel::setState(GameState state)
{
    if (m_state == state)
        return;

    m_state = state;
    emit stateChanged(m_state);
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
        emit minesRevealed(row, col, m_board->allMines());
        setState(GameState::Finished);
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

void MineModel::toggleFlag(int row, int col)
{
    if (m_state == GameState::Finished ||
        m_state == GameState::Paused)
        return;

    if (m_board->isOpened(row, col))
        return;

    bool flagged = m_board->toggleFlag(row, col);

    emit flagChanged(row, col, flagged);
    emit flagCountChanged(m_board->flagCount(), m_mineCount);
}

const QVector<BestTimeEntry>& MineModel::getEntries() const
{
    return m_bestTimesStorage->entries();
}
