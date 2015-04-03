#ifndef PERSON_H
#define PERSON_H

#include <QString>
#include <QDate>
#include <iostream>

/**
 * @brief The Person class
 *
 * This class is abstract (you can't make objects of this type), and is used to represent general Person characteristics.
 *
 * Public methods:
 *  QString getName() const;
 *  bool getGender() const;
 *  QString getGenderAsString() const;
 *  unsigned int getAge() const;
 */

class Person {
public:
    Person(): firstName(QString()), lastName(QString()), gender(false), born_date(QDate::currentDate()) {}
    Person(const QString& firstName, QString& lastName, const bool gender, const QDate& born_date):
        firstName(firstName), lastName(lastName), gender(gender), born_date(born_date) {}
    ~Person() {}
    QString getFullName() const;
    QString getFirstName() const;
    QString getLastName() const;
    bool getGender() const;
    QString getGenderAsString() const;
    unsigned int getAge() const;
    virtual QString getContact() const = 0;
private:
    QString firstName;
    QString lastName;
    bool gender;
    QDate born_date;
};

#endif // PERSON_H
