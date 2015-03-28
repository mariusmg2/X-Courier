#include "mainwindow.h"
#include "center.h"
#include "schedule.h"
#include "route.h"
#include "driver.h"
#include "package.h"
#include "client.h"
#include "position.h"

#include <QApplication>
#include <QSharedPointer>
#include <QString>
#include <iostream>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QSharedPointer<MainWindow> w(new MainWindow);

    Route route = Route("Timisoara", "Arad", 100);
    Route route2 = Route("Arad", "Caransebes", 320);
    Route route3 = Route("Sebes", "Orsova", 300);
    Route route4("Lugoj", "Bucuresti", 600);

    QVector<Route> routes({route, route2, route3, route4});

    QVector<TransType> transportTypes({TransType::fast, TransType::slow, TransType::medium});

    Center center = Center("Timisoara", routes, transportTypes, Schedule());

    for(auto i : center.getRoutes()) {
        std::cout << ("\nSource is: " + i.getSource() + " destination is: " +
                      i.getDestination() + " Total price: " + QString::number(i.getTotalPrice()) + "\n").toStdString();
    }

    Schedule schedule;
    Driver driver;
    Package package;
    Client client;
    Position position;

    w->show();

    return a.exec();
}
