#ifndef CLIENT_H
#define CLIENT_H

#include "QString"
#include "person.h"
#include "package.h"

class Client: public Person {
public:
    Client(): Person(), package(Package()), phone(QString()) {}
    Client(QString &name, bool gender, QDate &born_date, Package& package, QString& phone):
        Person(name, gender, born_date), package(package), phone(phone) {}
    ~Client() {}
    Package getPackage() const;
    unsigned int getAge() const;
    virtual QString getContact() const;
private:
    Package package;
    QString phone;
};

#endif // CLIENT_H

