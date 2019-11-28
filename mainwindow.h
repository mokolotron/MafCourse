#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include <QVector>
#include <playericon.h>
#include <gameform.h>
#include <dialog.h>
#include "gamefield.h"
#include "player.h"
#include "controller.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void addAmountPlayersButton();      //открытие формы Dialog заданное количество раз для создания игроков
    void startGameButtonPush();         //запускает игру в Controllere, открывает GameForm
    void addOnePlayerButtonPush();      //однократное открытие Dialog для создания 1 игрока
    void deletePlayerButtonPush();      //вызывает удаление игрока, выделенного в таблице tableGame
    void on_tableGame_itemSelectionChanged();   //при нажатии вне таблицы, снимает с неё выделение

    void on_buttonOK_clicked();

    void on_buttonOK_pressed();

protected:virtual void mousePressEvent(QMouseEvent *e);

private:
    Ui::MainWindow *ui;
    GameForm *formGame;                 //форма игры
    int amountPlayers = 0;              //количество игроков
    Controller *GameManager;            //игровой контроллер
};

#endif // MAINWINDOW_H
