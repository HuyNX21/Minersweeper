#ifndef MINEMODEL_H
#define MINEMODEL_H

#pragma once

#include <QObject>
#include <QVector>
#include <QPoint>

#include "gamestate.h"

class BoardModel;

class MineModel : public QObject
{
    Q_OBJECT

public:
    GameState state() const;

public:
    explicit MineModel(QObject* parent = nullptr);
    ~MineModel();

    // Khởi tạo ván chơi (chưa rải mine)
    void setup(int rows, int cols, int mineCount);

    // Người chơi click 1 ô
    void openCell(int row, int col);

    GameState getState() const;
    void setState(GameState);
    void toggleFlag(int row, int col);

signals:
    // Thông báo cho Controller để update View
    void cellOpened(int row, int col, int adjacent);
    void cellFlagChanged(int row, int col, bool flagged);
    void gameOver(bool win);

    void minesRevealed(int rowMineTriggered, int colMineTriggered, const QVector<QPoint>& mines);
    void stateChanged(GameState state);

    void flagChanged(int row, int col, bool flagged);
    void flagCountChanged(int used, int total);

private:
    void startGame(int safeRow, int safeCol);

private:
    BoardModel* m_board = nullptr;

    int m_rows      = 0;
    int m_cols      = 0;
    int m_mineCount = 0;

    GameState m_state = GameState::NotStarted;
};

#endif // MINEMODEL_H
