#include "mainwindow.h"
#include "center.h"
#include "schedule.h"
#include "route.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
