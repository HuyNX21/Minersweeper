#ifndef BOARD_GAME_CONTAINER_WIDGET_H
#define BOARD_GAME_CONTAINER_WIDGET_H

#include <QWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPushButton>

class BestTimesDialog;
class MineBoardGame;
class BestTimeEntry;
class SidePanel;

class BoardGameContainerWidget : public QWidget
{
    Q_OBJECT
public:
    explicit BoardGameContainerWidget(QWidget* parent = nullptr);
    void setBoardSize(int size);
    MineBoardGame* mineBoard() const;
    SidePanel* sidePanel() const;
    BestTimesDialog* bestTimesDialog() const;
    void showBestTimesRequested(const std::vector<BestTimeEntry>);
    void showWinMode(const BestTimeEntry);

signals:
    void changeDifficultyRequested();

private:
    MineBoardGame* m_board;
    SidePanel* m_side;
    BestTimesDialog* m_bestTimesDialog;

};

#endif