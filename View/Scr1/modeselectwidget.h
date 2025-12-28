#ifndef MODESELECTWIDGET_H
#define MODESELECTWIDGET_H

#include <QWidget>

class BoardSelect;

class ModeSelectWidget : public QWidget {
    Q_OBJECT
public:
    explicit ModeSelectWidget(QWidget* parent = nullptr);

protected:
    void resizeEvent(QResizeEvent* event) override;

signals:
    void modeSelected(int size, int mines);

private:
    BoardSelect* m_board;
};

#endif // MODESELECTWIDGET_H
