#include "person.h"

QString Person::getFirstName() const {
    return this->firstName;
}

QString Person::getLastName() const {
    return this->lastName;
}

QString Person::getFullName() const {
    return this->firstName + " " + this->lastName;
}

QString Person::getGenderAsString() const {
    return this->gender ? "M" : "F";
}

bool Person::getGender() const {
    return this->gender;
}

unsigned int Person::getAge() const {
    return (QDate::currentDate().year() - this->born_date.year());
}

void Person::setFirstName(const QString& fname) {
    firstName = fname;
}

void Person::setLastName(const QString& lname) {
    lastName = lname;
}

void Person::setGender(bool gender) {
    this->gender = gender;
}
