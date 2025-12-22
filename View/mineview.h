#ifndef MINEVIEW_H
#define MINEVIEW_H

#include <QWidget>
#include <QMainWindow>

class QStackedWidget;
class ModeSelectWidget;
class CentralWidget;

class MineView : public QMainWindow
{
public:
    explicit MineView(QWidget* parent = nullptr);
private:
    QStackedWidget*   m_stack        = nullptr;
    ModeSelectWidget* m_selectScreen = nullptr;
    CentralWidget*     m_boardScreen  = nullptr;
};

#endif // MINEVIEW_H
