#ifndef BMIDIALOG_H
#define BMIDIALOG_H

#include <QDialog>

namespace Ui {
class bmiDialog;
}

class bmiDialog : public QDialog
{
    Q_OBJECT

public:
    explicit bmiDialog(QWidget *parent = nullptr);
    ~bmiDialog();



private slots:


    void on_bmiButton_clicked();

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

private:
    Ui::bmiDialog *ui;
};

#endif // BMIDIALOG_H
