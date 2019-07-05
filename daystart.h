#pragma once
#ifndef DAYSTART_H
#define DAYSTART_H

#include "gamestep.h"
#include "dayspeaches.h"

class DayStart : public GameStep
{
public:
    DayStart();
    virtual ~DayStart();
    QVector<QString> doWork();              //выполняет функцию dayStart() из GameField
    void nextStage(GameStep *&ukazatel);    //меняет тип указателя на DaySpeaches
};

#endif // DAYSTART_H
