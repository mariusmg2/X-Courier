#ifndef PACKAGE_H
#define PACKAGE_H

#include <QString>
#include "pkgtype.h"

class Package {
public:
    Package(): weight(0), code(0), status(QString()), type(PkgType::undefined) {}
    Package(const unsigned int weight, const unsigned int code, const QString& status, const PkgType& type):
        weight(weight), code(code), status(status), type(type) {}
    ~Package() {}
    unsigned int getWeight() const;
    unsigned int getCode() const;
    QString getStatus() const;
private:
    unsigned int weight;
    unsigned int code;
    QString status;
    PkgType type;
};

#endif // PACKAGE_H

