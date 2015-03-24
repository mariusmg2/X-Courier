#ifndef CLIENT_H
#define CLIENT_H

#include <QString>
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
    Client(): Person(), package(Package()), phone(QString()) {}
    Client(const QString &name, const bool gender, const QDate &born_date, const Package& package, const QString& phone):
        Person(name, gender, born_date), package(package), phone(phone) {}
    ~Client() {}
    Package getPackage() const;
    virtual QString getContact() const override;
private:
    Package package;
    QString phone;
};

#endif // CLIENT_H
