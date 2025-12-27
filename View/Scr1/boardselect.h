#ifndef BOARDSELECT_H
#define BOARDSELECT_H

#include <QWidget>

class BoardSelect : public QWidget {
    Q_OBJECT
public:
    explicit BoardSelect(QWidget* parent = nullptr);

signals:
    void mode8Requested();
    void mode16Requested();
    void mode32Requested();
};

#endif // BOARDSELLECT_H
