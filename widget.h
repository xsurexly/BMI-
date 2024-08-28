#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui {
class Widget;
}
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();
    void paintEvent(QPaintEvent *e);

private slots:


    void on_perinfbtn_clicked();



    void on_findbtn_clicked();

    void on_docubtn_clicked();

    void on_BMIbtn_clicked();

    void on_deleteButton_clicked();

    void on_changebtn_clicked();

private:
    Ui::Widget *ui;
};
#endif // WIDGET_H
