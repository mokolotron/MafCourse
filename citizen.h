#pragma once
#ifndef CITIZEN_H
#define CITIZEN_H

#include <QVector>
#include <QPair>
#include <card.h>
#include <player.h>

class Citizen: public Card
{
public:
    Citizen();
    virtual ~Citizen();
    void formRelations(int *relationships, int amountPlayers, int numberPlayer);//формирование отношения к другим игрокам
    int dayDecision(int *relationships, int amountPlayers, QVector<int>* otherPlayers, int thisPlayer, int stageOfVote, int person);//возвращение номера игрока, против которого настроен данный игрок
    void nightRole(int *relationships, int amountPlayers, QVector<int> *votes, int thisPlayer);//реализует (для горожанина) сон
};

#endif // CITIZEN_H
