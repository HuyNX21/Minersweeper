#include "MineSetting.h"

static std::random_device rd;
static std::mt19937 gen(rd());

MineSetting::MineSetting()
{

}

void MineSetting::init(int rows, int cols)
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

void MineSetting::calculateSafeZone(int rows, int cols, int size)
{
    m_safeZone.clear();

    for(int deltaRow = -1; deltaRow <= 1; deltaRow++)
    {
        for(int deltaColumn = -1; deltaColumn <= 1; deltaColumn++)
        {
            int nearRow = rows + deltaRow;
            int nearColumn = cols + deltaColumn;

            if(size <= 8 && (deltaRow != 0 && deltaColumn != 0)) // For <= 8x8, only the clicked cell and its orthogonal neighbors are safe.
            {
                continue;
            }

            m_safeZone.emplace_back(nearRow, nearColumn);
        }
    }
}

bool MineSetting::isSafeCell(int row, int col)
{
    for (const auto &p : m_safeZone) {
        if (p.first == row && p.second == col)
            return true;
    }
    return false;
}

void MineSetting::placeMines(int mineCount)
{
    m_mineCount = mineCount;

    std::uniform_int_distribution<int> distRow(0, m_rows - 1);
    std::uniform_int_distribution<int> distCol(0, m_cols - 1);

    int placed = 0;
    while (placed < mineCount) {
        int r = distRow(gen);
        int c = distCol(gen);

        if (isSafeCell(r, c))
            continue;

        Cell& cell = m_cells[r][c];
        if (cell.isMine)
            continue;

        cell.isMine = true;
        ++placed;
    }
}

void MineSetting::calculateNumbers()
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

bool MineSetting::inBounds(int r, int c) const
{
    return r >= 0 && r < m_rows && c >= 0 && c < m_cols;
}

bool MineSetting::openCell(int row, int col, std::vector<PointCellOpened>& openedCells)
{
    if (!inBounds(row, col))
        return false;

    Cell& cell = m_cells[row][col];
    if (cell.opened || cell.flagged)
        return false;

    cell.opened = true;
    openedCells.push_back({row, col, cell.adjacent});

    if (cell.isMine)
        return true;

    if (cell.adjacent == 0) {
        static const int dr[8] = { -1,-1,-1, 0,0, 1,1,1 };
        static const int dc[8] = { -1, 0, 1,-1,1,-1,0,1 };

        for (int i = 0; i < 8; ++i) {
            int nr = row + dr[i];
            int nc = col + dc[i];
            openCell(nr, nc, openedCells);
        }
    }

    return false;
}

bool MineSetting::checkWin() const
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

bool MineSetting::isOpened(int row, int col) const
{
    if (!inBounds(row, col))
        return false;

    return m_cells[row][col].opened;
}

bool MineSetting::isFlagged(int row, int col) const
{
    if (!inBounds(row, col))
        return false;

    return m_cells[row][col].flagged;
}

int MineSetting::flagCount() const
{
    int count = 0;
    for (const auto& row : m_cells) {
        for (const Cell& cell : row) {
            if (cell.flagged)
                ++count;
        }
    }
    return count;
}

bool MineSetting::toggleFlag(int row, int col)
{
    if (!inBounds(row, col))
        return false;

    Cell& cell = m_cells[row][col];

    if (cell.opened)
        return cell.flagged;

    cell.flagged = !cell.flagged;
    return cell.flagged;
}

const std::vector<std::pair<int,int>> MineSetting::allMines() const
{
    std::vector<std::pair<int,int>> mines;
    mines.clear();

    for (int r = 0; r < m_rows; ++r) {
        for (int c = 0; c < m_cols; ++c) {
            if (m_cells[r][c].isMine)
                mines.emplace_back(r, c);
        }
    }

    return mines;
}