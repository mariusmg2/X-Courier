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
    Person(const QString& firstName, QString& lastName, bool gender, const QDate& born_date):
        firstName(firstName), lastName(lastName), gender(gender), born_date(born_date) {}
    virtual ~Person() {}
    virtual void setFirstName(const QString&);
    virtual void setLastName(const QString&);
    virtual void setGender(bool);
    virtual QString getFullName() const;
    virtual QString getFirstName() const;
    virtual QString getLastName() const;
    virtual bool getGender() const;
    virtual QString getGenderAsString() const;
    virtual unsigned int getAge() const;
    virtual QString getContact() const = 0;
private:
    QString firstName;
    QString lastName;
    bool gender;
    QDate born_date;
};

#endif // PERSON_H
