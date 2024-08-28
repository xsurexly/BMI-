#include "weightdialog.h"
#include "ui_weightdialog.h"
#include"lineardialog.h"
#include <QDebug>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlRecord>
#include <QtSql/QSqlError>
#include<QMessageBox>
#include<QPainter>

weightDialog::weightDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::weightDialog)
{
    ui->setupUi(this);
}

weightDialog::~weightDialog()
{
    delete ui;
}

void weightDialog::initChart()
{

    if(m_chart==nullptr)
    {
        m_chart=new QChart();
    }
    if(m_lineseries==nullptr)
    {
        m_lineseries=new QLineSeries();
        m_lineseries->setName("weight");
        m_chart->addSeries(m_lineseries);
    }
    if(a_lineseries==nullptr)
    {
        a_lineseries=new QLineSeries();
        a_lineseries->setName("weiaverage");
        m_chart->addSeries(a_lineseries);
    }
    if(m_axisX==nullptr)
    {
        m_axisX=new QValueAxis();
        m_axisX->setRange(0,30);
        m_axisX->setGridLineVisible(true);
        m_axisX->setTickCount(6);
        m_axisX->setMinorTickCount(5);
    }
    if(m_axisY==nullptr)
    {
        m_axisY=new QValueAxis();
        m_axisY->setRange(25,100);
        m_axisY->setGridLineVisible(true);
        m_axisY->setTickCount(10);
        m_axisY->setMinorTickCount(7);
    }
    m_chart->addAxis(m_axisX, Qt::AlignBottom);
    m_chart->addAxis(m_axisY,Qt::AlignLeft);

    m_lineseries->attachAxis(m_axisX);
    m_lineseries->attachAxis(m_axisY);
    a_lineseries->attachAxis(m_axisX);
    a_lineseries->attachAxis(m_axisY);
    // m_chart->legend()->hide();

    ui->graphicsView->setChart(m_chart);

    ui->graphicsView->setRenderHint(QPainter::Antialiasing);
}

void weightDialog::on_pushButton_clicked()
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

    const int initialSize = 100; // 初始数组大小
    double* doublebmi = (double*)malloc(initialSize * sizeof(double));
        double* average = (double*)malloc(initialSize * sizeof(double));
    int arraySize = initialSize;
    int count = 0;
    for(int i=0;i<30;i++)
    {
        doublebmi[i]=0.0;
    }
    query.exec("SELECT weight FROM datalist");
    while (query.next()) {
        if (count >= arraySize) {
            // 动态扩展数组
            arraySize *= 2;
            double* newArray = (double*)realloc(doublebmi, arraySize * sizeof(double));
            if (!newArray) {
                free(doublebmi);
                qDebug() << "Memory reallocation failed";
                return;
            }
            doublebmi = newArray;
        }
        double weight = query.value(0).toDouble(); // 获取 double 类型的bmi
        doublebmi[count++] = weight;             // 将 double 数据存储到数组中
    }
    double sum=0.0;

    for(int i=0;i<30;i++){
        if(doublebmi[i]!=0.0){
            sum=sum+doublebmi[i];
            average[i]=sum/(i+1);
        }
        else{
            break;
        }
    }
    initChart();
    for(int i=0;i<30;i++){
        if(doublebmi[i]!=0.0){
            m_lineseries->append(i,doublebmi[i]);
        }
        else{
            break;
        }
    }
    for(int i=0;i<30;i++){
        if(average[i]!=0.0){
            a_lineseries->append(i,average[i]);
        }
        else{

            break;
        }
    }
    free(doublebmi);
    free(average);
    db.close();
}


void weightDialog::on_pushButton_2_clicked()
{
    this->hide();
    linearDialog linear;
    linear.exec();
    this->exec();
}

