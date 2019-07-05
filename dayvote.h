#pragma once
#ifndef DAYVOTE_H
#define DAYVOTE_H

#include "gamestep.h"
#include "dayresult.h"
#include <QString>

class DayVote : public GameStep
{
public:
    DayVote();
    virtual ~DayVote();
    QVector<QString> doWork();              //выполняет функцию dayVote() из GameField
    void nextStage(GameStep *&ukazatel);    //меняет тип указателя на Night
};

#endif // DAYVOTE_H
