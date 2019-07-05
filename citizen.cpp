#include "citizen.h"
#include <gamefield.h>

Citizen::Citizen(){
}
Citizen::~Citizen(){
}
void Citizen::formRelations(int *relationships, int amountPlayers, int numberPlayer){
    GameField *a = GameField::GetInstance();
    int *thisAge = new int();
    *thisAge = a->getPlayer(numberPlayer)->getAge();
    for (int i = 0; i < amountPlayers; i++)
        if (i == numberPlayer)
            relationships[i] = 100000;
        else
        {
            if(*thisAge > a->getPlayer(i)->getAge())//меньше доверия к тем кто младше(разница в возрасте)
                relationships[i] = 99;
            else
                relationships[i] = 100;
        }
}
int Citizen::dayDecision(int *relationships, int amountPlayers, QVector<int>* otherPlayers, int thisPlayer, int stageOfVote, int person){
    if(person != -1)//День уже не первый?
    {
        if(stageOfVote == 1)//Только раннее обсуждение
        {
            if(GameField::GetInstance()->getPlayer(person)->getRole() == 2)//если был убит мафия прошлым днём
                for(int i = 0; i < amountPlayers; i++)
                {
                    if(i != thisPlayer && GameField::GetInstance()->getPlayer(i)->isAlive() )
                    {
                        if(otherPlayers->at(i) == person) //игрок голосовал против мафии
                            relationships[i] += 3;
                        else {//игрок голосовал не против мафии
                            relationships[i] -= 3;
                        }
                    }
                }
            else {
                for(int i = 0; i < amountPlayers; i++)
                {
                    if(i != thisPlayer && GameField::GetInstance()->getPlayer(i)->isAlive() )
                    {
                        if(otherPlayers->at(i) == person)
                            relationships[i] -= 2;
                        }
                    }
            }
            int death = GameField::GetInstance()->getKilledOnNight();
            if(death != -1){//если был ночью убит игрок
                if(GameField::GetInstance()->getPlayer(death)->getOratory() > GameField::GetInstance()->getPlayer(thisPlayer)->getOratory())
                    relationships[otherPlayers->value(death)] -= 6;
                else
                    relationships[otherPlayers->value(death)] -= 3;
            }
        }
        else { //Дневное голосование
            int srednee =  0;//чтобы человек мог изменять отношения только по советам тех, кому доверяет
            for(int i = 0; i < amountPlayers; i++)//проход по всем игрокам
            {
                Player *pl = GameField::GetInstance()->getPlayer(i);
                if(pl->isAlive() && i != thisPlayer)//если игрок жив и это не он сам
                {
                    int thisStamina = GameField::GetInstance()->getPlayer(thisPlayer)->getStamina();
                    if(pl->getOratory() > thisStamina && otherPlayers->at(i) == thisPlayer)//если он достаточно убедителен и проголосовал против самого игрока
                        relationships[i] -= 3;
                    else
                        if(pl->getOratory() > thisStamina && relationships[i] > srednee)//если он достаточно убедителен и игрок ему достаточно доверяет
                            relationships[otherPlayers->at(i)] -= 2;
                }
            }
        }
    }
    QList<int> *sameValues = new QList<int>();
    int min = relationships[thisPlayer];
    int minIndex;
    for(int i = 0; i < amountPlayers; i++)
        if(min > relationships[i] && i != thisPlayer && GameField::GetInstance()->getPlayer(i)->isAlive())
        {
            min = relationships[i];
        }
    for(int i = 0; i < amountPlayers; i++)
        if(min == relationships[i])
            sameValues->push_back(i);
    if(stageOfVote == 2 && sameValues->contains(person))//если голосуешь днём и в голосовании решения своего менять не стал
            return person;
    minIndex = sameValues->at(getrandom(0, sameValues->size() - 1));
    return minIndex;
}
void Citizen::nightRole(int *relationships, int amountPlayers, QVector<int> *votes, int thisPlayer){
    return;
}
