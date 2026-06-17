#ifndef BOARD_SELLECT_MODE_WIDGET_H
#define BOARD_SELLECT_MODE_WIDGET_H

#include <QWidget>
#include <QGridLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QVBoxLayout>
#include <QFont>
#include <QSizePolicy>

class ButtonsSelectMode;

class BoardSellectModeWidget : public QWidget {
    Q_OBJECT
public:
    explicit BoardSellectModeWidget(QWidget* parent = nullptr);
    void setupBoardSelect();

signals:
    void modeSelected(int size, int mines);

private:
    ButtonsSelectMode* m_button;
};

#endif // BOARD_SELLECT_MODE_WIDGET_H