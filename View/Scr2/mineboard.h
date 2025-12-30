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

    // ===== API cho Controller =====
    void openCell(int row, int col, int value);
    void revealMine(int row, int col, bool flagMineTriggered);
    void resetBoard();

    void showPausedOverlay(bool show);
    void setFlag(int row, int col, bool flagged);

signals:
    void cellClicked(int row, int col);
    void cellRightClicked(int row, int col);

protected:
    void resizeEvent(QResizeEvent* event) override;

private:
    void rebuildBoard();
    void updateCellFont();

private:
    QVector<QVector<QPushButton*>> m_buttons;
    static constexpr int MinButtonSize = 40;
    QGridLayout* m_grid = nullptr;
    int m_boardSize = 0;
    QWidget* m_pauseOverlay = nullptr;
};

#endif // MINEBOARD_H

