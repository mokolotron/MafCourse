#pragma once
#ifndef DAYRESULT_H
#define DAYRESULT_H

#include "gamestep.h"
#include "night.h"
#include "endofgame.h"

class DayResult : public GameStep
{
public:
    DayResult();
    virtual ~DayResult();
    QVector<QString> doWork();              //вызывает функцию dayResult() из GameField
    void nextStage(GameStep *&ukazatel);    //меняет тип указателя на Night, либо на EndOfGame, если игра окончена
};

#endif // DAYRESULT_H
