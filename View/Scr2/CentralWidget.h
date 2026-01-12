#ifndef CENTRALWIDGET_H
#define CENTRALWIDGET_H

#include <QWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPushButton>

class MineBoard;
class SidePanel;

/**
 * @class CentralWidget
 * @brief Main container widget of the game UI
 *
 * Owns and coordinates the MineBoard and SidePanel.
 * Exposes UI-level APIs for controllers or main views.
 */
class CentralWidget : public QWidget
{
    Q_OBJECT

public:
    /**
     * @brief Creates the central game widget
     * @param parent Parent widget
     */
    explicit CentralWidget(QWidget* parent = nullptr);

    /**
     * @brief Sets the size of the mine board
     * @param size Board dimension (e.g. NxN)
     */
    void setBoardSize(int size);

    /**
     * @brief Shows a confirmation dialog for starting a new game
     */
    void showConfirmNewGameDialog();

    /**
     * @brief Returns the mine board widget
     */
    MineBoard* mineBoard() const;

    /**
     * @brief Returns the side panel widget
     */
    SidePanel* sidePanel() const;

signals:
    /**
     * @brief Emitted when the user requests to go change difficulty
     */
    void changeDifficultyRequested();

private:
    MineBoard* m_board; ///< Mine board widget
    SidePanel* m_side;  ///< Side panel widget
};

#endif // CENTRALWIDGET_H
