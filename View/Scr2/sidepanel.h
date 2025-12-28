#ifndef SIDEPANEL_H
#define SIDEPANEL_H

#include <QWidget>
#include <QTimer>
#include <QLabel>

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

signals:
    void backRequested();
    void pauseRequested();

private:
    QPushButton* b1;
    QPushButton* m_btnBack;
    QPushButton* m_pauseBtn;

    QLabel* m_flagLabel;
    QLabel* m_clockIcon;
    QLabel* m_timeLabel;

    QTimer m_timer;
    int    m_elapsedSec = 0;
};

#endif // SIDEPANEL_H
