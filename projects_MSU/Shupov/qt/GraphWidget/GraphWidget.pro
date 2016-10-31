#-------------------------------------------------
#
# Project created by QtCreator 2016-09-29T06:03:17
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = GraphWidget
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    qpaintwidget.cpp \
    dialog.cpp

HEADERS  += mainwindow.h \
    qpaintwidget.h \
    dialog.h

FORMS    += mainwindow.ui \
    dialog.ui
