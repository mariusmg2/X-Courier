#include <QString>

#ifndef ROUTE_H
#define ROUTE_H

class Route {
private:
    QString source;
    QString destination;
public:
    QString getSource() const;
    QString getDestination() const;
};

#endif // ROUTE_H
