#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QGroupBox>
#include <QMessageBox>
#include <QLabel>
#include <QTime>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setFixedSize(this->geometry().width(), this->geometry().height());

    //build table of players
    ui->tablePlayersStats->setRowCount(7);
    QStringList listHeaders;
    listHeaders << "Игрок" << "Имя" << "Пол" << "Возраст" << "Красноречие" << "Стойкость" << "Хитрость";
    ui->tablePlayersStats->setVerticalHeaderLabels(listHeaders);

    //Оформляем таблицу для игры
    ui->tableGame->setColumnWidth(0, 120);
    ui->tableGame->setColumnWidth(1, 70);
    ui->tableGame->setColumnWidth(2, 30);
    ui->tableGame->setColumnWidth(3, 75);

    //кнопка удаления игрока
    formGame = new  GameForm();
    formGame->setParent(this, Qt::Window);

    //инициализация слотов для кнопок и кнопок
    ui->pushButton_3->setEnabled(false);
    connect(ui->buttonOK, SIGNAL(clicked()), this, SLOT(addAmountPlayersButton()));
    connect(ui->pushButton, SIGNAL(clicked()), this, SLOT(startGameButtonPush()));
    connect(ui->pushButton_2, SIGNAL(clicked()), this, SLOT(addOnePlayerButtonPush()));
    connect(ui->pushButton_3, SIGNAL(clicked()), this, SLOT(deletePlayerButtonPush()));

    //создание контроллера и передача ему параметров
    GameManager = new Controller();
    GameManager->setLinks(formGame->getChat(), formGame->getLabelHost(), ui->tableGame, ui->tablePlayersStats, formGame->getPlayersPanel(), formGame->getLabelAlive());
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::addAmountPlayersButton()
{
    if(GameManager->canStartNew())
    {
        if(GameField::GetInstance()->returnPlayers()->size() > 0)
        {
            QMessageBox::StandardButton reply = QMessageBox::question(this, "Предупреждение!" , "Старые игроки удалятся", QMessageBox::Yes|QMessageBox::No);
            if(reply == QMessageBox::No)
                return;
        }
        int amount = ui->lineEdit->text().toInt();
        // wrong amount of players
        if(amount < 3 || amount > 18)
        {
            QMessageBox::warning(this, "Предупреждение", "Игроков может быть 3-18!");
            return;
        }

        for(int i = amountPlayers - 1; i >= 0; i--)
            GameField::GetInstance()->deletePlayer(i);

        //open the form amount-time
        for(int i = 0; i < amount; i++)
        {
            Dialog *addPlayers = new Dialog(this);
            //нельзя было обратиться к главной, пока открыта эта форма
            addPlayers->setModal(true);
            addPlayers->exec();
            delete addPlayers;
        }
        amountPlayers = amount;
        ui->lineEdit->clear();
        GameManager->refreshTablePlayerStats();
        GameManager->refreshTableGame();
    }
    else {
        QMessageBox::warning(this, "Аккуратнее", "Игра уже идёт, нельзя в процессе изменять игроков!");
    }
}
void MainWindow::startGameButtonPush()//запуск формы с игрой
{
    if(GameManager->canStartNew())
    {
        if(amountPlayers > 2 && amountPlayers < 19)
        {
                formGame->show();

                GameManager->playGame();
        }
        else {
            QMessageBox::warning(this, "Предупреждение", "Невозможно начать игру! Игроков должно быть 3-18");
        }
    }
    else {
        formGame->show();
    }
}
void MainWindow::addOnePlayerButtonPush()//добавление ещё 1 игрока
{
    if(GameManager->canStartNew())
    {
        if(amountPlayers < 18){
            Dialog *addPlayers = new Dialog(this);
            //нельзя было обратиться к главной, пока открыта эта форма
            addPlayers->setModal(true);
            addPlayers->exec();
            delete addPlayers;
            amountPlayers++;
            GameManager->refreshTableGame();
            GameManager->refreshTablePlayerStats();
        }
        else {
            QMessageBox::warning(this, "Предупреждение", "Игроков уже 18!");
        }
    }
    else
        QMessageBox::warning(this, "Аккуратнее", "Игра уже идёт, нельзя в процессе изменять игроков!");
}
void MainWindow::deletePlayerButtonPush()//удаление 1 игрока
{
    if(GameManager->canStartNew())//если игра уже идёт нельзя удалять игроков
    {
       int rowNumber = ui->tableGame->selectedItems().first()->row();
       GameField::GetInstance()->deletePlayer(rowNumber);
       amountPlayers--;
       GameManager->refreshTablePlayerStats();
       GameManager->refreshTableGame();
    }
    else {
        QMessageBox::warning(this, "Аккуратнее", "Игра уже идёт, нельзя в процессе изменять игроков!");
    }
}
//Выбрана ячейка в tableGame или нет
void MainWindow::on_tableGame_itemSelectionChanged()
{
    if(ui->tableGame->selectedItems().count() > 0)
            ui->pushButton_3->setEnabled(true);
    else {
        ui->pushButton_3->setEnabled(false);
    }
}
void MainWindow::mousePressEvent(QMouseEvent *e){
    if(this->rect().contains(e->pos()))
        ui->tableGame->clearSelection();
}
