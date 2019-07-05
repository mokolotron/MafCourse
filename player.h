#pragma once
#ifndef PLAYER_H
#define PLAYER_H

#include <QVector>
#include <card.h>
#include <citizen.h>
#include <mafia.h>
#include <doctor.h>

class Player
{
public:
    Player();
    Player(QString name, QString gender, int age, int oratory, int stamina, int foxy);
    ~Player();

private:
    QString name;   //имя
    int age;        //возраст
    QString gender; //пол(м/ж)
    int foxy;       //хитрость
    int oratory;    //красноречие
    int stamina;    //стойкость
    bool alive = true;//жив или нет
    int winGame = 0, allGame = 0;//выиграно игр/всего сыграно игр
    int amountPlayers;//содержит количество игроков в партии
    int *relationships;//содержит отношения ко всем остальным игрокам
    QVector<int> votes;//содержит решения по предыдущему дневному голосованию
public:
    Card *role;     //роль игрока

public:
    void setRole(int i);                            //инициализирует Card игрока
    void setAmount(int amount);                     //устанавливает количество игроков
    void setVotes(QVector<int> votes);              //устанавливает массив голосов прошлого дня
    bool isAlive();                                 //возвращает, жив игрок или нет
    void setAlive(bool newAlive);                   //устанавливает жив игрок или нет
    void formRelationships(int amountPlayers, int numberPlayer);//инициализирует массив отношений, вызывает метод у Card
    QString daySpeach(int *decision, int amountPlayers, int thisPlayer, int killedYesterday); //возвращает строку, которую произносит заданный игрок днём
    int dayVote(int thisPlayer, QVector<int> *allDaySpeaches, int prevDecision); //возвращает номер игрока против которого днём голосует данный
    void nightPlay(int thisPlayer);                                              //вызывает соответствующую функцию у роли
    void decreaseRelation(int playerDie);           //изменяет отношение к заданному игроку
    QString getName();                              //возвращает имя
    QString getGender();                            //возвращает пол
    int getAge();                                   //возвращает возраст
    int getOratory();                               //возвращает красноречие
    int getFoxy();                                  //возвращает хитрость
    int getStamina();                               //возвращает стойкость
    int getRole();                                  //возвращает номер роли игрока
    void getStats(int *win, int *all);              //возвращает выиграно/всего игр
    void increaseAllGames();                        //увеличить количество игр
    void increaseWinGames();                        //увеличить количество выигранных игр
};
#endif // PLAYER_H
