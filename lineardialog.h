#ifndef LINEARDIALOG_H
#define LINEARDIALOG_H

#include <QDialog>
#include<QtCharts>

QT_CHARTS_USE_NAMESPACE


namespace Ui {
class linearDialog;
}

class linearDialog : public QDialog
{
    Q_OBJECT

public:
    explicit linearDialog(QWidget *parent = nullptr);
    ~linearDialog();
private:
    void initChart();
    void linearRegression(const std::vector<double>& x, const std::vector<double>& y, double& slope, double& intercept);
private:
    Ui::linearDialog *ui;
    QChart * m_chart=nullptr;
    QValueAxis *m_axisX=nullptr;
    QValueAxis *m_axisY=nullptr;
    QLineSeries *m_lineseries=nullptr;
};

#endif // LINEARDIALOG_H
