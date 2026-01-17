#ifndef SIDEPANEL_H
#define SIDEPANEL_H

#include <QWidget>
#include <QTimer>
#include <QLabel>
#include <QMessageBox>
#include <QDebug>
#include <QGridLayout>
#include <QPushButton>
#include <QVBoxLayout>

class QPushButton;

/**
 * @class SidePanel
 * @brief Control panel widget for game actions and status
 *
 * Displays game controls (back, pause, restart),
 * flag counter, and elapsed time.
 */
class SidePanel : public QWidget
{
    Q_OBJECT

public:
    /**
     * @brief Creates the side panel widget
     * @param parent Parent widget
     */
    explicit SidePanel(QWidget* parent = nullptr);

    /**
     * @brief Starts the game clock from zero
     */
    void startClock();

    /**
     * @brief Pauses the game clock
     */
    void pauseClock();

    /**
     * @brief Resumes the paused game clock
     */
    void resumeClock();

    /**
     * @brief Resets the game clock to zero
     */
    void resetClock();

    /**
     * @brief Sets the text of the pause button
     * @param text Button label
     */
    void setPauseButtonText(const QString& text);

    /**
     * @brief Enables or disables the pause button
     * @param enabled True to enable the button
     */
    void setPauseEnabled(bool enabled);

    /**
     * @brief Enables or disables the start-over button
     * @param enabled True to enable the button
     */
    void setStartOverEnabled(bool enabled);

    /**
     * @brief Sets the text of the start over button
     * @param text Button label
     */
    void setStartOverButtonText(const QString& text);

    /**
     * @brief Sets the text of the Change Difficulty button
     * @param text Button label
     */
    void setChangeDifficultyButtonText(const QString& text);

    /**
     * @brief Updates the flag counter display
     * @param used Number of flags used
     * @param total Total number of available flags
     */
    void setFlagCount(int used, int total);

    /**
     * @brief Resets the flag counter with a new total
     * @param total Total number of available flags
     */
    void resetFlagCount(int total);

    /**
     * @brief Shows a confirmation dialog for starting a new game
     * @return True if user start new game, false if user keep curent game
     */
    bool showConfirmNewGameDialog();

signals:
    /**
     * @brief Emitted when the user requests to go Change Difficulty
     */
    void changeDifficultyRequested();

    /**
     * @brief Emitted when the user requests to pause or resume the game
     */
    void pauseRequested();

    /**
     * @brief Emitted when the user requests to start over
     */
    void startOverRequest();

private:
    QPushButton* m_btnStartOver;            ///< Start-over button
    QPushButton* m_btnChangeDifficulty;     ///< Change Difficulty button
    QPushButton* m_btnPause;                ///< Pause/resume button

    QLabel* m_flagLabel;                    ///< Flag icon label
    QLabel* m_flagCountLabel;               ///< Flag counter label
    QLabel* m_clockIcon;                    ///< Clock icon label
    QLabel* m_timeLabel;                    ///< Elapsed time display

    QTimer m_timer;                         ///< Timer for tracking elapsed time
    int    m_elapsedSec = 0;                ///< Elapsed time in seconds
};

#endif // SIDEPANEL_H
