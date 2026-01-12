#ifndef MINEBOARD_H
#define MINEBOARD_H

#include <QWidget>
#include <QVector>
#include <QGridLayout>
#include <QPushButton>
#include <QResizeEvent>
#include <QtMath>
#include <QStyle>
#include <QSizePolicy>
#include <QDebug>
#include <QPainter>
#include <QLabel>

class QGridLayout;
class QPushButton;

/**
 * @class MineBoard
 * @brief Widget representing the minefield grid
 *
 * Manages the visual representation of the game board,
 * including cells, layout, and board-level UI states.
 */
class MineBoard : public QWidget
{
    Q_OBJECT

public:
    /**
     * @brief Creates the mine board widget
     * @param parent Parent widget
     */
    explicit MineBoard(QWidget* parent = nullptr);

    /**
     * @brief Sets the board dimension
     * @param size Board size (NxN)
     */
    void setBoardSize(int size);

    /**
     * @brief Indicates support for height-for-width layout
     */
    bool hasHeightForWidth() const override;

    /**
     * @brief Calculates height based on the given width
     * @param w Available width
     */
    int heightForWidth(int w) const override;

    /**
     * @brief Returns the preferred size of the board
     */
    QSize sizeHint() const override;

    /**
     * @brief Returns the minimum acceptable size of the board
     */
    QSize minimumSizeHint() const override;

    // ===== Controller-facing API =====

    /**
     * @brief Opens a cell and displays its value
     * @param row Cell row index
     * @param col Cell column index
     * @param value Cell value to display
     */
    void openCell(int row, int col, int value);

    /**
     * @brief Reveals a mine at the given cell
     * @param row Cell row index
     * @param col Cell column index
     * @param flagMineTriggered True if this mine caused game over
     */
    void revealMine(int row, int col, bool flagMineTriggered);

    /**
     * @brief Resets the board to its initial state
     */
    void resetBoard();

    /**
     * @brief Shows or hides the paused overlay
     * @param show True to show the overlay
     */
    void showPausedOverlay(bool show);

    /**
     * @brief Sets or clears a flag on a cell
     * @param row Cell row index
     * @param col Cell column index
     * @param flagged True to place a flag
     */
    void setFlag(int row, int col, bool flagged);

signals:
    /**
     * @brief Emitted when a cell is left-clicked by the user
     */
    void cellClicked(int row, int col);

    /**
     * @brief Emitted when a cell is right-clicked by the user
     */
    void cellRightClicked(int row, int col);

protected:
    /**
     * @brief Handles resize events to update layout and visuals
     */
    void resizeEvent(QResizeEvent* event) override;

private:
    /**
     * @brief Rebuilds the board layout and cells
     */
    void rebuildBoard();

    /**
     * @brief Updates font size based on cell dimensions
     */
    void updateCellFont();

private:
    QVector<QVector<QPushButton*>> m_buttons;  ///< Grid of cell buttons
    static constexpr int MinButtonSize = 40;   ///< Minimum cell size in pixels
    QGridLayout* m_grid = nullptr;             ///< Layout for the board grid
    int m_boardSize = 0;                       ///< Current board dimension
    QWidget* m_pauseOverlay = nullptr;         ///< Overlay shown when game is paused
};

#endif // MINEBOARD_H
