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
