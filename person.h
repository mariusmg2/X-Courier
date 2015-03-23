#ifndef PERSON_H
#define PERSON_H

#include <QString>
#include <QDate>
#include <iostream>

class Person {
public:
    Person(): name(QString()), gender(false), born_date(QDate::currentDate()) {}
    Person(const QString& name, const bool gender, const QDate& born_date): name(name), gender(gender), born_date(born_date) {}
    ~Person() {}
    QString getName() const;
    bool getGender() const;
    QString getGenderAsString() const;
    unsigned int getAge() const;
    virtual QString getContact() const = 0;
private:
    QString name;
    bool gender;
    QDate born_date;
};

#endif // PERSON_H
