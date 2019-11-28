#include "gamefield.h"
#include <QDebug>

GameField* GameField::Table = nullptr;

GameField* GameField::GetInstance(){
    if (!Table)
        Table = new GameField();
    return Table;
}

void GameField::PlayGame(){
    step = new StartGame();
}
QVector<QString> GameField::WhatsNext(){//какой следующий шаг в игре
    if(step == nullptr)
        return QVector<QString>();
    qDebug() << typeid(*step).name();
    QVector<QString> strings = step->doWork();
    step->nextStage(step);
    return strings;
}

void GameField::addPlayerToGame(QString name, QString gender, int age, int oratory, int foxy, int stamina){
    players->push_back(new Player(name, gender, age, oratory, stamina, foxy));
}
void GameField::deletePlayer(int index){//удаление игрока по индексу
    int *size = new int();
    *size = players->size();
    for(int i = 0; i < *size; i++)
        players->at(i)->setAmount(*size - 1);
    players->remove(index);
}

void GameField::giveRole(){//дать роли игрокам
    if(players->size() > 0)
    {
        doctor = false;
        mafia.clear();
        peaceful.clear();
        int amountMafia = players->size() / 3;
        int amountPlayers = players->size();
        for(int i = 0; i < amountPlayers; i++)
        {
            players->at(i)->setAlive(true);
            if(players->at(i)->role != nullptr)
            {
                delete players->at(i)->role;
                players->at(i)->role = nullptr;
            }
        }


        //create list of mafia
        for (int i = 0; i < amountMafia; i++)
        {
            int mafia_curr;
            do{
                mafia_curr = qrand() % amountPlayers;
            } while (mafia.contains(mafia_curr));
            mafia.push_back(mafia_curr);
        }
        std::sort(mafia.begin(), mafia.end());

        //add doctor
        int doc = -1;
        if(amountPlayers > 5)
        {
            do{
                doc = qrand() % amountPlayers;
            } while (mafia.contains(doc));
        }

        //create players
        for (int i = 0; i < amountPlayers; i++)
        {
            if (mafia.contains(i) == false)
            {
                peaceful.push_back(i);
                if(i != doc)
                    players->at(i)->setRole(1);
                else
                {
                    doctor = true;
                    players->at(i)->setRole(3);
                }
            }
            else
            {
                players->at(i)->setRole(2);
            }
        }
    }
}
QVector<QString> *GameField::startGame(){//начать игру
    QVector<QString> *strings = new QVector<QString>();
    giveRole();
    int amountPlayers = players->size();
    for(int i = 0; i < amountPlayers; i++)
        players->value(i)->formRelationships(amountPlayers, i);
    //day n.1 is coming
   onGame = true;
   strings->push_back("~Добро пожаловать в игру мафия! У вас у всех есть ваши роли, старайтесь их придерживаться.\nА теперь наступает День 1. Пора вам познакомиться :)");
   transportKilled = -1;
   killedOnDay = -1;
   killedOnNight = -1;
   speaches = new QVector<int>(amountPlayers, -1);
   return strings;
}
QVector<QString>* GameField::dayStart(){
    QVector<QString> *strings = new QVector<QString>();
    strings->push_back("_________________________________");
    killedOnNight = transportKilled;
    if(killedOnNight != -1)//Если кто то был убит ночью
    {
        strings->push_back("~День наступил! Игрок " + QString::number(killedOnNight + 1)+ " не проснулся\nНачинается обсуждение");
        int role = players->at(killedOnNight)->getRole();
        if(role == 1)
            strings->push_back("\nНаступил день, мафия убила Игрока " + QString::number(killedOnNight + 1) +"(Горожанин)");
        if(role == 2)
            strings->push_back("\nНаступил день, мафия убила Игрока " + QString::number(killedOnNight + 1) +"(Мафия)");
        if(role == 3)
        {
            doctor = false;
            strings->push_back("\nНаступил день, мафия убила Игрока " + QString::number(killedOnNight + 1) +"(Доктор)");
        }
    }
    else {

        strings->push_back("~День наступил! Все проснулись.\nНачинается обсуждение.");
        strings->push_back("\nНаступил день.");
    }
    return strings;
}
QVector<QString> *GameField::daySpeach(){
    QVector<QString> *strings = new QVector<QString>();
    int amountPlayers = players->size();
    speaches->fill(-1);

    int *decision = new int();
    for(int i = 0; i < amountPlayers; i++)
        if(players->at(i)->isAlive())
        {
            strings->push_back("Игрок " + QString::number(i + 1) + ":  " + players->at(i)->daySpeach(decision, amountPlayers, i, killedOnDay));
            int *data = speaches->data();
            data[i] = *decision;//против какого игрока высказана речь
        }
    return strings;
}
QVector<QString> *GameField::dayVote(){
    QVector<QString> *strings = new QVector<QString>();
    int amountPlayers = players->size();
    strings->push_back("~Хватит болтать! Пора голосовать.\nНачинается дневное голосование");
    strings->push_back("Началось дневное голосование:");
    QVector<int> votes(amountPlayers, -1);//результаты голосования

    int *data = speaches->data();
    for(int i = 0; i < amountPlayers; i++)
    {
        if(!mafia.contains(i))
            if(players->at(i)->isAlive())
                votes[i] = players->at(i)->dayVote(i, speaches, data[i]);
    }
    for(int i = 0; i < mafia.size(); i++)
        if(players->at(mafia.at(i))->isAlive())
        {
            votes[mafia.at(i)] = players->at(mafia.at(i))->dayVote(mafia.at(i), &votes, data[mafia.at(i)]);
        }
    for(int i = 0; i < amountPlayers; i++){
        if(players->at(i)->isAlive())
        {
            strings->push_back("Игрок " + QString::number(i + 1) + " против Игрок " + QString::number(votes.at(i) + 1));
        }
    }
    QVector<int> amountVotes(amountPlayers, 0);
    int max = 0;
    for(int i = 0; i < amountPlayers; i++)
        if(players->at(i)->isAlive())
            amountVotes[votes[i]] += 1;
    for(int i = 0; i < amountPlayers; i++)
        if(max < amountVotes[i])
            max = amountVotes[i];
    QVector<int> *sameValues = new QVector<int>();
    for(int i = 0; i < amountPlayers; i++)
        if(max == amountVotes[i])
            sameValues->push_back(i);

    int killedPlayer = sameValues->at(qrand() % sameValues->size());
    transportKilled = killedPlayer;
    //все игроки запоминают результаты голосования
    for(int i = 0; i < amountPlayers; i++)
        players->at(i)->setVotes(votes);
    return strings;
}
QVector<QString> *GameField::dayResult(){
    QVector<QString> *strings = new QVector<QString>();
    int amountPlayers = players->size();
    killedOnDay = transportKilled;
    strings->push_back("Игрок " + QString::number(killedOnDay + 1) + " был убит голосованием");
    int roleKilled = players->at(killedOnDay)->getRole();
    if(roleKilled == 2)
        mafia.removeOne(killedOnDay);
    else
        peaceful.removeOne(killedOnDay);
    if(roleKilled == 2)
    {
        strings->push_back("~Был убит Игрок " + QString::number(killedOnDay + 1) + " (Мафия)");
        strings->push_back("Убитый был Мафией");
    }
    if(roleKilled == 1)
    {
       strings->push_back("~Был убит Игрок " + QString::number(killedOnDay + 1) + " (Горожанин)");
       strings->push_back("Убитый был Горожанин");
    }
    if(roleKilled == 3)
    {
        strings->push_back("~Был убит Игрок " + QString::number(killedOnDay + 1) + " (Доктор)");
        strings->push_back("Убитый был Доктор");
        doctor = false;
    }

    //изменяем параметры убитого игрока и изменяем отношения к нему у всех
    players->at(killedOnDay)->setAlive(false);
    for(int i = 0; i < amountPlayers; i++)
        players->at(i)->decreaseRelation(killedOnDay);
    if(peaceful.size() == 0 || mafia.size() == 0)
        onGame = false;
    return strings;
}
QVector<QString> *GameField::night(){
    QVector<QString> *strings = new QVector<QString>();
    strings->push_back("~Ночь пришла. Горожане уснули. Мафия вышла на охоту");
    strings->push_back("Наступила ночь");

    int amountPlayers = players->size();
    for(int i = 0; i < amountPlayers; i++)
        if(players->at(i)->isAlive())
            players->at(i)->nightPlay(i);
    int smert = Mafia::nightKillMafia();


    strings->push_back("Мафия сделала свой выбор. (Игрок " + QString::number(smert + 1) + ").");
    if(doctor)
    {
        strings->push_back("Доктор в ответ вылечил игрока, но какого? (Игрок " + QString::number(Doctor::healPlayer() + 1) + ")");
        if(Doctor::healPlayer() == smert)//доктор угадал
            smert = -1;
        if(smert != -1)//Если не промахнулась мафия
        {
            players->at(smert)->setAlive(false);

            for(int i = 0; i < amountPlayers; i++)
                players->at(i)->decreaseRelation(smert);
            transportKilled = smert;
            peaceful.removeOne(smert);//извлекаем из списка мирных
        }
        else {
            transportKilled = -1;
            strings->push_back("Доктор вылечил этого же игрока! Никто не умер");
        }
    }
    else {
        players->at(smert)->setAlive(false);

        for(int i = 0; i < amountPlayers; i++)
            players->at(i)->decreaseRelation(smert);
        transportKilled = smert;
        peaceful.removeOne(smert);//извлекаем из списка мирных
    }
    if(peaceful.size() == 0 || mafia.size() == 0)
        onGame = false;
    return strings;
}
QVector<QString> *GameField::endOfGame(){
    QVector<QString> *strings = new QVector<QString>();
    killedOnNight = transportKilled;
    int amountPlayers = players->size();
    for(int i = 0; i < amountPlayers; i++)
        players->at(i)->increaseAllGames();
    if(mafia.size() == 0)
    {
        strings->push_back("~Мафия повержена! Мирные победили. Поздравляем :)");
        strings->push_back("Все мафии были раскрыты. Победа мирных");
        for(int i = 0; i < amountPlayers; i++)
            if(players->at(i)->getRole() != 2)
                players->at(i)->increaseWinGames();
    }
    if(peaceful.size() == 0)
    {
        strings->push_back("~Все мирные были убиты! Мафия торжествует :)");
        strings->push_back("Все горожане убиты. Победа мафиози");
        for(int i = 0; i < amountPlayers; i++)
             if(players->at(i)->getRole() == 2)
                 players->at(i)->increaseWinGames();
    }

    return strings;
}
bool GameField::isOnGame(){
    return onGame;
}

QList<int> GameField::getCitizenList(){
    return peaceful;
}
QList<int> GameField::getMafiaList(){//возвращает всю мафию
        return mafia;
}
int GameField::getDoctor(){
    return doctor;
}
QVector<Player *> *GameField::returnPlayers(){//вернуть список всех игроков
    return players;
}
Player *GameField::getPlayer(int i)
{
    return players->value(i);
}

int GameField::getKilledOnNight(){//кто был убит ночью
    return killedOnNight;
}
int GameField::getKilledOnDay(){//кто был днём убит
    return killedOnDay;
}
