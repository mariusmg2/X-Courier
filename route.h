#ifndef ROUTE_H
#define ROUTE_H

#include <QString>

/**
 * @brief The Route class
 *
 * This class is used to define a route (one source point, and one destination point).
 *
 * Public methods:
 *  QString getSource() const;
 *  QString getDestination() const;
 */

class Route {
public:
    Route(): source(QString()), destination(QString()), distance(0), pricePerKm(0) {}
    Route(const QString& source, const QString& destination, int distance, int pricePerKm = 2): source(source),
        destination(destination), distance(distance), pricePerKm(pricePerKm) {}
    ~Route() {}
    QString getSource() const;
    QString getDestination() const;
    unsigned int getDistance() const;
    unsigned int getTotalPrice() const;
    unsigned int getTransitTime() const;
private:
    QString source;
    QString destination;
    unsigned int distance;
    unsigned int pricePerKm;
};

#endif // ROUTE_H
