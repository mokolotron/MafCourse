#include "dayvote.h"
#include "gamefield.h"

DayVote::DayVote()
{
}
DayVote::~DayVote(){}

QVector<QString> DayVote::doWork(){
    return *GameField::GetInstance()->dayVote();
}
void DayVote::nextStage(GameStep *&ukazatel){
    GameStep *tmp = ukazatel;
    delete tmp;
    ukazatel = new DayResult();
}
