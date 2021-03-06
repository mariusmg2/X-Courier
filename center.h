#ifndef CENTER_H
#define CENTER_H

#include "route.h"
#include "transtype.h"
#include "schedule.h"
#include <QString>
#include <QVector>

/**
 * @brief The Center class
 *
 * This class is used for representing one transport center.
 *
 * Public methods:
 *  QVector<Route> getRoutes() const.
 *  QVector<TransType> getTransportTypes() const.
 *  Schedule getSchedule() const.
 */

class Center {
public:
    Center(): city(QString()), routes(QVector<Route>()), transport_types(QVector<TransType>()), timetable(Schedule()) {}
    Center(const QString& city, const QVector<Route>& routes, const QVector<TransType>& transport_types, const Schedule& timetable):
        city(city), routes(routes), transport_types(transport_types), timetable(timetable) {}
    ~Center() {}
    QVector<Route> getRoutes() const;
    QVector<TransType> getTransportTypes() const;
    Schedule getSchedule() const;
private:
    QString city;
    QVector<Route> routes;
    QVector<TransType> transport_types;
    Schedule timetable;
};

#endif // CENTER_H
