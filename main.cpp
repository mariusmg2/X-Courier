#include "mainwindow.h"
#include "packagestatuswindow.h"
#include "confirmationwindow.h"
#include "center.h"
#include "schedule.h"
#include "route.h"
#include "driver.h"
#include "package.h"
#include "client.h"
#include "position.h"
#include "courierdatabase.h"
#include "statusinfowindow.h"

#include <QApplication>
#include <QSharedPointer>
#include <QString>
#include <iostream>

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);

    // Smart pointer, that when will go out of scope, will release (calling the destructor) the resource.
    QSharedPointer<MainWindow> w(new MainWindow);

    w->show();

    return a.exec();
}
