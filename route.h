#ifndef ROUTE_H
#define ROUTE_H

#include <QString>
#include <QDate>
#include <QDebug>

#include "package.h"
#include "transtype.h"

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
    Route(): source(QString()), destination(QString()), type(TransType::undefined), distance(0), pricePerKm(0) {}
    Route(const QString& source, const QString& destination, TransType type, int distance, int pricePerKm = 2): source(source),
        destination(destination), type(type), distance(distance), pricePerKm(pricePerKm) {}
    virtual ~Route() {}
    virtual QString getSource() const;
    virtual QString getDestination() const;
    virtual unsigned int getDistance() const;
    virtual unsigned int getTotalPrice() const;
    virtual float getTotalPriceWithPackage(const Package&) const;
    virtual unsigned int getTransitTime() const;
    virtual QDate getPickUpDate() const;
    virtual QString getTransportType() const;
    virtual void setSource(const QString&);
    virtual void setDestination(const QString&);
    virtual void setDistance(int);
private:
    QString source;
    QString destination;
    TransType type;
    unsigned int distance;
    unsigned int pricePerKm;
};

#endif // ROUTE_H
