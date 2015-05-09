#-------------------------------------------------
#
# Project created by QtCreator 2015-03-21T16:30:04
#
#-------------------------------------------------

QT       += core gui
QT       += sql
CONFIG   += c++14
QMAKE_CXXFLAGS += -ggdb

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
    confirmationwindow.cpp \
    courierdatabase.cpp \
    statusinfowindow.cpp \
    routewindow.cpp

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
    confirmationwindow.h \
    courierdatabase.h \
    statusinfowindow.h \
    statustype.h \
    routewindow.h

FORMS    += mainwindow.ui \
    packagestatuswindow.ui \
    confirmationwindow.ui \
    statusinfowindow.ui \
    routewindow.ui
