#pragma once
#ifndef DOCTOR_H
#define DOCTOR_H

#include <algorithm>
#include <card.h>
#include <mafia.h>
#include <citizen.h>
#include <player.h>

class Doctor : public Card
{
public:
    Doctor();
    virtual ~Doctor();
    void formRelations(int *relationships, int amountPlayers, int numberPlayer);//формирует отношения к остальным игрокам
    int dayDecision(int *relationships, int amountPlayers, QVector<int>* otherPlayers, int thisPlayer, int stageOfVote, int person);//возвращает номер игрока, против которого настроен персонаж
    void nightRole(int *relationships, int amountPlayers, QVector<int> *votes, int thisPlayer);//устанавливает номер игрока, которого будет лечить
    static int healPlayer();//возвращает номер игрока, которого доктор решил лечить днём
private:
    bool healYourself = true; //1 раз док может хилить себя
    static int healAtNight;//хранит номер игрока, которого лечит доктор
};

#endif // DOCTOR_H
