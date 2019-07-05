#include "dayspeaches.h"
#include "gamefield.h"

DaySpeaches::DaySpeaches()
{
}
DaySpeaches::~DaySpeaches(){}

QVector<QString> DaySpeaches::doWork(){
    return *GameField::GetInstance()->daySpeach();
}
void DaySpeaches::nextStage(GameStep *&ukazatel){
    GameStep *tmp = ukazatel;
    delete tmp;
    ukazatel = new DayVote();
}
