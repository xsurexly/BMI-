#ifndef WEIGHTDIALOG_H
#define WEIGHTDIALOG_H

#include <QDialog>
#include<QtCharts>

QT_CHARTS_USE_NAMESPACE

namespace Ui {
class weightDialog;
}


class weightDialog : public QDialog
{
    Q_OBJECT

public:
    explicit weightDialog(QWidget *parent = nullptr);
    ~weightDialog();
     void initChart();
private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::weightDialog *ui;
    QChart * m_chart=nullptr;
    QValueAxis *m_axisX=nullptr;
    QValueAxis *m_axisY=nullptr;
    QLineSeries *m_lineseries=nullptr;
     QLineSeries *a_lineseries=nullptr;
};

#endif // WEIGHTDIALOG_H
