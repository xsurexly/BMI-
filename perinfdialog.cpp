#include "perinfdialog.h"
#include "ui_perinfdialog.h"
#include"logindialog.h"
#include<QDebug>
#include <QMessageBox>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlRecord>
#include <QtSql/QSqlError>
perinfDialog::perinfDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::perinfDialog)
{
    ui->setupUi(this);
    LoginDialog login;
    ui->username->setText(login.usern());
}

perinfDialog::~perinfDialog()
{
    delete ui;
}


void perinfDialog::on_pushButton_clicked()
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

    LoginDialog login;
    QSqlQuery query;
    query.prepare("SELECT * FROM perinf WHERE user = :value");
    query.bindValue(":value", login.usern()); // 替换为实际的查询条件值
    if (!query.exec()) {
        qDebug() << "Query error:" << query.lastError().text();
    } else {
        while (query.next()) {

            double height = query.value(1).toDouble(); // 例子中假设结果是字符串
           int age= query.value(2).toInt();
           double  weight=query.value(3).toDouble();
          QString  gender=query.value(4).toString();
           QString sheight=QString ::number(height);
          QString sage=QString::number(age);
         QString sweight=QString ::number(weight);

          ui->heightte->setText(sheight);
         ui->agete->setText(sage);
          ui->weightte->setText(sweight);
         ui->genderte->setText(gender);
        }
    }
    db.close();
}

