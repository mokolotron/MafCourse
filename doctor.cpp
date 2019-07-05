#include "doctor.h"
#include "gamefield.h"
#include <QDebug>

int Doctor::healAtNight = -1;
Doctor::Doctor(){
    healAtNight = -1;
}

Doctor::~Doctor(){
}
void Doctor::formRelations(int *relationships, int amountPlayers, int numberPlayer){
    GameField *a = GameField::GetInstance();
    int *thisAge = new int();
    *thisAge = a->getPlayer(numberPlayer)->getAge();
    for (int i = 0; i < amountPlayers; i++)
        if (i == numberPlayer)
            relationships[i] = 100000;
        else
        {
            relationships[i] = 100;
        }
}
int Doctor::dayDecision(int *relationships, int amountPlayers, QVector<int> *otherPlayers, int thisPlayer, int stageOfVote, int person){
    if(person != -1)
    {
        if(stageOfVote == 1)//Только раннее обсуждение
        {
            int death = GameField::GetInstance()->getKilledOnNight();
            if(death == -1)//спас игрока от смерти
            {
                if(healAtNight != thisPlayer)//но не самого себя
                    relationships[healAtNight] = 10000;
            }
            else
            {
                if(death != -1){//если был ночью убит игрок
                    if(GameField::GetInstance()->getPlayer(death)->getOratory() > GameField::GetInstance()->getPlayer(thisPlayer)->getOratory())
                        relationships[otherPlayers->value(death)] -= 6;
                    else
                        relationships[otherPlayers->value(death)] -= 3;
                }
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
void Doctor::nightRole(int *relationships, int amountPlayers, QVector<int> *votes, int thisPlayer){
    healAtNight = -1;//обновляем старое значение игрока для лечения
    int killedOnDay = GameField::GetInstance()->getKilledOnDay();
    if(killedOnDay != -1){
        //Игрок ночью не спит, так что обновляем его отношения с другими
        if(GameField::GetInstance()->getPlayer(killedOnDay)->getRole() == 2)//если был убит мафия прошлым днём
            for(int i = 0; i < amountPlayers; i++)
            {
                if(i != thisPlayer && GameField::GetInstance()->getPlayer(i)->isAlive() )
                {
                    if(votes->at(i) == killedOnDay) //игрок голосовал против мафии
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
                    if(votes->at(i) == killedOnDay)
                        relationships[i] -= 2;
                    }
                }
        }
        //Выбор игрока для лечения
        if(GameField::GetInstance()->getPlayer(killedOnDay)->getRole() == 2)//если убили мафию, то лечит второго по голосам
        {
            QVector<int> amountVotes(amountPlayers, 0);
            for(int i = 0; i < amountPlayers; i++)
                if(votes->at(i) != -1)
                    amountVotes[votes->at(i)]++;
            amountVotes[killedOnDay] = 0;
            if(healYourself == false)//нельзя второй раз себя лечить
                amountVotes[thisPlayer] = 0;
            int indexHeal = std::distance(amountVotes.begin(), std::max_element(amountVotes.begin(), amountVotes.end()));
            if(indexHeal == thisPlayer)//лечу себя
                healYourself = false;
            healAtNight = indexHeal;
        }
        else {//лечит того, кому больше всего доверяет
            int whomeHeal = 1;
            if(healYourself)
                whomeHeal = qrand() % 3;
            if(whomeHeal != 0)
            {
                int maxRelations = 0;
                int maxRelationsIndex = -1;
                for(int i = 0; i < amountPlayers; i++)
                    if(i != thisPlayer)
                        if(GameField::GetInstance()->getPlayer(i)->isAlive() && relationships[i] >= maxRelations)
                        {
                            maxRelations = relationships[i];
                            maxRelationsIndex = i;
                        }
                healAtNight = maxRelationsIndex;
            }
            else {
                healYourself = false;
                healAtNight = thisPlayer;
            }
        }
    }
}
int Doctor::healPlayer(){
    return healAtNight;
}
