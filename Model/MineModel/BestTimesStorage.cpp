#include "pch.h"
#include <fstream>
#include <filesystem>
#include <nlohmann/json.hpp>

#include "BestTimesStorage.h"
#include "HmacUtils.h"

using json = nlohmann::json;

BestTimesStorage::BestTimesStorage()
{
    m_filePath =
        (std::filesystem::current_path() / "best_times.json").string();
}

bool BestTimesStorage::save() const
{
    json bestTimes = json::array();

    for (const auto& entry : m_entries)
    {
        bestTimes.push_back(
        {
            {"size", entry.size},
            {"mines", entry.mines},
            {"seconds", entry.seconds},
            {"player", entry.playerName}
        });
    }

    const std::string dataToSign =
        bestTimes.dump();

    const std::string signature =
        hmacSha256(
            dataToSign,
            "MySecretKey123");

    json root;

    root["best_times"] = bestTimes;
    root["signature"] = signature;

    std::ofstream file(m_filePath);

    if (!file)
        return false;

    file << root.dump(4);

    return true;
}

bool BestTimesStorage::load()
{
    std::ifstream file(m_filePath);

    if (!file)
        return false;

    json root;

    try
    {
        file >> root;
    }
    catch (...)
    {
        return false;
    }

    if (!root.contains("best_times"))
        return false;

    if (!root.contains("signature"))
        return false;

    json bestTimes =
        root["best_times"];

    std::string storedSignature =
        root["signature"];

    std::string calculatedSignature =
        hmacSha256(
            bestTimes.dump(),
            "MySecretKey123");

    if (storedSignature != calculatedSignature)
    {
        std::cout
            << "Save file modified!"
            << std::endl;

        return false;
    }

    m_entries.clear();

    for (const auto& item : bestTimes)
    {
        BestTimeEntry entry;

        entry.size =
            item.value("size", 0);

        entry.mines =
            item.value("mines", 0);

        entry.seconds =
            item.value("seconds", 0);

        entry.playerName =
            item.value("player", "");

        if (entry.size <= 0)
            continue;

        if (entry.mines <= 0)
            continue;

        if (entry.seconds <= 0)
            continue;

        m_entries.push_back(entry);
    }

    sortEntries();

    return !m_entries.empty();
}

void BestTimesStorage::sortEntries()
{
    std::sort(
        m_entries.begin(),
        m_entries.end(),
        [](const BestTimeEntry& a,
           const BestTimeEntry& b)
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

void BestTimesStorage::addEntry(const BestTimeEntry entry)
{
    m_entries.push_back(entry);
}

void BestTimesStorage::clear()
{
    m_entries.clear();
}

std::vector<BestTimeEntry> BestTimesStorage::entries() const
{
    return m_entries;
}

