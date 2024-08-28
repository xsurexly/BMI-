#ifndef DATADIALOG_H
#define DATADIALOG_H

#include <QDialog>
#include<QtCharts>

QT_CHARTS_USE_NAMESPACE

namespace Ui {
class dataDialog;
}

class dataDialog : public QDialog
{
    Q_OBJECT

public:
    explicit dataDialog(QWidget *parent = nullptr);
    ~dataDialog();

private slots:
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();

private:
    void initChart();

private:
    Ui::dataDialog *ui;
    QChart * m_chart=nullptr;
    QValueAxis *m_axisX=nullptr;
     QValueAxis *m_axisY=nullptr;
    QLineSeries *m_lineseries=nullptr;

};

#endif // DATADIALOG_H
