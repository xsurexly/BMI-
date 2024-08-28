#ifndef PERINFDIALOG_H
#define PERINFDIALOG_H

#include <QDialog>

namespace Ui {
class perinfDialog;
}

class perinfDialog : public QDialog
{
    Q_OBJECT

public:
    explicit perinfDialog(QWidget *parent = nullptr);
    ~perinfDialog();
    void dispaly();


private slots:
    void on_pushButton_clicked();

private:
    Ui::perinfDialog *ui;
};

#endif // PERINFDIALOG_H
