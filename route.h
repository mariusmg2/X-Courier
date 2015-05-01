#ifndef ROUTE_H
#define ROUTE_H

#include <QString>
#include <QDate>

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
    virtual ~Route() {}
    virtual QString getSource() const;
    virtual QString getDestination() const;
    virtual unsigned int getDistance() const;
    virtual unsigned int getTotalPrice() const;
    virtual unsigned int getTransitTime() const;
    virtual QDate getPickUpDate() const;
private:
    QString source;
    QString destination;
    unsigned int distance;
    unsigned int pricePerKm;
};

#endif // ROUTE_H
