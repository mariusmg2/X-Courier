#include "position.h"

QString Position::getPositionAsString() const {
    return QString::number(this->longitude) + " x " + QString::number(this->latitude);
}

int Position::getLongitude() const {
    return this->longitude;
}

int Position::getLatitude() const {
    return this->latitude;
}
