#pragma once
#ifndef GAMEFIELD_H
#define GAMEFIELD_H

#include <QList>
#include <QVector>
#include <QTime>
#include <algorithm>
#include <QString>
#include "player.h"
#include "startgame.h"

class GameField
{
    //singleton
private:
    static GameField *Table;//единственный объект данного класса
    GameField(){
        qsrand(QTime::currentTime().msec());
    }
    GameField(const GameField&);
    GameField& operator=(GameField&);
public:
    static GameField* GetInstance();//получить указатель на объект
private:
    QVector<Player *> *players = new QVector<Player *>();//все игроки
    QList<int> mafia;               //мафия
    QList<int> peaceful;            //мирные
    bool doctor = false;            //док
    QVector<int> *speaches;         //номера игроков в дневных обсуждениях
    bool onGame = false;            //работает ли сейчас игра
    int killedOnDay = -1, killedOnNight = -1; // кто был убит днём/ночью
    GameStep *step;                 //шаг игры
    int transportKilled;            //временная переменная для переноса killedOnDay/killedOnNight без присвоения ей значения
public:
    QVector<QString> WhatsNext();   //Вызывает следующий шаг игры
    void PlayGame();                //инициализирует step для начала игры

    void addPlayerToGame(QString name, QString gender, int age, int oratory, int foxy, int stamina);//добавляет нового игрока в игру
    void giveRole();                //получение ролей игроками
    void deletePlayer(int index);   //удаляет игрока с заданным индексом
    QVector<QString>* startGame();  //Начало игры, дача ролей и формирование отношений каждого игрока
    QVector<QString>* dayStart();   //Начало дня, объявляется кто умер и его роль
    QVector<QString>* daySpeach();  //Дневные обвинения, каждый игрок называет того, кому меньше всего доверяет
    QVector<QString>* dayVote();    //Дневное голосование, каждый игрок голосует против другого и выбирается набравший большее число голосов
    QVector<QString>* dayResult();  //Результаты дневного голосования, кто убит и какая у него роль
    QVector<QString>* night();      //Реализуются роли каждого игрока, мафия называет номер убиваемого, доктор - спасаемого
    QVector<QString>* endOfGame();  //Печатает, кто победил, если осталась всего одна команда
    bool isOnGame();                //находится ли сейчас игра в статусе в игре
    QVector<Player *> *returnPlayers();//возвращает всех игроков
    Player *getPlayer(int i);       //возвращаетигрока с заданным номером
    QList<int> getCitizenList();    //возвращает список мирных жителей
    QList<int> getMafiaList();      //возвращает список мафий
    int getDoctor();                //возвращает жив ли доктор
    int getKilledOnNight();         //возвращает номер игрока, убитого ночью
    int getKilledOnDay();           //возвращает номер игрока, убитого днём
};

#endif // GAMEFIELD_H
