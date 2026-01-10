#ifndef SIDEPANEL_H
#define SIDEPANEL_H

#include <QWidget>
#include <QTimer>
#include <QLabel>
#include <QMessageBox>
#include <QDebug>

class QPushButton;

class SidePanel : public QWidget
{
    Q_OBJECT
public:
    explicit SidePanel(QWidget* parent = nullptr);

    void startClock();
    void pauseClock();
    void resumeClock();
    void resetClock();

    void setPauseButtonText(const QString& text);
    void setPauseEnabled(bool enabled);
    void setStartOverEnabled(bool enabled);
    void setFlagCount(int used, int total);
    void resetFlagCount(int total);

    void showConfirmNewGameDialog();

signals:
    void backRequested();
    void pauseRequested();
    void startOverRequest();

private:
    QPushButton* m_btnStartOver;
    QPushButton* m_btnBack;
    QPushButton* m_btnPause;

    QLabel* m_flagLabel;
    QLabel* m_flagCountLabel;
    QLabel* m_clockIcon;
    QLabel* m_timeLabel;

    QTimer m_timer;
    int    m_elapsedSec = 0;
};

#endif // SIDEPANEL_H
