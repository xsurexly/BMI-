#include "bmidialog.h"
#include "ui_bmidialog.h"
#include"logindialog.h"
#include <QMessageBox>
#include"datadialog.h"
#include <QDebug>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlRecord>
#include <QtSql/QSqlError>
#include"weightdialog.h"




bmiDialog::bmiDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::bmiDialog)
{
    ui->setupUi(this);
}

bmiDialog::~bmiDialog()
{
    delete ui;
}
double bmi;
double weight;
void bmiDialog::on_bmiButton_clicked()
{
    bool okWeight, okHeight;
     weight = ui->weightle->text().toDouble(&okWeight);
    double height = ui->heightle->text().toDouble(&okHeight);
    if (okWeight && okHeight && height > 0) {
         bmi = weight*10000 / (height * height);
        QString bmiText = QString("BMI: %1").arg(bmi, 0, 'f', 2);
        QString category;

        if (bmi < 18.5) {
            category = "您的体重过轻，需要多补充营养喔！";
        } else if (bmi >= 18.5 && bmi < 24.9) {
            category = "您的体重正常，继续保持！";
        } else if (bmi >= 25 && bmi < 29.9) {
            category = "您的体重已经超重，需要多锻炼，健康饮食！！";
        } else {
            category = "您的体重已经满足肥胖症，建议您去医院看一下，听一下医生的建议！！";
        }

        ui->textEdit->setText(bmiText+".\n"+category);
    } else {
        ui->textEdit->setText("Invalid input");
    }
}


void bmiDialog::on_pushButton_clicked()
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("localhost");
    db.setUserName("root");
    db.setPassword("20040702xly");
    db.setDatabaseName("qtconnect");
    db.setPort(3306);
    if(!db.open())
    {
        return; //退出
    }
    QSqlQuery query;
    query.exec("select * from datalist");
    query.prepare("insert into datalist values(?,?,?)");
    LoginDialog login;
    QString user=login.usern();

    query.addBindValue(user);
    query.addBindValue(weight);

    query.addBindValue(bmi);
    if(!query.exec()){//执行增加数据语句

        qDebug()<<"无法插入数据";

        QMessageBox::information(NULL, "增加表数据","增加失败",QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);

    }else{
        QMessageBox::information(NULL, "增加表数据","增加成功",QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
    }
    db.close();
}


void bmiDialog::on_pushButton_2_clicked()
{
    this->hide();
    dataDialog data;
    data.exec();
    this->exec();
}


void bmiDialog::on_pushButton_3_clicked()
{
    this->hide();
    weightDialog weight;
    weight.exec();
    this->exec();
}

