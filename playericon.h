#ifndef PLAYERICON_H
#define PLAYERICON_H

#include <QWidget>
#include <QLabel>
#include <QGroupBox>
#include <QPixmap>
#include <QMessageBox>
#include <QLocale>
#include <QFile>
#include <gameform.h>

class PlayerIcon : public QWidget//виджет иконка игрока
{
    Q_OBJECT
public:
    PlayerIcon(QWidget *parent = nullptr, int number = 1, QString name = "", int role = 1); //создание виджета с заданными параметрами, установление его места
    ~PlayerIcon();
private:
    static int distanceX, distanceY;                //текущее смещение по осям
    QGroupBox *gb;                                  //контейнер, где содержатся все текста  и изображения
    QLabel *playerNum, *playerName, *anonimPic, *playerPic, *playerDeathPic; //номер/имя/картинка неизвестного игрока/ картинка живого игрока, учитывая его роль/картинка мёртвого игрока, учитывая его роль
public:
    static int max_width, max_height;               //максимальная ширина и высота игровой панели
    void showDeath();                               //показать роль игрока с мертвой картинкой
    void showWin();                                 //показать роль игрока с живой картинкой

};

#endif // PLAYERICON_H
