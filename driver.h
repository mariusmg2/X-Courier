#ifndef DRIVER_H
#define DRIVER_H

#include "person.h"
#include "position.h"
#include <QString>

/**
 * @brief The Driver class
 *
 * This class is used for representing a driver person, it inherits Person base class.
 *
 * Methods:
 *  Position getPosition() const;
    virtual QString getContact() const override;
 */

class Driver: public Person {
public:
    Driver(): Person(), position(Position()), email(QString()), phone(QString()) {}
    Driver(const QString& name, const bool gender, const QDate& born_date, const Position& position,
           const QString& email, const QString& phone): Person(name, gender, born_date),
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

