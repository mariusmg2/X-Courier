#include "center.h"

QVector<Route> Center::getRoutes() const {
    return this->routes;
} //test

Schedule Center::getSchedule() const {
    return this->timetable;
}

QVector<TransType> Center::getTransportTypes() const {
    return this->transport_types;
}
