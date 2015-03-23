#include "mainwindow.h"
#include "center.h"
#include "schedule.h"
#include "route.h"
#include "driver.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;

    Center center;
    Route route;
    Schedule schedule;
    //Driver driver;

    w.show();

    return a.exec();
}
