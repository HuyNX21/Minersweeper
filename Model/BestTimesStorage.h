#ifndef BESTTIMESSTORAGE_H
#define BESTTIMESSTORAGE_H

#pragma once

#include <QVector>
#include <QString>
#include "BestTimeEntry.h"

class BestTimesStorage
{
public:
    BestTimesStorage();

    void load();
    void save() const;

    void addEntry(const BestTimeEntry& entry);
    const QVector<BestTimeEntry>& entries() const;

    void clear();

private:
    void sortAndTrim();

private:
    QVector<BestTimeEntry> m_entries;
    static constexpr int MaxEntries = 10;
};


#endif // BESTTIMESSTORAGE_H
