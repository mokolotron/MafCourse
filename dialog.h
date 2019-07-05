#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QVector>
#include <QString>
#include <QFile>
#include <QTime>
#include <QTextCodec>
#include <gamefield.h>

namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = nullptr); //заполнение полей случайными значениями при открытии формы
    ~Dialog();

private slots:
    void on_pushButtonOK_clicked();             //добавление игрока по нажатию на кнопку

private:
    Ui::Dialog *ui;
    static QVector<QString> *women;             //массив из женских имён, которые считываются их файда
    static QVector<QString> *men;               //массив из мужских имён, которые считываются из файла
};

#endif // DIALOG_H
