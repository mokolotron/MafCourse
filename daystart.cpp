#include "daystart.h"
#include "gamefield.h"

DayStart::DayStart(){
}
DayStart::~DayStart(){}
QVector<QString> DayStart::doWork(){
    return *GameField::GetInstance()->dayStart();
}
void DayStart::nextStage(GameStep *&ukazatel){
    GameStep *tmp = ukazatel;
    delete tmp;
    ukazatel = new DaySpeaches();
}
