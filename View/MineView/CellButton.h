#ifndef CELLBUTTON_H
#define CELLBUTTON_H

#include <QObject>
#include <QPushButton>
#include <QMouseEvent>

class CellButton : public QPushButton
{
    Q_OBJECT
public:
    explicit CellButton(QWidget* parent = nullptr)
        : QPushButton(parent) {}

    void setFlagged(bool f) { m_flagged = f; }
    bool isFlagged() const  { return m_flagged; }

signals:
    void rightClicked();
    void leftClicked();

protected:
    void mousePressEvent(QMouseEvent* e) override {
        if (e->button() == Qt::RightButton) {
            emit rightClicked();
            e->accept();
            return;
        }

        if (e->button() == Qt::LeftButton) {
            if (m_flagged) {
                e->accept();
                return;
            }
            
            QPushButton::mousePressEvent(e);
            emit leftClicked();
            e->accept();
            return;
        }

        QPushButton::mousePressEvent(e);
    }

private:
    bool m_flagged = false;
};


#endif // CELLBUTTON_H
