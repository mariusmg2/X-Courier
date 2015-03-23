#include "driver.h"

Position Driver::getPosition() const {
    return this->position;
}

QString Driver::getContact() const {
    return "Name: " + this->getName() + "\nGender: " + this->getGenderAsString() + "\nPhone: " + this->phone
            + "\nEmail: " + this->email + "\n";
}
