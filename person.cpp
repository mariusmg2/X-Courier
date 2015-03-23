#include "person.h"

QString Person::getName() const {
    return this->name;
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
