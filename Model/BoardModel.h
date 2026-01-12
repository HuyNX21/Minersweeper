#ifndef BOARDMODEL_H
#define BOARDMODEL_H

#pragma once

#include <QVector>
#include <QPoint>
#include <QRandomGenerator>
#include <QQueue>

/**
 * @class BoardModel
 * @brief Core data model for the mine board
 *
 * Stores board state, mine placement, and cell logic.
 * Contains no UI or Qt widget dependencies.
 */
class BoardModel
{
public:
    /**
     * @brief Creates an empty board model
     */
    BoardModel() = default;

    /**
     * @brief Initializes an empty board without mines
     * @param rows Number of rows
     * @param cols Number of columns
     */
    void init(int rows, int cols);

    /**
     * @brief Places mines on the board
     * @param mineCount Number of mines to place
     * @param safeRow Row index of the safe cell (first click)
     * @param safeCol Column index of the safe cell (first click)
     */
    void placeMines(int mineCount, int safeRow, int safeCol);

    /**
     * @brief Calculates adjacent mine counts for all cells
     */
    void calculateNumbers();

    /**
     * @brief Opens a cell and applies flood fill if needed
     * @param row Cell row index
     * @param col Cell column index
     * @param openedCells Output list of newly opened cells
     * @return True if a mine was triggered
     */
    bool openCell(int row, int col, QVector<QPoint>& openedCells);

    /**
     * @brief Returns the number of adjacent mines for a cell
     */
    int adjacentMines(int row, int col) const;

    /**
     * @brief Checks whether the win condition is met
     */
    bool checkWin() const;

    /**
     * @brief Checks if a cell is already opened
     */
    bool isOpened(int row, int col) const;

    /**
     * @brief Checks if a cell is flagged
     */
    bool isFlagged(int row, int col) const;

    /**
     * @brief Toggles the flag state of a cell
     * @return New flag state after toggling
     */
    bool toggleFlag(int row, int col);

    /**
     * @brief Returns the current number of placed flags
     */
    int flagCount() const;

    /**
     * @brief Returns positions of all mines
     */
    QVector<QPoint> allMines() const;

private:
    /**
     * @brief Represents a single board cell
     */
    struct Cell {
        bool isMine   = false; ///< True if the cell contains a mine
        bool opened   = false; ///< True if the cell is opened
        bool flagged  = false; ///< True if the cell is flagged
        int  adjacent = 0;     ///< Number of adjacent mines
    };

private:
    /**
     * @brief Checks whether the position is inside board bounds
     */
    bool inBounds(int r, int c) const;

    /**
     * @brief Opens connected empty cells using flood fill
     */
    void floodFill(int r, int c, QVector<QPoint>& openedCells);

private:
    int m_rows = 0;        ///< Number of board rows
    int m_cols = 0;        ///< Number of board columns
    int m_mineCount = 0;  ///< Total number of mines

    QVector<QVector<Cell>> m_cells; ///< 2D grid of board cells
};

#endif // BOARDMODEL_H
