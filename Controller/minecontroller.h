#ifndef MINECONTROLLER_H
#define MINECONTROLLER_H

#pragma once

#include <QObject>

#include "../Model/GameState.h"

class MineView;
class MineModel;

class MineController : public QObject
{
    Q_OBJECT
public:
    explicit MineController(MineView* view,MineModel* model, QObject* parent = nullptr);

private slots:
    void onModeSelected(int size, int mines);
    void onBackRequested();
    void onCellClicked(int row, int col);

    // Model → View
    void onCellOpened(int row, int col, int value);
    void onGameOver(bool win);

    void onMinesRevealed(int rowMineTriggered, int colMineTriggered, const QVector<QPoint>& mines);
    void onPauseRequested();
    void onGameStateChanged(GameState);

    void onCellRightClicked(int , int);
    void onFlagChanged(int, int, bool);
    void onFlagCountChanged(int , int);

    void onStartOverRequest();

private:
    MineView*  m_view;
    MineModel* m_model;
    int m_sizeOld;
    int m_mineOld;
};


#endif // MINECONTROLLER_H
