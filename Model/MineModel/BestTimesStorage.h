#ifndef BESTTIMESSTORAGE_H
#define BESTTIMESSTORAGE_H

#pragma once

#include "BLKC_Common.h"
#include "BestTimeEntry.h"

class BestTimesStorage
{
public:
    BestTimesStorage();

    bool load();
    bool save() const;

    void addEntry(const BestTimeEntry entry);
    void clear();

    std::vector<BestTimeEntry> entries() const;

    void sortEntries();

private:
    std::string m_filePath;
    std::vector<BestTimeEntry> m_entries;
};


#endif // BESTTIMESSTORAGE_H