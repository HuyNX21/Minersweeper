#ifndef CENTRALWIDGET_H
#define CENTRALWIDGET_H

#include <QWidget>

class MineBoard;
class SidePanel;

class CentralWidget : public QWidget
{
    Q_OBJECT

public:
    explicit CentralWidget(QWidget* parent = nullptr);
    void setBoardSize(int size);

private:
    MineBoard* m_board = nullptr;
    SidePanel* m_side = nullptr;

signals:
    void backRequested();
};

#endif // CENTRALWIDGET_H
