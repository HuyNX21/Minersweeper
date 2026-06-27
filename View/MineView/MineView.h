#ifndef MINEVIEW_H
#define MINEVIEW_H

#include <QMainWindow>
#include <QStackedWidget>

#define DEFAULT_SELLECT_MODE_SIZE 365

class QStackedWidget;
class BoardSellectModeWidget;
class BoardGameContainerWidget;
class BestTimesDialog;
class MineBoardGame;
class BestTimeEntry;
class SidePanel;

class MineView : public QMainWindow {
    Q_OBJECT
public:
    explicit MineView(QWidget* parent = nullptr);
    void showSelectScreen();
    void showBoardScreen();
    void setBoardSize(int size);
    void clearFixedSize();
    MineBoardGame* mineBoard() const;
    SidePanel* sidePanel() const;
    BoardSellectModeWidget* sellectBoard() const;
    BestTimesDialog* bestTimesDialog() const;
    void showBestTimesRequested(const std::vector<BestTimeEntry>);
    void showWinMode(const BestTimeEntry entry);

private:
    QStackedWidget*    m_stack;
    BoardSellectModeWidget* m_selectScreen;
    BoardGameContainerWidget* m_boardScreen;
};

#endif