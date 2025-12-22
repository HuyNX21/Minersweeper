#ifndef MINEBOARD_H
#define MINEBOARD_H

#include <QWidget>
#include <QPushButton>

class QGridLayout;

class MineBoard : public QWidget
{
    Q_OBJECT

public:
    explicit MineBoard(QWidget* parent = nullptr);

    void setBoardSize(int size);

    bool hasHeightForWidth() const override;
    int  heightForWidth(int w) const override;

    QSize sizeHint() const override;
    QSize minimumSizeHint() const override;
    QVector<QVector<QPushButton*>> m_buttons;

protected:
    void resizeEvent(QResizeEvent* event) override;

private:
    void rebuildBoard();

private:
    QGridLayout* m_grid = nullptr;
    int m_boardSize = 0;
};

#endif // MINEBOARD_H

