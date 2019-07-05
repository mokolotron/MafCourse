#ifndef CARD_H
#define CARD_H

#include <QVector>
#include <QTime>

class Card
{
public:
    Card();
    virtual ~Card() = 0;
    virtual void formRelations(int *relationships, int amountPlayers, int numberPlayer) = 0;//формирование значений relationships к каждому из amountPlayers игрогов для numberPlayer игрока
    virtual int dayDecision(int *relationships, int amountPlayers, QVector<int>* otherPlayers, int thisPlayer, int stageOfVote, int person) = 0;//возвращает номер игрока, против которого настроен thisPlayer
    virtual void nightRole(int *relationships, int amountPlayers, QVector<int> *votes, int thisPlayer) = 0;//реализует действия ночью в зависимости от роли
public:
    static int getrandom(int start, int end);
};

#endif // CARD_H
