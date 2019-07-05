#include "endofgame.h"
#include "gamefield.h"

EndOfGame::EndOfGame(){
}
EndOfGame::~EndOfGame(){}
QVector<QString> EndOfGame::doWork(){
    return *GameField::GetInstance()->endOfGame();
}
void EndOfGame::nextStage(GameStep *&ukazatel){
    GameStep *tmp = ukazatel;
    delete tmp;
    ukazatel = nullptr;
}
