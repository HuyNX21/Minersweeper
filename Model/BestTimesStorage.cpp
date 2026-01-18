#include "BestTimesStorage.h"

BestTimesStorage::BestTimesStorage()
{
    m_filePath =
        QCoreApplication::applicationDirPath() + "/best_times.json";
}

bool BestTimesStorage::load()
{
    QFile file(m_filePath);
    if (!file.exists())
        return false;

    if (!file.open(QIODevice::ReadOnly))
        return false;

    const QJsonDocument doc =
        QJsonDocument::fromJson(file.readAll());

    if (!doc.isObject())
        return false;

    const QJsonObject root = doc.object();
    const QJsonArray array =
        root.value("best_times").toArray();

    if (array.isEmpty())
        return false;

    m_entries.clear();
    m_entries.reserve(array.size());

    for (const QJsonValue& value : array)
    {
        if (!value.isObject())
            continue;

        const QJsonObject obj = value.toObject();

        BestTimeEntry entry;
        entry.size       = obj.value("size").toInt();
        entry.mines      = obj.value("mines").toInt();
        entry.seconds    = obj.value("seconds").toInt();
        entry.playerName = obj.value("player").toString();

        if (entry.size <= 0 || entry.mines <= 0 || entry.seconds <= 0)
            continue;

        m_entries.push_back(entry);
    }

    sortEntries();

    return !m_entries.isEmpty();
}


bool BestTimesStorage::save() const
{
    QJsonArray array;

    for (const BestTimeEntry& entry : m_entries)
    {
        QJsonObject obj;
        obj["size"]    = entry.size;
        obj["mines"]   = entry.mines;
        obj["seconds"] = entry.seconds;
        obj["player"]  = entry.playerName;

        array.append(obj);
    }

    QJsonObject root;
    root["best_times"] = array;

    QFile file(m_filePath);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Truncate))
        return false;

    file.write(
        QJsonDocument(root).toJson(QJsonDocument::Indented)
        );

    return true;
}


void BestTimesStorage::sortEntries()
{
    std::sort(m_entries.begin(), m_entries.end(),
              [](const BestTimeEntry& a, const BestTimeEntry& b)
              {
                  if (a.size != b.size)
                      return a.size > b.size;

                  if (a.mines != b.mines)
                      return a.mines > b.mines;

                  if (a.seconds != b.seconds)
                      return a.seconds < b.seconds;

                  return false;
              });
}

void BestTimesStorage::addEntry(const BestTimeEntry& entry)
{
    m_entries.push_back(entry);
}

void BestTimesStorage::clear()
{
    m_entries.clear();
}

const QVector<BestTimeEntry>& BestTimesStorage::entries() const
{
    return m_entries;
}
