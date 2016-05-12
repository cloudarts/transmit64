#-------------------------------------------------
#
# Project created by QtCreator 2016-05-12T21:52:18
#
#-------------------------------------------------

QT	+= core gui
QT	+= serialport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = qTransmit64
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp

HEADERS  += mainwindow.h

FORMS    += mainwindow.ui
