#ifndef BUTTONS_SELECT_MODE_H
#define BUTTONS_SELECT_MODE_H

#include <QWidget>
#include <QGridLayout>
#include <QPushButton>

class ButtonsSelectMode : public QWidget {
    Q_OBJECT
public:
    explicit ButtonsSelectMode(QWidget* parent = nullptr);
signals:
    void mode8Requested();
    void mode16Requested();
    void mode32Requested();
};

#endif