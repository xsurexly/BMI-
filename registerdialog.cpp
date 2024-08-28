#include "registerdialog.h"
#include "ui_registerdialog.h"
#include"logindialog.h"
#include <QMessageBox>

#include <QDebug>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlRecord>
#include <QtSql/QSqlError>
RegisterDialog::RegisterDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::RegisterDialog)
{
    ui->setupUi(this);
}

RegisterDialog::~RegisterDialog()
{
    delete ui;
}

void RegisterDialog::on_pushButton_clicked()
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


    QString namestring=ui->usrLineEdit->text().trimmed();
    QString pwdstring=ui->pwdLineEdit->text().trimmed();
    QSqlQuery query;
    query.exec("select * from loginuser");
    int id=1;
    while(query.next()){
        id=query.value(0).toInt();
    }
    query.prepare("insert into loginuser values(?,?,?)");

    query.addBindValue(id+1);
    query.addBindValue(namestring);

    query.addBindValue(pwdstring);
    if(!query.exec()){//执行增加数据语句

        qDebug()<<"无法插入数据";

        QMessageBox::information(NULL, "增加表数据","增加失败",QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);

    }else{
        QMessageBox::information(NULL, "增加表数据","增加成功",QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
        close();
        LoginDialog login;
        login.exec();
    }
    db.close();
}

