#include "route.h"
#include "transtype.h"
#include "schedule.h"
#include <QString>
#include <QVector>

#ifndef CENTER_H
#define CENTER_H

class Center {
public:
    Center(): city(QString()), routes(), transport_types(QVector<TransType>()), timetable() {}
    Center(const QString& city, const Route& routes, const QVector<TransType>& transport_types, const Schedule& timetable):
        city(city), routes(routes), transport_types(transport_types), timetable(timetable) {}
    ~Center() {}
    Route getRoute() const;
    QVector<TransType> getTransportTypes() const;
    Schedule getSchedule() const;
private:
    QString city;
    Route routes;
    QVector<TransType> transport_types;
    Schedule timetable;
};

#endif // CENTER_H
