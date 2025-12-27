#ifndef MINEBOARD_H
#define MINEBOARD_H

#include <QWidget>
#include <QVector>

class QGridLayout;
class QPushButton;

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

protected:
    void resizeEvent(QResizeEvent* event) override;

private:
    void rebuildBoard();
    QVector<QVector<QPushButton*>> m_buttons;
    static constexpr int MinButtonSize = 40;

private:
    QGridLayout* m_grid = nullptr;
    int m_boardSize = 0;
};

#endif // MINEBOARD_H

