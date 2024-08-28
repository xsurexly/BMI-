#include "logindialog.h"
#include "ui_logindialog.h"
#include"registerdialog.h"
#include <QMessageBox>

#include <QDebug>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlRecord>
#include <QtSql/QSqlError>
LoginDialog::LoginDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::LoginDialog)
{
    ui->setupUi(this);
}

LoginDialog::~LoginDialog()
{
    delete ui;
}


QString user;
void LoginDialog::on_loginBtn_clicked()
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("localhost");
    db.setUserName("root");
    db.setPassword("20040702xly");
    db.setDatabaseName("qtconnect");
    db.setPort(3306);
    if(!db.open())
    {
        qDebug()<<"connect database failed";
        return; //退出

    }
    qDebug()<<"connect database ok";
    //登录按钮对应槽函数：登陆成功跳转到主功能界面or管理员界面

        //获取用户名和密码输入框中数据
    QString nameString = ui->usrLineEdit->text().trimmed();
    QString pswdString = ui->pwdLineEdit->text().trimmed();

        //遍历数据库
        int non_flag = 1;//标志数据库中没有该用户信息

        QSqlQuery query(db);
        query.exec("select * from loginuser");//执行sql语句
        bool success = query.exec("SELECT * FROM loginuser");

        if (success) {
            while (query.next()) {
                //获取
                QString uName = query.value(1).toString();
                QString uPwd = query.value(2).toString();
                //QMessageBox::about(this, "显示", "用户名："+uName +"密码"+uPwd);
                //比较
                if (nameString == uName && pswdString == uPwd) {
                    //创建功能主界面并显示
                    user=nameString;
                 accept();
                    this->hide();
                    non_flag = 0;
                    db.close();
                    break;
                }
            }
            if (non_flag) {
                QMessageBox::about(this, "警告", "用户名或密码错误");
            }
        }
        else {
            // 查询执行失败
            QSqlError error = query.lastError();
            QString errorMessage = error.text();
            QMessageBox::about(this, "数据库错误", "查询失败" + errorMessage);
        }



    //if(ui->usrLineEdit->text().trimmed()==tr("admin")&&ui->pwdLineEdit->text().trimmed()==tr("123456")){
        //调用对话框的accept方法，关闭登录对话框
      //  accept();
    //}
    //else{
      //  QMessageBox::warning(this,tr("信息"),tr("用户名或密码错误"),QMessageBox::Yes);
    //}
}

QString LoginDialog::usern(){
    return user;
}

void LoginDialog::on_registerBtn_clicked()
{
    this->hide();
    RegisterDialog regi;
    regi.exec();

}

