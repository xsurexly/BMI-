QT       += core gui
QT       +=sql
QT       += charts
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    bmidialog.cpp \
    datadialog.cpp \
    lineardialog.cpp \
    logindialog.cpp \
    main.cpp \
    perinfdialog.cpp \
    registerdialog.cpp \
    weightdialog.cpp \
    widget.cpp

HEADERS += \
    bmidialog.h \
    datadialog.h \
    lineardialog.h \
    logindialog.h \
    perinfdialog.h \
    registerdialog.h \
    weightdialog.h \
    widget.h

FORMS += \
    bmidialog.ui \
    datadialog.ui \
    lineardialog.ui \
    logindialog.ui \
    perinfdialog.ui \
    registerdialog.ui \
    weightdialog.ui \
    widget.ui

TRANSLATIONS += \
    BMIsystem_zh_CN.ts
CONFIG += lrelease
CONFIG += embed_translations

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    image.qrc

DISTFILES += \
    ../../IMage/wr.png
