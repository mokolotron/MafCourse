#include "player.h"
#include <QMessageBox>

Player::Player()
{
}
Player::~Player(){
}
Player::Player(QString name, QString gender, int age, int oratory, int stamina, int foxy){//создание игрока
    role = nullptr;
    this->name = name;
    this->age = age;
    this->gender = gender;
    this->foxy = foxy;
    this->oratory = oratory;
    this->stamina = stamina;
}
void Player::setRole(int i){//установление роли от переданного параметра
    if(i == 1)
        role = new Citizen();
    else {
        if(i == 2)
            role = new Mafia();
        else {
            role = new Doctor();
        }
    }
}
bool Player::isAlive(){//жив ли игрок
    return alive;
}
void Player::setAlive(bool newAlive){
    alive = newAlive;
}
void Player::formRelationships(int amountPlayers, int numberPlayer){//сформировать отношения с другими игроками
    relationships = new int[amountPlayers];
    this->amountPlayers = amountPlayers;
    role->formRelations(relationships, amountPlayers, numberPlayer);
}
void Player::decreaseRelation(int playerDie)//изменить отношения к мертвому
{
    relationships[playerDie] = -100000;
}
void Player::increaseAllGames(){
    allGame++;
}
void Player::increaseWinGames(){
    winGame++;
}

QString Player::daySpeach(int *decision, int amountPlayers, int thisPlayer, int killedYesterday){//Какого игрока обвинит в обсуждении
    *decision = role->dayDecision(relationships, amountPlayers, &votes, thisPlayer, 1, killedYesterday);
    if(oratory < 3)
        return "Хмм.. Я обвиню Игрока " + QString::number(*decision + 1);
    else {
        if(oratory < 5)
            return "Я считаю, что Игрок " + QString::number(*decision + 1) + " - мафия";
        else {
            if(oratory < 8)
                return "Определённо, он ведёт себя подозрительно. Скорее всего он мафия, Игрок " + QString::number(*decision + 1);
            else {
                return "Только посмотрите на него! Игрок " + QString::number(*decision + 1) + " ведёт себя точно как мафия! Посадим его!";
            }
        }
    }
}
int Player::dayVote(int thisPlayer, QVector<int> *allDaySpeaches, int prevDecision){//дневное голосование
    return role->dayDecision(relationships, allDaySpeaches->size(), allDaySpeaches, thisPlayer, 2, prevDecision);
}
void Player::nightPlay(int thisPlayer){
    role->nightRole(relationships, amountPlayers, &votes, thisPlayer);
}

QString Player::getName(){
    return name;
}
QString Player::getGender(){
    return gender;
}
int Player::getAge(){
    return age;
}
int Player::getOratory(){
    return oratory;
}
int Player::getFoxy(){
    return foxy;
}
int Player::getStamina(){
    return stamina;
}
int Player::getRole(){

    if (role == nullptr)
    {
        return -1;
    }
    if(strcmp(typeid (*role).name(), "7Citizen") == 0)
        return 1;
    if(strcmp(typeid (*role).name(), "5Mafia") == 0)
        return 2;
    if(strcmp(typeid (*role).name(), "6Doctor") == 0)
        return 3;
    else {
        return 0;
    }
}
void Player::getStats(int *win, int *all){
    *win = winGame;
    *all = allGame;
}
void Player::setVotes(QVector<int> votes){
    this->votes = votes;
}
void Player::setAmount(int amount){
    this->amountPlayers = amount;
}
