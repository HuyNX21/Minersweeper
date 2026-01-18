#ifndef BESTTIMEENTRY_H
#define BESTTIMEENTRY_H

#include <QString>

struct BestTimeEntry
{
    int size = 0;
    int mines = 0;
    int seconds = 0;
    QString playerName;

    QString minefieldText() const
    {
        return QString("%1x%1 - %2 Mines")
        .arg(size)
            .arg(mines);
    }
};

#endif // BESTTIMEENTRY_H
