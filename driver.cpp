#include "driver.h"

Position Driver::getPosition() const {
    return this->position;
}

QString Driver::getContact() const {
    return "Name: " + this->getFullName() + "\nGender: " + this->getGenderAsString() + "\nPhone: " + this->phone
            + "\nEmail: " + this->email + "\n";
}
