#include "dayresult.h"
#include "gamefield.h"

DayResult::DayResult(){
}
DayResult::~DayResult(){}
QVector<QString> DayResult::doWork(){
    return *GameField::GetInstance()->dayResult();
}
void DayResult::nextStage(GameStep *&ukazatel){
    GameStep *tmp = ukazatel;
    delete tmp;
    if(GameField::GetInstance()->isOnGame())
    {
        ukazatel = new Night();
    }
    else {
        ukazatel = new EndOfGame();
    }
}
