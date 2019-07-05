#ifndef GAMEFORM_H
#define GAMEFORM_H

#include <QWidget>
#include <QTableWidgetItem>
#include <QTableWidget>
#include <QMessageBox>
#include <QString>
#include <QTimer>
#include <QProcess>
#include <QLineEdit>
#include <gamefield.h>

namespace Ui {
class GameForm;
}

class GameForm : public QWidget
{
    Q_OBJECT

public:
    explicit GameForm(QWidget *parent = nullptr);   //создание формы и установление её характеристик
    ~GameForm();
private:
    Ui::GameForm *ui;
    QString firstStr;                               //первая строчка в чате
    QLineEdit *dataChat;                            //поле ввода в чате
    int heightTab;                                  //высота таблицы-чата
public:
    void addToChat(QString str);                    //добавление сообщения в чат
    void clearChat();                               //очистка чата
    QLineEdit *getChat();                           //возвращает поле ввода, указывающее на поступающие в чат сообщения
    QLabel *getLabelHost();                         //возвращает текстовое поле
    QLabel *getLabelAlive();                        //возвращает текстовое поле с живыми игроками
    QWidget *getPlayersPanel();                     //возвращает панель с игроками
private slots:
    void ChangeText(QString);                       //добавление сообщения в чат при изменении QLineEdit
};

#endif // GAMEFORM_H
