#ifndef BOARDMODEL_H
#define BOARDMODEL_H

#pragma once

#include <QVector>
#include <QPoint>

class BoardModel
{
public:
    BoardModel() = default;

    // Khởi tạo board rỗng (chưa mine)
    void init(int rows, int cols);

    // Rải mine, tránh ô an toàn (first click)
    void placeMines(int mineCount, int safeRow, int safeCol);

    // Tính số mine lân cận
    void calculateNumbers();

    // Mở 1 ô
    // - openedCells: danh sách ô được mở (phục vụ flood fill)
    // - return true nếu dính mine
    bool openCell(int row, int col, QVector<QPoint>& openedCells);

    // Lấy số mine lân cận của ô
    int adjacentMines(int row, int col) const;

    // Kiểm tra thắng
    bool checkWin() const;

    QVector<QPoint> allMines() const;

private:
    struct Cell {
        bool isMine   = false;
        bool opened   = false;
        bool flagged  = false;
        int  adjacent = 0;
    };

private:
    bool inBounds(int r, int c) const;
    void floodFill(int r, int c, QVector<QPoint>& openedCells);

private:
    int m_rows = 0;
    int m_cols = 0;
    int m_mineCount = 0;

    QVector<QVector<Cell>> m_cells;
};


#endif // BOARDMODEL_H
