#-------------------------------------------------
#
# Project created by QtCreator 2015-03-21T16:30:04
#
#-------------------------------------------------

QT       += core gui
CONFIG   += c++14

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = X-Courier
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    center.cpp \
    route.cpp

HEADERS  += mainwindow.h \
    center.h \
    schedule.h \
    route.h \
    transtype.h \
    person.h \
    driver.h

FORMS    += mainwindow.ui
