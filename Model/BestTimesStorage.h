#ifndef BESTTIMESSTORAGE_H
#define BESTTIMESSTORAGE_H

#pragma once

#include <QVector>
#include <QString>
#include <QFile>
#include <QDir>
#include <QStandardPaths>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QSettings>
#include <QCoreApplication>
#include "BestTimeEntry.h"

class BestTimesStorage
{
public:
    BestTimesStorage();

    bool load();                // load từ file JSON
    bool save() const;          // save ra file JSON

    void addEntry(const BestTimeEntry& entry);
    void clear();

    const QVector<BestTimeEntry>& entries() const;

    void sortEntries();

private:
    QString m_filePath;
    QVector<BestTimeEntry> m_entries;
};


#endif // BESTTIMESSTORAGE_H
