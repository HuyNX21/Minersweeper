#ifndef MINECONTROLLER_H
#define MINECONTROLLER_H

#pragma once
#include <QObject>
#include <QDebug>

class MineView;

class MineController : public QObject {
    Q_OBJECT
public:
    explicit MineController(MineView* view);

private slots:
    void onModeSelected(int size);
    void onBackRequested();
    void onCellClicked(int row, int col);

private:
    MineView* m_view;
};



#endif // MINECONTROLLER_H
