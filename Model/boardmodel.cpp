#include "BoardModel.h"

#include <QRandomGenerator>
#include <QQueue>

void BoardModel::init(int rows, int cols)
{
    m_rows = rows;
    m_cols = cols;
    m_mineCount = 0;

    m_cells.resize(rows);
    for (auto& row : m_cells) {
        row.resize(cols);
        for (auto& cell : row)
            cell = Cell{};
    }
}

void BoardModel::placeMines(int mineCount, int safeRow, int safeCol)
{
    m_mineCount = mineCount;

    int placed = 0;
    while (placed < mineCount) {
        int r = QRandomGenerator::global()->bounded(m_rows);
        int c = QRandomGenerator::global()->bounded(m_cols);

        // Tránh ô đầu tiên
        if (r == safeRow && c == safeCol)
            continue;

        Cell& cell = m_cells[r][c];
        if (cell.isMine)
            continue;

        cell.isMine = true;
        ++placed;
    }
}

void BoardModel::calculateNumbers()
{
    static const int dr[8] = { -1,-1,-1, 0,0, 1,1,1 };
    static const int dc[8] = { -1, 0, 1,-1,1,-1,0,1 };

    for (int r = 0; r < m_rows; ++r) {
        for (int c = 0; c < m_cols; ++c) {
            Cell& cell = m_cells[r][c];
            if (cell.isMine)
                continue;

            int count = 0;
            for (int i = 0; i < 8; ++i) {
                int nr = r + dr[i];
                int nc = c + dc[i];
                if (inBounds(nr, nc) && m_cells[nr][nc].isMine)
                    ++count;
            }
            cell.adjacent = count;
        }
    }
}

bool BoardModel::openCell(int row, int col, QVector<QPoint>& openedCells)
{
    if (!inBounds(row, col))
        return false;

    Cell& start = m_cells[row][col];
    if (start.opened || start.flagged)
        return false;

    if (start.isMine)
        return true;

    floodFill(row, col, openedCells);
    return false;
}

void BoardModel::floodFill(int r, int c, QVector<QPoint>& openedCells)
{
    QQueue<QPoint> queue;
    queue.enqueue({r, c});

    while (!queue.isEmpty()) {
        QPoint p = queue.dequeue();
        int cr = p.x();
        int cc = p.y();

        if (!inBounds(cr, cc))
            continue;

        Cell& cell = m_cells[cr][cc];
        if (cell.opened || cell.flagged)
            continue;

        cell.opened = true;
        openedCells.push_back(p);

        // Nếu có số > 0 thì không lan tiếp
        if (cell.adjacent > 0)
            continue;

        // Lan ra 8 hướng
        for (int dr = -1; dr <= 1; ++dr) {
            for (int dc = -1; dc <= 1; ++dc) {
                if (dr == 0 && dc == 0)
                    continue;

                int nr = cr + dr;
                int nc = cc + dc;
                if (inBounds(nr, nc))
                    queue.enqueue({nr, nc});
            }
        }
    }
}

int BoardModel::adjacentMines(int row, int col) const
{
    if (!inBounds(row, col))
        return 0;

    return m_cells[row][col].adjacent;
}

bool BoardModel::checkWin() const
{
    int openedCount = 0;
    for (const auto& row : m_cells) {
        for (const auto& cell : row) {
            if (cell.opened)
                ++openedCount;
        }
    }

    return openedCount == (m_rows * m_cols - m_mineCount);
}

bool BoardModel::inBounds(int r, int c) const
{
    return r >= 0 && r < m_rows && c >= 0 && c < m_cols;
}

QVector<QPoint> BoardModel::allMines() const
{
    QVector<QPoint> result;
    for (int r = 0; r < m_rows; ++r) {
        for (int c = 0; c < m_cols; ++c) {
            if (m_cells[r][c].isMine)
                result.push_back(QPoint(r, c));
        }
    }
    return result;
}
