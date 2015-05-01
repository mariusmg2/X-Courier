#ifndef PACKAGE_H
#define PACKAGE_H

#include <QString>

#include "pkgtype.h"
#include "statustype.h"

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
    Package(): weight(0), code(0), price(0), status(StatusType::undefined), type(PkgType::undefined) {}
    Package(const unsigned int weight, const unsigned int code, const unsigned int price,
            const StatusType& status, const QString& packageName, const PkgType& type) :
                weight(weight), code(code), price(price), status(status), packageName(packageName), type(type) {}
    virtual ~Package() {}
    virtual unsigned int getWeight() const;
    virtual unsigned int getCode() const;
    virtual QString getStatus() const;
    virtual QString getType() const;
    virtual PkgType getType(bool) const; // This crap cannot be owerloaded (why?) so I just trow one blind bool arg.
    virtual QString getPackageName() const;
    virtual unsigned int getPrice() const;
    virtual void setWeight(int);
    virtual void setCode(int);
    virtual void setStatus(const StatusType);
    virtual void setPackageName(const QString&);
    virtual void setType(const PkgType);
    virtual void setType(const QString&);
    virtual void setPrice(int);
private:
    unsigned int weight;
    unsigned int code;
    unsigned int price;
    StatusType status;
    QString packageName;
    PkgType type;
};

#endif // PACKAGE_H
