#ifndef CUSTOMGAMEDIALOG_H
#define CUSTOMGAMEDIALOG_H

#include <QDialog>

class QLabel;
class QSpinBox;
class QPushButton;

class CustomGameDialog : public QDialog
{
    Q_OBJECT

public:
    explicit CustomGameDialog(QWidget *parent = nullptr);

    int boardWidthHeight() const;
    int minePercent() const;

    void setBoardSize(int size);
    void setMinePercent(int percent);

private:
    void setupUi();

private slots:
    void updateMinePercentLimit(int boardSize);

private:
    QLabel*      m_sizeLabel;
    QLabel*      m_percentLabel;

    QSpinBox*    m_sizeSpin;
    QSpinBox*    m_percentSpin;

    QPushButton* m_playButton;
    QPushButton* m_cancelButton;

    QLabel* m_sizeHintLabel;
    QLabel* m_mineHintLabel;
};

#endif // CUSTOMGAMEDIALOG_H