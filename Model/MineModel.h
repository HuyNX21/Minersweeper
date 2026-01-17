#ifndef MINEMODEL_H
#define MINEMODEL_H

#pragma once

#include <QObject>
#include <QVector>
#include <QPoint>

#include "GameState.h"

class BoardModel;
class BestTimesStorage;
class BestTimeEntry;

/**
 * @class MineModel
 * @brief Game logic model for the Minesweeper game
 *
 * Manages game state, player actions, and board logic.
 * Acts as the bridge between BoardModel and the controller.
 */
class MineModel : public QObject
{
    Q_OBJECT

public:
    /**
     * @brief Returns the current game state
     */
    GameState state() const;

public:
    /**
     * @brief Creates the game model
     * @param parent Parent object
     */
    explicit MineModel(QObject* parent = nullptr);

    /**
     * @brief Destroys the game model and releases resources
     */
    ~MineModel();

    /**
     * @brief Sets up a new game without placing mines
     * @param rows Number of board rows
     * @param cols Number of board columns
     * @param mineCount Number of mines
     */
    void setup(int rows, int cols, int mineCount);

    /**
     * @brief Handles a player opening a cell
     * @param row Cell row index
     * @param col Cell column index
     */
    void openCell(int row, int col);

    /**
     * @brief Returns the current game state
     */
    GameState getState() const;

    /**
     * @brief Updates the current game state
     * @param state New game state
     */
    void setState(GameState state);

    /**
     * @brief Toggles the flag state of a cell
     * @param row Cell row index
     * @param col Cell column index
     */
    void toggleFlag(int row, int col);

    /**
     * @brief Returns best times entry.
     */
    const QVector<BestTimeEntry>& getEntries() const;

signals:
    /**
     * @brief Notifies that a cell has been opened
     */
    void cellOpened(int row, int col, int adjacent);

    /**
     * @brief Notifies that a cell flag state has changed
     */
    void cellFlagChanged(int row, int col, bool flagged);

    /**
     * @brief Notifies that the game has ended
     * @param win True if the player wins
     */
    void gameOver(bool win);

    /**
     * @brief Notifies that all mines should be revealed
     * @param rowMineTriggered Row of the triggered mine
     * @param colMineTriggered Column of the triggered mine
     * @param mines Positions of all mines
     */
    void minesRevealed(int rowMineTriggered,
                       int colMineTriggered,
                       const QVector<QPoint>& mines);

    /**
     * @brief Notifies that the game state has changed
     */
    void stateChanged(GameState state);

    /**
     * @brief Notifies that a cell flag has changed
     */
    void flagChanged(int row, int col, bool flagged);

    /**
     * @brief Notifies that the flag count has changed
     * @param used Number of flags used
     * @param total Total number of available flags
     */
    void flagCountChanged(int used, int total);

private:
    /**
     * @brief Starts the game by placing mines
     * @param safeRow Row index of the first opened cell
     * @param safeCol Column index of the first opened cell
     */
    void startGame(int safeRow, int safeCol);

private:
    BoardModel* m_board = nullptr;                      ///< Underlying board data model
    BestTimesStorage * m_bestTimesStorage = nullptr;    ///< Underlying best times data model

    int m_rows      = 0; ///< Number of board rows
    int m_cols      = 0; ///< Number of board columns
    int m_mineCount = 0; ///< Total number of mines

    GameState m_state = GameState::NotStarted; ///< Current game state
};

#endif // MINEMODEL_H
