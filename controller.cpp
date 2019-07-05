#include "controller.h"
#include <QDebug>

Controller::Controller(QObject *parent) : QObject(parent)
{
    timer = new QTimer();
    connect(timer, SIGNAL(timeout()), this, SLOT(printMessages()));
    abilityToStartNew = true;
}
void Controller::playGame(){

    GameField::GetInstance()->PlayGame();
    setUItoDefault();
    for(int i = 0; i < icons.size(); i++)
        delete icons[i];
    icons.clear();
    abilityToStartNew = false;
    timer->start(3000);
}
void Controller::setLinks(QLineEdit *line, QLabel *label, QTableWidget* tableGame, QTableWidget* tablePlayerStats, QWidget *playersPanel, QLabel *labelAlive){
    this->writeChat = line;
    this->writeHost = label;
    this->tableGame = tableGame;
    this->tablePlayerStats = tablePlayerStats;
    this->playersPanel = playersPanel;
    this->labelAlive = labelAlive;
}
void Controller::printMessages(){
    QVector<QString> strings =  GameField::GetInstance()->WhatsNext();
    refreshAlivePlayers();
    refreshPlayerIcons();
    if(strings.length() == 0)
    {
        abilityToStartNew = true;
        refreshPlayerIcons();
        timer->stop();
    }
    refreshPlayerIcons();
    refreshTableGame();
    for(int i = 0; i < strings.length(); i++)
    {
        if(strings.at(i).data()[0] == '~')
        {
            writeHost->setText(strings.at(i));
        }
        else
        {
            writeChat->setText(strings.at(i));
        }
    }
}

void Controller::refreshPlayerIcons(){
    int amountPlayers = GameField::GetInstance()->returnPlayers()->size();
    if(icons.size() == 0)
    {
        for(int i = 0; i < amountPlayers; i++)
        {
            Player *pl = GameField::GetInstance()->getPlayer(i);
            icons.push_back(new PlayerIcon(playersPanel, i, pl->getName(), pl->getRole()));
        }
    }
    if(abilityToStartNew == false)
    {
        int killedOnDay = GameField::GetInstance()->getKilledOnDay(), killedOnNight = GameField::GetInstance()->getKilledOnNight();
        if(killedOnDay != -1)
            icons.at(killedOnDay)->showDeath();
        if(killedOnNight != -1)
            icons.at(killedOnNight)->showDeath();
    }
    else {
        for(int i = 0; i < amountPlayers; i++)
            if(GameField::GetInstance()->getPlayer(i)->isAlive())
                icons.at(i)->showWin();
    }
}
void Controller::refreshTableGame(){//обновление таблицы состояния в игре
    tableGame->setRowCount(0);
    int amountPlayers = GameField::GetInstance()->returnPlayers()->size();
    for(int i = 0; i < amountPlayers; i++)
    {
        Player *pl = GameField::GetInstance()->getPlayer(i);
        tableGame->setRowCount(tableGame->rowCount() + 1);
        QTableWidgetItem* item = new QTableWidgetItem();
        item->setText("Игрок " + QString::number(i + 1) + " (" + pl->getName() + ")");
        tableGame->setItem(i, 0, item);

        QTableWidgetItem* itemRole = new QTableWidgetItem();
        QString *role = new QString();
        int resRole = pl->getRole();
        if(resRole == -1)
            *role = "Нет";
        if(resRole == 1)
            *role = "Горожанин";
        if(resRole == 2)
            *role = "Мафия";
        if(resRole == 3)
            *role = "Доктор";
        itemRole->setText(*role);
        tableGame->setItem(i, 1, itemRole);
        delete role;

        QTableWidgetItem* itemAlive = new QTableWidgetItem();
        if(pl->isAlive())
            itemAlive->setText("Жив");
        else {
            itemAlive->setText("Мертв");
        }
        tableGame->setItem(i, 2, itemAlive);

        int *win = new int();
        int *all = new int();
        pl->getStats(win, all);
        QTableWidgetItem* itemStatistic = new QTableWidgetItem();
        itemStatistic->setText(QString::number((*win))+ " / " + QString::number((*all)));
        tableGame->setItem(i, 3, itemStatistic);
        delete win;
        delete all;
    }
}
void Controller::refreshTablePlayerStats(){
    tablePlayerStats->setColumnCount(0);
    int amountPlayers = GameField::GetInstance()->returnPlayers()->size();
    //filling the table of characteristic
    for(int i = 0; i < amountPlayers; i++){
        Player *pl = GameField::GetInstance()->getPlayer(i);
        tablePlayerStats->setColumnCount(tablePlayerStats->columnCount() + 1);
        tablePlayerStats->setColumnCount(tablePlayerStats->columnCount() + 1);
        QTableWidgetItem* item = new QTableWidgetItem();
        item->setText("Игрок " + QString::number(i + 1));
        tablePlayerStats->setItem(0, tablePlayerStats->columnCount() - 1, item);

        QTableWidgetItem* itemName = new QTableWidgetItem();
        itemName->setText(pl->getName());
        tablePlayerStats->setItem(1, tablePlayerStats->columnCount() - 1, itemName);

        QTableWidgetItem* itemGender = new QTableWidgetItem();
        itemGender->setText(pl->getGender());
        tablePlayerStats->setItem(2, tablePlayerStats->columnCount() - 1, itemGender);

        QTableWidgetItem* itemAge = new QTableWidgetItem();
        itemAge->setText(QString::number(pl->getAge()));
        tablePlayerStats->setItem(3, tablePlayerStats->columnCount() - 1, itemAge);

        QTableWidgetItem* itemOratory = new QTableWidgetItem();
        itemOratory->setText(QString::number(pl->getOratory()));
        tablePlayerStats->setItem(4, tablePlayerStats->columnCount() - 1, itemOratory);

        QTableWidgetItem* itemFoxy = new QTableWidgetItem();
        itemFoxy->setText(QString::number(pl->getFoxy()));
        tablePlayerStats->setItem(6, tablePlayerStats->columnCount() - 1, itemFoxy);

        QTableWidgetItem* itemStamina = new QTableWidgetItem();
        itemStamina->setText(QString::number(pl->getStamina()));
        tablePlayerStats->setItem(5, tablePlayerStats->columnCount() - 1, itemStamina);

    }
    tablePlayerStats->resizeColumnsToContents();
}
void Controller::refreshAlivePlayers(){
    int doc = GameField::GetInstance()->getDoctor();
    labelAlive->setText("Мафиози: " + QString::number(GameField::GetInstance()->getMafiaList().size()) + "\nГорожане: " + QString::number(GameField::GetInstance()->getCitizenList().size() - doc) + "\nДоктор: " + QString::number(doc));
}
void Controller::setUItoDefault(){
    writeHost->setText("Происходит распределение ролей!");
    labelAlive->setText("Мафиози: 0\nГорожане: 0\nДоктор: 0");
    PlayerIcon::max_width = playersPanel->width();
    PlayerIcon::max_height = playersPanel->height();
    int amountRows = tableGame->rowCount();
    for(int i = 0; i < amountRows; i++)
    {
        tableGame->item(i, 1)->setText("Нет");
        tableGame->item(i, 2)->setText("Жив");
    }
}
bool Controller::canStartNew(){
    return abilityToStartNew;
}
