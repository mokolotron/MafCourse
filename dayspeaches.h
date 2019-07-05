#pragma once
#ifndef DAYSPEACHES_H
#define DAYSPEACHES_H

#include "gamestep.h"
#include "dayvote.h"
#include <QString>

class DaySpeaches : public GameStep
{
public:
    DaySpeaches();
    virtual ~DaySpeaches();
    QVector<QString> doWork();              //выполняет функцию daySpeaches() из GameField
    void nextStage(GameStep *&ukazatel);    //меняет тип указателя на DayVote
};

#endif // DAYSPEACHES_H
