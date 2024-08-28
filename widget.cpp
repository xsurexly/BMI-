#include "widget.h"
#include "ui_widget.h"
#include"logindialog.h"
#include"perinfdialog.h"
#include"bmidialog.h"
#include <QDebug>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlRecord>
#include <QtSql/QSqlError>
#include<QMessageBox>
#include<QPainter>
Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_perinfbtn_clicked()
{
    this->hide();
    perinfDialog perinf;
    perinf.exec();
    this->show();
}

void Widget::paintEvent(QPaintEvent *)
{
    QStyleOption opt;
    opt.init(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}

void Widget::on_findbtn_clicked()
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

    QSqlQuery query;
    query.exec("SELECT * FROM bmidocu");

    ui->docutd->clear();
    int numRows = query.size(); // 获取查询结果的行数
    int numCols = query.record().count(); // 获取查询结果的列数

    ui->docutd->setRowCount(numRows);
    ui->docutd->setColumnCount(numCols);
    QStringList header;
    header << " user " << " 饮食 " << " 增加的卡路里 " << " 运动类型" << "消耗的卡路里 ";
    ui->docutd->setHorizontalHeaderLabels(header); // 设置表头
    ui->docutd->verticalHeader()->setVisible(false); // 隐藏行号

    int row = 0;
    while (query.next()) {
        for (int col = 0; col < numCols; ++col) {
            QString value = query.value(col).toString();
            QTableWidgetItem *item = new QTableWidgetItem(value);
            ui->docutd->setItem(row, col, item);
        }
        ++row;
    }

    ui->docutd->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->docutd->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    for (int row = 0; row < ui->docutd->rowCount(); ++row) {
        for (int column = 0; column < ui->docutd->columnCount(); ++column) {
            QTableWidgetItem *item = ui->docutd->item(row, column);
            if (item) {
                item->setTextAlignment(Qt::AlignCenter);
            }
        }
    }
    db.close();
}


void Widget::on_docubtn_clicked()
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

    QString food=ui->foodlineEdit->text().trimmed();
    QString supenergy=ui->uplineEdit->text().trimmed();
    QString exercise=ui->exerciselineEdit->text().trimmed();
    QString sdown=ui->downlineEdit->text().trimmed();

    int upenergy=supenergy.toInt();
    int down=sdown.toInt();
    QSqlQuery query;
    query.exec("select * from bmidocu");
    query.prepare("insert into bmidocu values(?,?,?,?,?)");
    LoginDialog login;
    QString user=login.usern();
    query.addBindValue(user);
    query.addBindValue(food);
    query.addBindValue(upenergy);

    query.addBindValue(exercise);
    query.addBindValue(down);
    if(!query.exec()){//执行增加数据语句

        qDebug()<<"无法插入数据";

        QMessageBox::information(NULL, "增加表数据","增加失败",QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);

    }else{
        QMessageBox::information(NULL, "增加表数据","增加成功",QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
    }
    ui->foodlineEdit->clear();
    ui->uplineEdit->clear();
    ui->exerciselineEdit->clear();
    ui->downlineEdit->clear();
    db.close();
}


void Widget::on_BMIbtn_clicked()
{
    this->hide();
    bmiDialog bmi;
    bmi.exec();
    this->show();
}


void Widget::on_deleteButton_clicked()
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
    LoginDialog login;
    query.prepare("DELETE FROM bmidocu WHERE user = :id LIMIT 1");
    query.bindValue(":id", login.usern());

    if (!query.exec()) {
        qDebug() << "Error: Unable to execute delete query." << query.lastError().text();
    }
    else{
        QMessageBox::information(NULL, "删除表数据","删除成功",QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
    }
    db.close();
}


void Widget::on_changebtn_clicked()
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
    query.prepare("UPDATE bmidocu SET 饮食 = :newValue WHERE user = :id LIMIT 1");
     QString food=ui->foodlineEdit->text().trimmed();
    query.bindValue(":newValue",food);
     LoginDialog login;
    query.bindValue(":id", login.usern());

    if (!query.exec()) {
        qDebug() << "Error: Unable to execute update query." << query.lastError().text();
    }
    else{
         QMessageBox::information(NULL, "修改表数据","修改成功",QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
    }
    db.close();
}

