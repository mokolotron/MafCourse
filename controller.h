#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <QObject>
#include <QLineEdit>
#include <QLabel>
#include <QGroupBox>
#include <QTimer>
#include <QTableWidget>
#include "gamefield.h"
#include "gameform.h"
#include "playericon.h"

class Controller : public QObject
{
    Q_OBJECT
public:
    explicit Controller(QObject *parent = nullptr);
    void playGame();                                //Начинает игру
    void setLinks(QLineEdit *line, QLabel *label, QTableWidget* tableGame, QTableWidget* tablePlayerStats, QWidget *playersPanel, QLabel *LabelAlive);//установление ссылок на элементы UI
    void refreshTableGame();                        //Обновляет таблицу со статусами игроков
    void refreshTablePlayerStats();                 //Обновляет таблицу с характеристиками игроков
    void refreshAlivePlayers();                     //Обновляет текст с живыми игроками на игровой форме
    void setUItoDefault();                          //Сбрасывает текста в интерфейсе в стандартное состояние
    bool canStartNew();                             //возвращает true, если можно начать новую игру, иначе false
    void refreshPlayerIcons();                      //обновляет иконки игроков в игровом окне, она же их создаёт
private:
    QTableWidget *tablePlayerStats, *tableGame;     //таблицы характеристик игроков, статусов в игре
    QLineEdit *writeChat;                           //строка, которая считывает данные в чат
    QLabel *writeHost;                              //текст, который отображается в качестве текста ведущего
    QWidget *playersPanel;                          //панель, на которой располагаются PlayerIcon
    QLabel *labelAlive;                             //Текст содержащий информацию о живых игроках
    QVector<QString> *strings;                      //массив строк, которые печатаются в чат
    QTimer *timer;                                  //таймер для вызова стадий игры с задержкой
    QVector<PlayerIcon*> icons;                     //массив из иконок игроков для каждого игрока
    bool abilityToStartNew;                         //можно ли начать новую игру
signals:

public slots:
    void printMessages();                           //функция, которая отвечает за получение и отправку сообщений из текущий стадии игры
};

#endif // CONTROLLER_H
