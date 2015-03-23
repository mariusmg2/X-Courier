#include "package.h"

unsigned int Package::getWeight() const {
    return this->weight;
}

unsigned int Package::getCode() const {
    return this->code;
}

QString Package::getStatus() const {
    return this->status;
}
