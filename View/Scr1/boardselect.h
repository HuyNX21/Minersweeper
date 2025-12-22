#ifndef BOARDSELECT_H
#define BOARDSELECT_H

#include <QWidget>

class BoardSelect : public QWidget
{
    Q_OBJECT
public:
    explicit BoardSelect(QWidget* parent = nullptr);

signals:
    void modeSelected(int size);   // ⭐ NEW
};

#endif // BOARDSELLECT_H
