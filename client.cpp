#include "client.h"

Package Client::getPackage() const {
    return this->package;
}

QString Client::getContact() const {
    return "Name: " + this->getFullName() + "\nGender: " + this->getGenderAsString() + "\nPhone: " + this->phone + "\n";
}
