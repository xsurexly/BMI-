#include "lineardialog.h"
#include "ui_lineardialog.h"
#include <QDebug>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlRecord>
#include <QtSql/QSqlError>
#include<QMessageBox>
#include<QPainter>
#include<QRandomGenerator>
#include <iostream>
#include <vector>

linearDialog::linearDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::linearDialog)
{
    ui->setupUi(this);
    initChart();
}

linearDialog::~linearDialog()
{
    delete ui;
}



void linearDialog::linearRegression(const std::vector<double> &x, const std::vector<double> &y, double &slope, double &intercept)
{
    size_t n = x.size();
    if (n != y.size() || n == 0) return;

    double x_sum = std::accumulate(x.begin(), x.end(), 0.0);
    double y_sum = std::accumulate(y.begin(), y.end(), 0.0);
    double xy_sum = std::inner_product(x.begin(), x.end(), y.begin(), 0.0);
    double x_squared_sum = std::inner_product(x.begin(), x.end(), x.begin(), 0.0);

    slope = (n * xy_sum - x_sum * y_sum) / (n * x_squared_sum - x_sum * x_sum);
    intercept = (y_sum - slope * x_sum) / n;
}


void linearDialog::initChart()
{
    if(m_chart==nullptr)
    {
        m_chart=new QChart();
    }
    if(m_lineseries==nullptr)
    {
        m_lineseries=new QLineSeries();
        m_lineseries->setName("Linear Regression");
        m_chart->addSeries(m_lineseries);
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

    // m_chart->legend()->hide();

    ui->graphicsView->setChart(m_chart);

    ui->graphicsView->setRenderHint(QPainter::Antialiasing);

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
     std::vector<double> y;
    for(int i=0;i<30;i++){
        if(doublebmi[i]!=0.0){
            y.push_back(doublebmi[i]);
        }
        else{
            break;
        }
    }
     std::vector<double> x;
    for(int i=0;i<count;i++){
         x.push_back(i);
    }
    double slope, intercept;
    linearRegression(x, y, slope, intercept);
    for(int i=0;i<=30;i++){
        m_lineseries->append(i,slope * i + intercept);
    }
}






