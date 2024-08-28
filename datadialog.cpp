#include "datadialog.h"
#include "ui_datadialog.h"
#include <QDebug>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlRecord>
#include <QtSql/QSqlError>
#include<QMessageBox>
#include<QPainter>
#include<QRandomGenerator>
dataDialog::dataDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::dataDialog)
{
    ui->setupUi(this);
}

dataDialog::~dataDialog()
{
    delete ui;
}

void dataDialog::on_pushButton_clicked()
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
    query.exec("SELECT * FROM datalist");

    ui->dataWidget->clear();
    int numRows = query.size(); // 获取查询结果的行数
    int numCols = query.record().count(); // 获取查询结果的列数

    ui->dataWidget->setRowCount(numRows);
    ui->dataWidget->setColumnCount(numCols);
    QStringList header;
    header << " user " << " weight " << " bmi " ;
    ui->dataWidget->setHorizontalHeaderLabels(header); // 设置表头
    ui->dataWidget->verticalHeader()->setVisible(false); // 隐藏行号

    int row = 0;
    while (query.next()) {
        for (int col = 0; col < numCols; ++col) {
            QString value = query.value(col).toString();
            QTableWidgetItem *item = new QTableWidgetItem(value);
            ui->dataWidget->setItem(row, col, item);
        }
        ++row;
    }

    ui->dataWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->dataWidget->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    for (int row = 0; row < ui->dataWidget->rowCount(); ++row) {
        for (int column = 0; column < ui->dataWidget->columnCount(); ++column) {
            QTableWidgetItem *item = ui->dataWidget->item(row, column);
            if (item) {
                item->setTextAlignment(Qt::AlignCenter);
            }
        }
    }
    db.close();
}

void dataDialog::initChart()
{
    if(m_chart==nullptr)
    {
        m_chart=new QChart();
    }
    if(m_lineseries==nullptr)
    {
        m_lineseries=new QLineSeries();
        m_lineseries->setName("bmi");
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
        m_axisY->setRange(0,30);
        m_axisY->setGridLineVisible(true);
        m_axisY->setTickCount(6);
        m_axisY->setMinorTickCount(5);
    }
    m_chart->addAxis(m_axisX, Qt::AlignBottom);
    m_chart->addAxis(m_axisY,Qt::AlignLeft);

    m_lineseries->attachAxis(m_axisX);
    m_lineseries->attachAxis(m_axisY);

   // m_chart->legend()->hide();

    ui->graphicsView->setChart(m_chart);

    ui->graphicsView->setRenderHint(QPainter::Antialiasing);
}


void dataDialog::on_pushButton_2_clicked()
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

    int arraySize = initialSize;
    int count = 0;
    for(int i=0;i<30;i++)
    {
        doublebmi[i]=0.0;
    }
    query.exec("SELECT bmi FROM datalist");
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
        double bmi = query.value(0).toDouble(); // 获取 double 类型的bmi
        doublebmi[count++] = bmi;             // 将 double 数据存储到数组中
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
        free(doublebmi);
    db.close();
}

