#include "center.h"

Route Center::getRoute() const {
    return this->routes;
}

Schedule Center::getSchedule() const {
    return this->timetable;
}

// Will return an QVector
QVector<TransType> Center::getTransportTypes() const {
    return this->transport_types;
}
