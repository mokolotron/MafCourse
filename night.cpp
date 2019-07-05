#include "night.h"
#include "gamefield.h"

Night::Night(){
}
Night::~Night(){}
QVector<QString> Night::doWork(){
    return *GameField::GetInstance()->night();
}
void Night::nextStage(GameStep *&ukazatel){
    GameStep *tmp = ukazatel;
    delete tmp;
    if(GameField::GetInstance()->isOnGame())
    {
        ukazatel = new DayStart();
    }
    else {
        ukazatel = new EndOfGame();
    }
}
