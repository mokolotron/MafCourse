#pragma once
#ifndef NIGHT_H
#define NIGHT_H

#include "daystart.h"
#include "gamestep.h"


class Night : public GameStep
{
public:
    Night();
    virtual ~Night();
    QVector<QString> doWork();              //выполняет функцию night() из GameField
    void nextStage(GameStep *&ukazatel);    //меняет тип указателя на dayStart, либо на EndOfGame, если игра окончена
};

#endif // NIGHT_H
