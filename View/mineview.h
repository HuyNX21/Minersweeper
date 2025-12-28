#ifndef MINEVIEW_H
#define MINEVIEW_H

#include <QWidget>
#include <QMainWindow>

class QStackedWidget;
class ModeSelectWidget;
class CentralWidget;
class MineBoard;

class MineView : public QMainWindow {
    Q_OBJECT
public:
    explicit MineView(QWidget* parent = nullptr);

    // UI API cho Controller
    void showSelectScreen();
    void showBoardScreen();
    void setBoardSize(int size);
    MineBoard* board() const;

signals:
    // Forward intent từ screen
    void modeSelected(int size);
    void backRequested();

private:
    QStackedWidget*   m_stack;
    ModeSelectWidget* m_selectScreen;
    CentralWidget*    m_boardScreen;
};


#endif // MINEVIEW_H
