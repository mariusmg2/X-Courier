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
    route.cpp \
    client.cpp \
    person.cpp \
    driver.cpp \
    package.cpp \
    position.cpp \
    schedule.cpp \
    packagestatuswindow.cpp \
    confirmationwindow.cpp

HEADERS  += mainwindow.h \
    center.h \
    schedule.h \
    route.h \
    transtype.h \
    person.h \
    driver.h \
    position.h \
    client.h \
    package.h \
    pkgtype.h \
    packagestatuswindow.h \
    confirmationwindow.h

FORMS    += mainwindow.ui \
    packagestatuswindow.ui \
    confirmationwindow.ui
