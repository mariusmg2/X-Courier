#include "package.h"

unsigned int Package::getWeight() const {
    return weight;
}

unsigned int Package::getCode() const {
    return code;
}

QString Package::getStatus() const {
    switch(status) {
        case StatusType::inTransit:
            return QString("In Transit");
            break;
        case StatusType::rejected:
            return QString("Rejected");
            break;
        case StatusType::waiting:
            return QString("Waiting to be picked");
            break;
        case StatusType::undefined:
            return QString("Hmm, wut?");
            break;
        default:
            return QString("No info.");
    }
}

QString Package::getType() const{
    switch(type) {
        case PkgType::dangerous:
            return QString("Dangerous");
            break;
        case PkgType::fragile:
            return QString("Fragile");
            break;
        case PkgType::precious:
            return QString("Precious");
            break;
        case PkgType::undefined:
            return QString("Undefined");
            break;
        default:
            return QString("No info.");
    }
}

PkgType Package::getType(bool) const {
    return this->type;
}

QString Package::getPackageName() const {
    return packageName;
}

unsigned int Package::getPrice() const {
    return price;
}

void Package::setWeight(int weight) {
    this->weight = weight;
}

void Package::setCode(int code) {
    this->code = code;
}

void Package::setStatus(const StatusType status) {
    this->status = status;
}

void Package::setPackageName(const QString& name) {
    packageName = name;
}

void Package::setType(const PkgType type) {
    this->type = type;
}

void Package::setType(const QString& type) {
    if(type.toLower() == "dangerous") {
        this->type = PkgType::dangerous;
    }
    else if(type.toLower() == "fragile") {
        this->type = PkgType::fragile;
    }
    else if(type.toLower() == "precious") {
        this->type = PkgType::precious;
    }
    else {
        this->type = PkgType::undefined;
    }
}

void Package::setPrice(int price) {
    this->price = price;
}
