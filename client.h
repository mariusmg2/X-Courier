#ifndef CLIENT_H
#define CLIENT_H

#include <QString>
#include <QDate>
#include "person.h"
#include "package.h"

/**
 * @brief The Client class
 *
 * This class is used for representing one person, it inherits Person base class.
 *
 * Public methods:
 *  Package getPackage() const.
 *  virtual QString getContact() const override.
 */

class Client: public Person {
public:
    Client(): Person(), package(Package()), phone(QString()), email(QString()) {}
    Client(const QString& firstName, const QString& lastName, const QString& phone, const QString& email): Person(firstName, lastName), package(Package()), phone(phone), email(email) {}
    Client(const QString& firstName, QString& lastName, const bool gender, const QDate& born_date,
           const Package& package, const QString& phone, const QString& email):
        Person(firstName, lastName, gender, born_date), package(package), phone(phone), email(email) {}
    ~Client() {}
    Package getPackage() const;
    QString getContact() const override;
    QString getPhone() const;
    QString getEmail() const;
    void setPhone(const QString&);
    void setEmail(const QString&);
    void setPackage(const Package&);
private:
    Package package;
    QString phone;
    QString email;
};

#endif // CLIENT_H
// This file was writed by Cosmin Ghitea.
