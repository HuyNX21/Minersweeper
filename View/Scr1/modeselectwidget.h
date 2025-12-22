#ifndef MODESELECTWIDGET_H
#define MODESELECTWIDGET_H

#include <QWidget>

class BoardSelect;

class ModeSelectWidget: public QWidget
{
    Q_OBJECT
public:
    explicit ModeSelectWidget(QWidget* parent = nullptr);

signals:
    void modeSelected(int size);

protected:
    void resizeEvent(QResizeEvent* event) override;

private:
    BoardSelect* m_board;
    const int m_minButtonSize = 80;
};

#endif // MODESELECTWIDGET_H
