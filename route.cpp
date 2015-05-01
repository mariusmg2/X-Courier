#include "route.h"

QString Route::getSource() const {
    return this->source;
}

QString Route::getDestination() const {
    return this->destination;
}

unsigned int Route::getDistance() const {
    return this->distance;
}

unsigned int Route::getTotalPrice() const {
    return this->distance * this->pricePerKm;
}

unsigned int Route::getTransitTime() const {
    if(this->distance <= 100) {
        return 1;
    }
    else if(this->distance <= 300) {
        return 2;
    }
    else {
        return 3;
    }
}

/**
 * @brief Route::getPickUpDate
 * @return This will return the date when the package will arive at some center, and will need to be picked up.
 */

QDate Route::getPickUpDate() const {
    return QDate::currentDate().addDays(this->getTransitTime());
}

void Route::setSource(const QString& source) {
    this->source = source;
}

void Route::setDestination(const QString& destination) {
    this->destination = destination;
}

void Route::setDistance(int distance) {
    this->distance = distance;
}
