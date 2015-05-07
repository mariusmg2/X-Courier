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

float Route::getTotalPriceWithPackage(const Package& pkg) const {
    float temp = this->getTotalPrice();

    temp *= ((float)pkg.getWeight() / 2.0);
    temp *= ((float)pkg.getPrice() / 5.0);

    if(pkg.getType().toLower() == "dangerous") {
        temp *= 2.2;
    }
    else if(pkg.getType().toLower() == "fragile") {
        temp *= 3.3;
    }
    else {
        temp *= 4.4;
    }

    return temp / 10000;
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
