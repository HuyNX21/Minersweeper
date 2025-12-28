#ifndef CENTRALWIDGET_H
#define CENTRALWIDGET_H

#include <QWidget>

class MineBoard;
class SidePanel;

class CentralWidget : public QWidget {
    Q_OBJECT
public:
    explicit CentralWidget(QWidget* parent = nullptr);

    // UI API cho Controller / MainView
    void setBoardSize(int size);
    MineBoard* mineBoard() const;
    SidePanel* sidePanel() const;

signals:
    // Intent UI
    void backRequested();

private:
    MineBoard* m_board;
    SidePanel* m_side;
};

#endif // CENTRALWIDGET_H
