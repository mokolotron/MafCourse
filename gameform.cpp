#include "gameform.h"
#include "ui_gameform.h"
#include <QDebug>

GameForm::GameForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::GameForm)
{
    ui->setupUi(this);

    this->setFixedSize(this->geometry().width(), this->geometry().height());

    heightTab = ui->tableWidget->height();

    ui->tableWidget->setColumnCount(ui->tableWidget->columnCount() + 1);
    ui->tableWidget->setColumnWidth(0, ui->tableWidget->width() - 15);
    ui->tableWidget->setFocusPolicy(Qt::NoFocus);

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
    else {
        ui->tableWidget->item(0,0)->setText(firstStr);
    }
    //add elem to chat
    ui->tableWidget->setRowCount(ui->tableWidget->rowCount() + 1);
    QTableWidgetItem* item = new QTableWidgetItem();
    item->setText("\n\n" + str);
    item->setForeground(Qt::white);
    ui->tableWidget->setItem(ui->tableWidget->rowCount() - 1, 0, item);
    ui->tableWidget->resizeRowsToContents();

    int sum = 0;
    for(int i = 0; i < ui->tableWidget->rowCount(); i++){
        sum += ui->tableWidget->rowHeight(i);
    }
    //add '\n' to make visibility of chat
    QString *a = new QString();
    for(int i = 0; i < (heightTab - sum) / 15; i++)
        *a += "\n";
    //empty space
    if(sum < heightTab)
        ui->tableWidget->item(0,0)->setText(a + ui->tableWidget->item(0,0)->text());
    ui->tableWidget->resizeRowsToContents();
    //scroll to buttom
    ui->tableWidget->scrollToBottom();

    delete a;
}
void GameForm::clearChat(){
    ui->tableWidget->setRowCount(0);
    firstStr = "";
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
