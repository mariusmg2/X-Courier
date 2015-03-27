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
    return this->totalPrice;
}
