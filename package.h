#ifndef PACKAGE_H
#define PACKAGE_H

#include <QString>
#include "pkgtype.h"

/**
 * @brief The Package class
 *
 * This class is used for representing a package, package that will be sent by a *Client*, and delivered by a *Driver*.
 *
 * Public methods:
 *  unsigned int getWeight() const;
 *  unsigned int getCode() const;
 *  QString getStatus() const;
 */

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

