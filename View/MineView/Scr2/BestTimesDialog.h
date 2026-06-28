#ifndef BESTTIMESDIALOG_H
#define BESTTIMESDIALOG_H

#include <QDialog>
#include <QLabel>
#include <QTableWidget>
#include <QVBoxLayout>
#include <QHeaderView>
#include <QPushButton>
#include <QLineEdit>
#include <QRegularExpression>
#include <QDebug>

#include "BestTimeEntry.h"

class BestTimesDialog : public QDialog
{
    Q_OBJECT
public:
    enum class Mode
    {
        View,
        Entry
    };

    explicit BestTimesDialog(QWidget* parent = nullptr);

    void showBestTimes(const std::vector<BestTimeEntry> times);
    void enterWinMode(const BestTimeEntry newEntry);

signals:
    void entryConfirmed(const BestTimeEntry entry);

private slots:
    void onDoneClicked();

private:
    void updateUiForMode();

private:
    Mode m_mode = Mode::View;

    QTableWidget* m_table;
    QPushButton*  m_actionButton;
    int           m_entryRow = -1;

    QLabel* m_title;
};

#endif // BESTTIMESDIALOG_H
