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
        temp *= 1.2;
    }
    else if(pkg.getType().toLower() == "fragile") {
        temp *= 2.3;
    }
    else {
        temp *= 3.4;
    }

    if(this->getTransportType().toLower() == "fast") {
        temp *= 3;
    }
    else if(this->getTransportType().toLower() == "slow") {
        temp /= 1.5;
    }

    return temp / 10000;
}

unsigned int Route::getTransitTime() const {
    if(this->distance <= 100) {
        return 1;
    }
    else if(this->distance <= 200) {
        return 2;
    }
    else if(this->distance <= 300) {
        return 3;
    }
    else {
        return 4;
    }
}

/**
 * @brief Route::getPickUpDate
 * @return This will return the date when the package will arive at some center, and will need to be picked up.
 */

QDate Route::getPickUpDate() const {
    return QDate::currentDate().addDays(this->getTransitTime());
}

QString Route::getTransportType() const {
    switch(type) {
        case TransType::fast:
            return QString("Fast");
        case TransType::medium:
            return QString("Medium");
        case TransType::slow:
            return QString("Slow");
        case TransType::undefined:
            return QString("Undefined");
        default:
            return QString("No Info.");
    }
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
