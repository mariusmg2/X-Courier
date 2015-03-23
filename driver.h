#ifndef DRIVER_H
#define DRIVER_H

#include "person.h"
#include "position.h"
#include <QString>

class Driver: public Person {
public:
    Driver(): Person(), position(Position()), email(QString()), phone(QString()) {}
    Driver(QString& name, bool gender, QDate& born_date, Position& position,
           QString& email, QString& phone): Person(name, gender, born_date),
        position(position), email(email), phone(phone) {}
    ~Driver() {}
    Position getPosition() const;
    virtual QString getContact() const override;
private:
    Position position;
    QString email;
    QString phone;
};

#endif // DRIVER_H

