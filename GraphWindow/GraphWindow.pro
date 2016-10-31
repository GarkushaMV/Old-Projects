#-------------------------------------------------
#
# Project created by QtCreator 2016-09-29T05:04:21
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
                                  QT += opengl

TARGET = GraphWindow
TEMPLATE = app


SOURCES += main.cpp\
        graphwindow.cpp \
    qgraphwidget.cpp

HEADERS  += graphwindow.h \
    qgraphwidget.h

FORMS    += graphwindow.ui
