#ifndef BESTTIMEENTRY_H
#define BESTTIMEENTRY_H

#include <QString>

struct BestTimeEntry
{
    int size = 0;
    int mines = 0;
    int seconds = 0;
    std::string playerName;

    std::string minefieldText() const
    {
        return std::to_string(size) + "x" + std::to_string(size) + " - " + std::to_string(mines) + " Mines";
    }
};

#endif // BESTTIMEENTRY_H
