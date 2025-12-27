#ifndef MINECONTROLLER_H
#define MINECONTROLLER_H

#pragma once
#include <QObject>

class MineView;

class MineController : public QObject {
    Q_OBJECT
public:
    explicit MineController(MineView* view);

private slots:
    void onModeSelected(int size);
    void onBackRequested();

private:
    MineView* m_view;
};



#endif // MINECONTROLLER_H
