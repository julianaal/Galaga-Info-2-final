#-------------------------------------------------
#
# Project created by QtCreator 2018-06-06T02:56:47
#
#-------------------------------------------------

QT       += core gui
QT       += multimedia


greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Entrega
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
        main.cpp \
        principal.cpp \
    alien.cpp \
    bala.cpp \
    menu.cpp \
    multiwidget.cpp \
    nave.cpp \
    nube.cpp \
    registro.cpp \
    records.cpp \
    simplewidget.cpp

HEADERS += \
        principal.h \
    alien.h \
    bala.h \
    menu.h \
    multiwidget.h \
    nave.h \
    nube.h \
    registro.h \
    records.h \
    simplewidget.h

FORMS += \
        principal.ui \
    menu.ui \
    multiwidget.ui \
    registro.ui \
    records.ui \
    simplewidget.ui

RESOURCES += \
    image.qrc
