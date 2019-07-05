#include "startgame.h"
#include "gamefield.h"

StartGame::StartGame()
{
}
StartGame::~StartGame(){}
QVector<QString> StartGame::doWork(){
    return *GameField::GetInstance()->startGame();
}
void StartGame::nextStage(GameStep *&ukazatel){
    GameStep *tmp = ukazatel;
    delete tmp;
    ukazatel = new DayStart();
}
