#include "dialog.h"
#include "ui_dialog.h"

QVector<QString>* Dialog::women = new QVector<QString>();
QVector<QString>* Dialog::men = new QVector<QString>();
Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);

    qsrand(QTime::currentTime().msec());

    if(women->size() == 0){//заполняем статические переменные для имён
        QFile fileW(":data/nameWomen.txt");
        QFile fileM(":data/nameMen.txt");
        if(fileW.exists() == false || fileM.exists() == false || fileM.open(QIODevice::ReadOnly) == false || fileW.open(QIODevice::ReadOnly) == false){
            women->push_back("Имя");
            men->push_back("Имя");
        }
        else {
            QTextCodec *codec = QTextCodec::codecForName("cp1251");
            while(!fileW.atEnd())
                women->push_back(codec->toUnicode(fileW.readLine()));
            while(!fileM.atEnd())
                men->push_back(codec->toUnicode(fileM.readLine()));
            fileW.close();
            fileM.close();
            if(women->size() == 0)
                women->push_back("Имя");
        }
    }

    this->setFixedSize(this->size());
    //to do not close these window
    setWindowFlags(Qt::Window | Qt::WindowTitleHint | Qt::CustomizeWindowHint);

    ui->lineEdit->setInputMask("aaaaaaaaa");
    ui->lineEdit_2->setInputMask("00");
    ui->spinBox->setRange(1, 10);
    ui->spinBox_2->setRange(1, 10);
    ui->spinBox_3->setRange(1, 10);

    //Filling filds
    ui->spinBox->setValue(qrand() % 10 + 1);
    ui->spinBox_2->setValue(qrand() % 10 + 1);
    ui->spinBox_3->setValue(qrand() % 10 + 1);
    ui->lineEdit_2->setText(QString::number(qrand() % 60 + 5));
    int gender = qrand() % 2;
    if(gender){
        ui->comboBox->setCurrentIndex(1);
        gender = qrand() % women->size();
        ui->lineEdit->setText(women->at(gender));
    }
    else {
        ui->comboBox->setCurrentIndex(0);
        gender = qrand() % men->size();
        ui->lineEdit->setText(men->at(gender));
    }
}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::on_pushButtonOK_clicked()
{
    if(ui->lineEdit->text() != "" && ui->lineEdit_2->text() != "")
    {
        GameField::GetInstance()->addPlayerToGame(ui->lineEdit->text(), ui->comboBox->currentText(), ui->lineEdit_2->text().toInt(), ui->spinBox->value(), ui->spinBox_3->value(), ui->spinBox_2->value());
        this->close();
    }
}
