#pragma once
#ifndef MAFIA_H
#define MAFIA_H

#include <QList>
#include <card.h>
#include <QTime>


class Mafia : public Card
{
private:
    QList<int> mafia;//список мафий
    static int collectiveDecision;//содержит коллективное решение по дневному голосованию
    static int nightKill;//содержит номер игрока, которого мафия собирается убить
public:
    Mafia();
    virtual ~Mafia();
    void formRelations(int *relationships, int amountPlayers, int numberPlayer);//формирование отношений
    int dayDecision(int *relationships, int amountPlayers, QVector<int>* otherPlayers, int thisPlayer, int stageOfVote, int person);//возвращает номер игрока против которого выступает данный игрок.
    void nightRole(int *relationships, int amountPlayers, QVector<int> *votes, int thisPlayer);//устанавливает номер игрока, которого мафия убивает ночью
    static int nightKillMafia();//возвращает номер игрока, которого собирается убить мафия
};

#endif // MAFIA_H
