#ifndef MINECONTROLLER_H
#define MINECONTROLLER_H

#pragma once

#include <QObject>

#include "../Model/GameState.h"

class MineView;
class MineModel;

/**
 * @class MineController
 * @brief Coordinates interaction between the view and the model
 *
 * Handles user actions from the view, updates the model,
 * and reflects model state changes back to the view.
 */
class MineController : public QObject
{
    Q_OBJECT

public:
    /**
     * @brief Creates the game controller
     * @param view Game view layer
     * @param model Game model layer
     * @param parent Parent object
     */
    explicit MineController(MineView* view, MineModel* model, QObject* parent = nullptr);

private slots:
    /**
     * @brief Handles mode selection from the view
     * @param size Board size
     * @param mines Number of mines
     */
    void onModeSelected(int size, int mines);

    /**
     * @brief Handles back navigation request
     */
    void onBackRequested();

    /**
     * @brief Handles a cell left-click action
     * @param row Cell row index
     * @param col Cell column index
     */
    void onCellClicked(int row, int col);

    /**
     * @brief Updates the view when a cell is opened
     * @param row Cell row index
     * @param col Cell column index
     * @param value Cell value
     */
    void onCellOpened(int row, int col, int value);

    /**
     * @brief Handles game over state
     * @param win True if the player wins
     */
    void onGameOver(bool win);

    /**
     * @brief Reveals all mines in the view
     * @param rowMineTriggered Row of the triggered mine
     * @param colMineTriggered Column of the triggered mine
     * @param mines Positions of all mines
     */
    void onMinesRevealed(int rowMineTriggered,
                         int colMineTriggered,
                         const QVector<QPoint>& mines);

    /**
     * @brief Handles pause or resume requests
     */
    void onPauseRequested();

    /**
     * @brief Handles game state changes from the model
     * @param state New game state
     */
    void onGameStateChanged(GameState state);

    /**
     * @brief Handles a cell right-click action
     * @param row Cell row index
     * @param col Cell column index
     */
    void onCellRightClicked(int row, int col);

    /**
     * @brief Handles flag state changes on a cell
     * @param row Cell row index
     * @param col Cell column index
     * @param flagged True if the cell is flagged
     */
    void onFlagChanged(int row, int col, bool flagged);

    /**
     * @brief Updates the flag counter in the view
     * @param used Number of flags used
     * @param total Total number of available flags
     */
    void onFlagCountChanged(int used, int total);

    /**
     * @brief Shows the new game confirmation dialog
     */
    void onShowConfirmNewGameDialog();

private:
    MineView*  m_view;   ///< View layer
    MineModel* m_model;  ///< Model layer
};

#endif // MINECONTROLLER_H
