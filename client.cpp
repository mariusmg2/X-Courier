#include "client.h"

Package Client::getPackage() const {
    return this->package;
}

QString Client::getContact() const {
    return "Name: " + this->getFullName() + "\nGender: " + this->getGenderAsString() + "\nPhone: " + this->phone + "\n";
}

QString Client::getPhone() const {
    return phone;
}

QString Client::getEmail() const {
    return email;
}

void Client::setPhone(const QString& phone) {
    this->phone = phone;
}

void Client::setEmail(const QString& email) {
    this->email = email;
}

void Client::setPackage(const Package& package) {
    this->package = package;
}
