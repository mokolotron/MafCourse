#include "playericon.h"

int PlayerIcon::distanceX = 10;
int PlayerIcon::distanceY = 10;
int PlayerIcon::max_width = 0;
int PlayerIcon::max_height = 0;

PlayerIcon::PlayerIcon(QWidget *parent, int number, QString name, int role) : QWidget(parent)
{
    if(distanceY + 100 >= max_height)
    {
        QMessageBox::warning(this, "Заголовок","Нету места больше игроков добавить");
        return;
    }
    if(distanceX + 75 >= max_width)
    {
        distanceY += 110;
        distanceX = 10;
    }
    //create common elems
    gb=new QGroupBox(parent);
    gb->setGeometry(distanceX, distanceY, 70, 100);
    gb->setObjectName("NewGB_Lables");
    gb->show();
    gb->setStyleSheet("background-color: green; border: 1px solid green;");

    playerNum = new QLabel(gb);
    playerNum->setObjectName("LabelPL");
    playerNum->setGeometry(5, 70, playerNum->width(), playerNum->height());
    playerNum->setText("Игрок " + QString::number(number + 1));
    playerNum->show();

    playerName = new QLabel(gb);
    playerName->setObjectName("LabelPL");
    playerName->setGeometry(5, 50, playerName->width(), playerName->height());
    playerName->setText(name);
    playerName->show();

    anonimPic = new QLabel(gb);
    anonimPic->setObjectName("LabelImPl");
    anonimPic->setGeometry(10, 5, 50, 50);
    anonimPic->setStyleSheet("border: 1px solid white;");
    if(QFile::exists(":images/unknown.png"))
    {
        QPixmap pixmap(":images/unknown.png");
        anonimPic->setPixmap(pixmap);
        anonimPic->setScaledContents(true);
        anonimPic->setSizePolicy( QSizePolicy::Ignored, QSizePolicy::Ignored );
    }
    else {
        anonimPic->setText("Неизвестно");
    }
    anonimPic->show();

    if(role == 1)
    {
        playerPic = new QLabel(gb);
        playerDeathPic = new QLabel(gb);
        playerPic->setObjectName("LabelCit");
        playerDeathPic->setObjectName("LabelDeathCit");
        playerPic->setGeometry(10, 5, 50, 50);
        playerDeathPic->setGeometry(10, 5, 50, 50);
        if(QFile::exists(":images/citizen.png"))
        {
            QPixmap pixmap1(":images/citizen.png");
            playerPic->setPixmap(pixmap1);
            playerPic->setScaledContents(true);
            playerPic->setSizePolicy( QSizePolicy::Ignored, QSizePolicy::Ignored );
        }
        else {
            playerPic->setText("Горожанин");
        }
        if(QFile::exists(":images/citizenDeath.png"))
        {
            QPixmap pixmap1(":images/citizenDeath.png");
            playerDeathPic->setPixmap(pixmap1);
            playerDeathPic->setScaledContents(true);
            playerDeathPic->setSizePolicy( QSizePolicy::Ignored, QSizePolicy::Ignored );
        }
        else {
            playerDeathPic->setText("Горожанин(мертв)");
        }
    }
    if(role == 2)
    {
        playerPic = new QLabel(gb);
        playerDeathPic = new QLabel(gb);
        playerPic->setObjectName("LabelMaf");
        playerDeathPic->setObjectName("LabelDeathMaf");
        playerPic->setGeometry(10, 5, 50, 50);
        playerDeathPic->setGeometry(10, 5, 50, 50);
        if(QFile::exists(":images/mafia.png"))
        {
            QPixmap pixmap1(":images/mafia.png");
            playerPic->setPixmap(pixmap1);
            playerPic->setScaledContents(true);
            playerPic->setSizePolicy( QSizePolicy::Ignored, QSizePolicy::Ignored );
        }
        else {
            playerPic->setText("Мафия");
        }
        if(QFile::exists(":images/mafiaDeath.png"))
        {
            QPixmap pixmap1(":images/mafiaDeath.png");
            playerDeathPic->setPixmap(pixmap1);
            playerDeathPic->setScaledContents(true);
            playerDeathPic->setSizePolicy( QSizePolicy::Ignored, QSizePolicy::Ignored );
        }
        else {
            playerDeathPic->setText("Мафия(мертв)");
        }
    }
    if(role == 3)
    {
        playerPic = new QLabel(gb);
        playerDeathPic = new QLabel(gb);
        playerPic->setObjectName("LabelDoc");
        playerDeathPic->setObjectName("LabelDeathDoc");
        playerPic->setGeometry(10, 5, 50, 50);
        playerDeathPic->setGeometry(10, 5, 50, 50);
        if(QFile::exists(":images/doctor.png"))
        {
            QPixmap pixmap1(":images/doctor.png");
            playerPic->setPixmap(pixmap1);
            playerPic->setScaledContents(true);
            playerPic->setSizePolicy( QSizePolicy::Ignored, QSizePolicy::Ignored );
        }
        else {
            playerPic->setText("Доктор");
        }
        if(QFile::exists(":images/doctorDeath.png"))
        {
            QPixmap pixmap1(":images/doctorDeath.png");
            playerDeathPic->setPixmap(pixmap1);
            playerDeathPic->setScaledContents(true);
            playerDeathPic->setSizePolicy( QSizePolicy::Ignored, QSizePolicy::Ignored );
        }
        else {
            playerDeathPic->setText("Доктор(мертв)");
        }
    }


    distanceX += 80;
}
PlayerIcon::~PlayerIcon(){
    distanceX = 10;
    distanceY = 10;
    delete gb;
}
void PlayerIcon::showDeath(){
    anonimPic->hide();
    playerDeathPic->show();
}
void PlayerIcon::showWin(){
    anonimPic->hide();
    playerPic->show();
}
