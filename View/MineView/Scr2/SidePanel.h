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

class SidePanel : public QWidget
{
    Q_OBJECT

public:
    explicit SidePanel(QWidget* parent = nullptr);
    
    void setPauseEnabled(bool enabled);
    void setStartOverEnabled(bool enabled);

    void setPauseButtonText(const QString& text);
    void setStartOverButtonText(const QString& text);
    void setChangeDifficultyButtonText(const QString& text);

    bool showConfirmNewGameDialog();

    void startClock();
    void pauseClock();
    void resumeClock();
    void resetClock();

    void setFlagCount(int used, int total);
    void resetFlagCount(int total);
    int  getFinalTime();


signals:
    void changeDifficultyRequested();
    void pauseRequested();
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

#endif