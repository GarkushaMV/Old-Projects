#-------------------------------------------------
#
# Project created by QtCreator 2015-05-26T06:12:25
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport

TARGET = Runge-Kutta
TEMPLATE = app


SOURCES += main.cpp\
        calculation.cpp \
    qcustomplot.cpp

HEADERS  += calculation.h \
    qcustomplot.h

FORMS    += calculation.ui
