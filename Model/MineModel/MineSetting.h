#ifndef MINE_SETTING_H
#define MINE_SETTING_H

#include "BLKC_Common.h"
#include <stdio.h>
#include <vector>
#include <utility>
#include <random>

class MineSetting
{
    public:
        MineSetting();
        void init(int rows, int cols);
        void calculateSafeZone(int rows, int cols, int size);
        void placeMines(int mineCount);
        bool isSafeCell(int row, int col);
        void calculateNumbers();
        bool openCell(int row, int col, std::vector<PointCellOpened>& openedCells);
        bool checkWin() const;
        bool isOpened(int row, int col) const;
        int  flagCount() const;
        bool isFlagged(int row, int col) const;
        bool toggleFlag(int row, int col);
        const std::vector<std::pair<int,int>> allMines() const;

    private:
        bool inBounds(int r, int c) const;
    
    private:
        struct Cell {
            bool isMine   = false;
            bool opened   = false;
            bool flagged  = false;
            int  adjacent = 0;
        };

    private:
        int m_rows = 0;
        int m_cols = 0;
        int m_mineCount = 0;
        std::vector<std::vector<Cell>> m_cells;
        std::vector<std::pair<int,int>> m_safeZone;
};

#endif