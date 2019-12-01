#include "gameform.h"
#include "ui_gameform.h"
#include <QDebug>

GameForm::GameForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::GameForm)
{
    ui->setupUi(this);

    this->setFixedSize(this->geometry().width(), this->geometry().height());



    ui->labelAlivePlayers->setText("Мафиози: 0\nГорожане: 0\nДоктор: 0");

    //Для чтения сообщений из основого класса GameField
    dataChat = new QLineEdit(this);
    dataChat->setVisible(false);
    //Перехватываем все изменения текста в невидимой lineEdit в таблицу
    connect(dataChat, SIGNAL(textChanged(QString)), this, SLOT(ChangeText(QString)));

}
QWidget *GameForm::getPlayersPanel(){
    return ui->groupBoxPlayers;
}

GameForm::~GameForm()
{
    delete ui;
}
void GameForm::addToChat(QString str){
    //if first string
    if(firstStr == ""){
        firstStr = "\n\n" + str;
    }

    //add elem to chat

    QTableWidgetItem* item = new QTableWidgetItem();
    item->setText("\n\n" + str);
    item->setForeground(Qt::white);


    int sum = 0;

    //add '\n' to make visibility of chat
    QString *a = new QString();
    for(int i = 0; i < (heightTab - sum) / 15; i++)
        *a += "\n";
    //empty space
    if(sum < heightTab)


    delete a;
}

QLabel* GameForm::getLabelHost(){
    return ui->labelHost;
}
QLabel* GameForm::getLabelAlive(){
    return ui->labelAlivePlayers;
}
QLineEdit *GameForm::getChat(){
    return dataChat;
}
void GameForm::ChangeText(QString str){//произошло ли изменение текста(для отображения его в чате)
    if(!str.isEmpty())
        addToChat(str);//пишем в чат
}
