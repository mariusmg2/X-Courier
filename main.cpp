#include "mainwindow.h"
#include "center.h"
#include "schedule.h"
#include "route.h"
#include "driver.h"
#include "package.h"
#include "client.h"
#include "position.h"
#include <QApplication>
#include <iostream>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;

    Center center = Center("Timisoara", Route("Timisoara", "Arad"), QVector<TransType>({TransType::fast, TransType::slow, TransType::medium}), Schedule());
    QString foo = "\nDestination is: " + center.getRoute().getDestination() + "\n";

    std::cout << foo.toStdString();

    Route route;
    Schedule schedule;
    Driver driver;
    Package package;
    Client client;
    Position position;

    w.show();

    return a.exec();
}
