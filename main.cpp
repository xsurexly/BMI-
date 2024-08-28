#include "logindialog.h"
#include "widget.h"


#include <QApplication>
#include <QLocale>
#include <QTranslator>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QTranslator translator;
    const QStringList uiLanguages = QLocale::system().uiLanguages();
    for (const QString &locale : uiLanguages) {
        const QString baseName = "login_" + QLocale(locale).name();
        if (translator.load(":/i18n/" + baseName)) {
            a.installTranslator(&translator);
            break;
        }
    }
    Widget w;
    LoginDialog dlg;
    //点击登录按钮关闭登录对话框
    if(dlg.exec()==QDialog::Accepted){
        w.show();
       return a.exec();
    }
    return a.exec();

}
