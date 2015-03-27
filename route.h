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
    Route(): source(QString()), destination(QString()) {}
    Route(const QString& source, const QString destination): source(source), destination(destination) {}
    ~Route() {}
    QString getSource() const;
    QString getDestination() const;
    unsigned int getDistance() const;
private:
    QString source;
    QString destination;
    unsigned int distance;
};

#endif // ROUTE_H
