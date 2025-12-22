#ifndef SIDEPANEL_H
#define SIDEPANEL_H

#include <QWidget>

class QPushButton;

class SidePanel : public QWidget
{
    Q_OBJECT
public:
    explicit SidePanel(QWidget* parent = nullptr);

signals:
    void backRequested();

private:
    QPushButton* b1;
    QPushButton* m_btnBack;
    QPushButton* b3;
};

#endif // SIDEPANEL_H
