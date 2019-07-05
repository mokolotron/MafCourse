#pragma once
#ifndef GAMESTEP_H
#define GAMESTEP_H

#include <QString>

class GameStep
{
public:
    GameStep();
    virtual ~GameStep() = 0;
    virtual QVector<QString> doWork() = 0;              //Вызывает функцию, соответствующую классу из GameField
    virtual void nextStage(GameStep *&ukazatel) = 0;    //Переписывает указатель, заменяя его тип на тип следующей стадии
};

#endif // GAMESTEP_H
