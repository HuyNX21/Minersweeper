#ifndef BESTTIMESDIALOG_H
#define BESTTIMESDIALOG_H

#include <QDialog>
#include <QLabel>
#include <QTableWidget>
#include <QVBoxLayout>
#include <QHeaderView>
#include <QPushButton>
#include <QDebug>

#include "../../Model/BestTimeEntry.h"

class BestTimesDialog : public QDialog
{
    Q_OBJECT

public:
    explicit BestTimesDialog(QWidget* parent = nullptr);

    void setBestTimes(const QVector<BestTimeEntry>& times);

private:
    QLabel* m_titleLabel;
    QPushButton* m_closeButton;
    QTableWidget* m_table;
};


#endif // BESTTIMESDIALOG_H
