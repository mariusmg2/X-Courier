#ifndef ROUTE_H
#define ROUTE_H

#include <QString>

class Route {
public:
    Route(): source(QString()), destination(QString()) {}
    Route(QString& source, QString destination): source(source), destination(destination) {}
    ~Route() {}
    QString getSource() const;
    QString getDestination() const;
private:
    QString source;
    QString destination;
};

#endif // ROUTE_H
