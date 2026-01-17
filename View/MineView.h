#ifndef MINEVIEW_H
#define MINEVIEW_H

#include <QMainWindow>
#include <QStackedWidget>

class QStackedWidget;
class ModeSelectWidget;
class CentralWidget;
class MineBoard;
class SidePanel;
class BestTimesDialog;
class BestTimeEntry;

/**
 * @brief Top-level view responsible for screen navigation.
 *
 * MineView owns and manages the main application screens
 * (mode selection and game board) and handles transitions
 * between them. It does not contain game logic.
 */
class MineView : public QMainWindow {
    Q_OBJECT
public:
    /**
     * @brief Constructs the main application view.
     *
     * Initializes and owns all primary UI screens.
     */
    explicit MineView(QWidget* parent = nullptr);

    /**
     * @brief Displays the mode selection screen.
     */
    void showSelectScreen();

    /**
     * @brief Displays the game board screen.
     */
    void showBoardScreen();

    /**
     * @brief Sets the size of the game board.
     *
     * @param size Board dimension (e.g. 8, 16, 32).
     */
    void setBoardSize(int size);

    /**
     * @brief Displays best times dialog.
     */
    void showBestTimesRequested(const QVector<BestTimeEntry>&);

    /**
     * @brief Returns the game board instance.
     *
     * Ownership remains with MineView.
     */
    MineBoard* mineBoard() const;

    /**
     * @brief Returns the side panel associated with the game board.
     *
     * Ownership remains with MineView.
     */
    SidePanel* sidePanel() const;

signals:
    /**
     * @brief Emitted when the user selects a game mode.
     *
     * @param size  Board dimension.
     * @param mines Number of mines.
     */
    void modeSelected(int size, int mines);

    /**
     * @brief Emitted when the user requests to return
     *        to the mode selection screen.
     */
    void changeDifficultyRequested();

private:
    QStackedWidget*    m_stack;        ///< Manages screen switching
    ModeSelectWidget* m_selectScreen;  ///< Mode selection UI
    CentralWidget*    m_boardScreen;   ///< Game board container
};

#endif // MINEVIEW_H
