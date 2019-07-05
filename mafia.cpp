#include "mafia.h"
#include <QDebug>
#include "gamefield.h"

int Mafia::collectiveDecision = -1;
int Mafia::nightKill = -1;
Mafia::Mafia(){
    collectiveDecision = -1;
    nightKill = -1;
}
Mafia::~Mafia(){
}
int Mafia::nightKillMafia(){
    return nightKill;
}

void Mafia::formRelations(int *relationships, int amountPlayers, int numberPlayer){
    for (int i = 0; i < amountPlayers; i++)
            if (i == numberPlayer)
                relationships[i] = 100000;
            else
                relationships[i] = 100;
    mafia = GameField::GetInstance()->getMafiaList();
    for (auto it = mafia.begin(); it != mafia.end(); it++)
        relationships[*it] = 100000;
}
int Mafia::dayDecision(int *relationships, int amountPlayers, QVector<int>* otherPlayers, int thisPlayer, int stageOfVote, int person){
    if(person != -1)//(есть результаты дневного обсуждения или голосования)
    {
        if(stageOfVote == 1)
            nightKill = -1;
        else {
            int thisStamina = GameField::GetInstance()->getPlayer(thisPlayer)->getStamina();
            for(int i = 0; i < amountPlayers; i++)
                if(mafia.contains(i) == false)
                {
                    if(GameField::GetInstance()->getPlayer(i)->getOratory() > thisStamina && otherPlayers->at(i) == thisPlayer && GameField::GetInstance()->getPlayer(i)->isAlive())
                    {
                        relationships[i] += 3;
                    }
                    else {
                        relationships[i]--;
                    }
                }
        }
    }
    if(collectiveDecision != -1)
    {
        int thisFoxy = GameField::GetInstance()->getPlayer(thisPlayer)->getFoxy();
        if(thisFoxy > 5)
        {
            QVector<int> amountVotes(amountPlayers, 0);

            for(int i = 0; i < amountPlayers; i++)
                if(otherPlayers->at(i) != -1 && !mafia.contains(i))//если игрок уже голосовал (без учета мафии)
                    amountVotes[otherPlayers->at(i)] += 1;//количество голосов против игрока
            int amountAliveMafia = 0;
            for(int i = 0; i < mafia.size(); i++)
                if(GameField::GetInstance()->getPlayer(mafia.at(i))->isAlive())//сколько живой мафии
                {
                    if(mafia.at(i) >= thisPlayer)
                        amountAliveMafia++;
                    else {
                        amountVotes[otherPlayers->at(mafia.at(i))] += 1;
                    }
                }
            //поиск первого и второго максимума
            int fMax = 0, sMax = 0;
            for (int i = 0; i < amountPlayers; i++)
                    if (amountVotes[fMax] < amountVotes[i])
                        fMax = i;
            if(mafia.contains(fMax))//Если игрок против которого собираются голосовать - мафия
            {
                for (int i = 0; i < amountPlayers; i++)
                    if (fMax != i)
                        if (amountVotes[sMax] < amountVotes[i])
                            sMax = i;
                if(sMax + amountAliveMafia >= fMax)//если он видит, что оставшимися игроками можно спасти мафию
                {
                    return sMax;
                }
                else {
                    return fMax;//иначе голосует как все
                }
            }

        }
        else
            return collectiveDecision;
    }
    QList<int> *sameValues = new QList<int>();
    int max = -1;
    int maxIndex;
    for(int i = 0; i < amountPlayers; i++)
        if(max < relationships[i] && mafia.contains(i) == false && GameField::GetInstance()->getPlayer(i)->isAlive())
        {
            max = relationships[i];
        }
    for(int i = 0; i < amountPlayers; i++)
        if(max == relationships[i])
            sameValues->push_back(i);
    maxIndex = sameValues->at(getrandom(0, sameValues->size() - 1));
    if(stageOfVote == 2)
    {
        if (sameValues->contains(person))
        {
            collectiveDecision = person;
            return person;
        }
        else {
            collectiveDecision = person;
        }
    }
    return maxIndex;
}
void Mafia::nightRole(int *relationships, int amountPlayers, QVector<int> *votes, int thisPlayer){
    collectiveDecision = -1;
    if(nightKill != -1)
        return;
    else {
        QList<int> votesAgaingsMafia;
        for(int i = 0; i < amountPlayers; i++)
        {
            int vote = votes->value(i);
            if(mafia.contains(vote) && !mafia.contains(i) && GameField::GetInstance()->getPlayer(i)->isAlive())
            {
                votesAgaingsMafia.push_back(i);
            }
        }
        if(votesAgaingsMafia.size() == 0){
            int killPlayer = -1;
            QList<int> peaceful = GameField::GetInstance()->getCitizenList();
            killPlayer = peaceful[getrandom(0, peaceful.size() - 1)];
            nightKill = killPlayer;
            return;
        }
        else {
            int maxOratoryPlayer = -1;
            int maxOratory = 0;
            for(auto it = votesAgaingsMafia.begin(); it != votesAgaingsMafia.end(); ++it)
            {
                int thisOratory = GameField::GetInstance()->getPlayer(*it)->getOratory();
                if(thisOratory >= maxOratory)
                {
                    maxOratoryPlayer = *it;
                    maxOratory = thisOratory;
                }
            }
            nightKill = maxOratoryPlayer;
            return;
        }
    }
}
