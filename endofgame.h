#pragma once
#ifndef ENDOFGAME_H
#define ENDOFGAME_H

#include "gamestep.h"

class EndOfGame : public GameStep
{
public:
    EndOfGame();
    virtual ~EndOfGame();
    QVector<QString> doWork();              //выполняет функцию endOfGame() из GameField
    void nextStage(GameStep *&ukazatel);    //устанавливает указатель в nullptr
};

#endif // ENDOFGAME_H
