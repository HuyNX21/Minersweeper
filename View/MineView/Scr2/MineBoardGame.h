#ifndef MINE_BOARD_GAME_H
#define MINE_BOARD_GAME_H

#include <QWidget>
#include <QVector>
#include <QGridLayout>
#include <QPushButton>
#include <QResizeEvent>
#include <QtMath>
#include <QStyle>
#include <QSizePolicy>
#include <QDebug>
#include <QPainter>
#include <QLabel>

class QGridLayout;
class QPushButton;

class MineBoardGame : public QWidget
{
    Q_OBJECT
public:
    explicit MineBoardGame(QWidget* parent = nullptr);
    void setBoardSize(int size);
    void rebuildBoard();
    void openCell(int row, int col, int value);
    void resetBoard();
    void updateCellFont();
    void revealMine(int row, int col, bool flagMineTriggered);
    void showPausedOverlay(bool show);
    void setFlag(int row, int col, bool flagged);

signals:
    void cellClicked(int row, int col);
    void cellRightClicked(int row, int col);

private:
    QVector<QVector<QPushButton*>> m_buttons;
    QGridLayout* m_grid = nullptr;
    QWidget* m_pauseOverlay = nullptr;
    int m_boardSize = 0;
    int m_buttonCellSize = 0;
};

#endif