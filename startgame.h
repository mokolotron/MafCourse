#pragma once
#ifndef STARTGAME_H
#define STARTGAME_H

#include "gamestep.h"
#include "daystart.h"
#include <QString>

class StartGame : public GameStep
{
public:
    StartGame();
    virtual ~StartGame();
    QVector<QString> doWork();              //вызывает функцию StartGame() из GameField
    void nextStage(GameStep *&ukazatel);    //меняет тип указателя на DayStart
};

#endif // STARTGAME_H
