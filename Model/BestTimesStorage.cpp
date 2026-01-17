#include "BestTimesStorage.h"
#include <QSettings>
#include <algorithm>

namespace
{
constexpr const char* GROUP_NAME = "BestTimes";
}

BestTimesStorage::BestTimesStorage()
{
}

void BestTimesStorage::load()
{
    QSettings settings;
    settings.beginGroup(GROUP_NAME);

    if (settings.childGroups().isEmpty() &&
        settings.childKeys().isEmpty())
    {
        settings.endGroup();
        return;
    }

    m_entries.clear();

    int size = settings.beginReadArray("Entries");
    for (int i = 0; i < size; ++i)
    {
        settings.setArrayIndex(i);

        BestTimeEntry entry;
        entry.seconds    = settings.value("seconds").toInt();
        entry.minefield  = settings.value("minefield").toString();
        entry.playerName = settings.value("player").toString();

        m_entries.push_back(entry);
    }

    settings.endArray();
    settings.endGroup();

    sortAndTrim();
}

void BestTimesStorage::save() const
{
    QSettings settings;
    settings.beginGroup(GROUP_NAME);

    settings.remove(""); // clear old data

    settings.beginWriteArray("Entries");
    for (int i = 0; i < m_entries.size(); ++i)
    {
        settings.setArrayIndex(i);
        settings.setValue("seconds", m_entries[i].seconds);
        settings.setValue("minefield", m_entries[i].minefield);
        settings.setValue("player", m_entries[i].playerName);
    }
    settings.endArray();

    settings.endGroup();
}


void BestTimesStorage::addEntry(const BestTimeEntry& entry)
{
    m_entries.push_back(entry);
    sortAndTrim();
}

const QVector<BestTimeEntry>& BestTimesStorage::entries() const
{
    return m_entries;
}

void BestTimesStorage::clear()
{
    m_entries.clear();

    QSettings settings;
    settings.beginGroup(GROUP_NAME);
    settings.remove("");
    settings.endGroup();
}

void BestTimesStorage::sortAndTrim()
{
    std::sort(m_entries.begin(), m_entries.end(),
              [](const BestTimeEntry& a, const BestTimeEntry& b)
              {
                  return a.seconds < b.seconds;
              });

    if (m_entries.size() > MaxEntries)
        m_entries.resize(MaxEntries);
}
