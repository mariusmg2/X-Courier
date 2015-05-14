#ifndef INVOICE
#define INVOICE

#include <QTextDocument>
#include <QtPrintSupport/QPrinter>
#include <QDir>
#include <QDate>
#include <QDebug>
#include <QString>

#include "client.h"
#include "route.h"

class Invoice {
public:
    Invoice() { qDebug() << "Invoice::Invoice()"; }
    ~Invoice() {}
    static void generateInvoice(const Client& sender, const Client& rec, const Route& route,
                                const QString& dir = QString::fromStdString(QDir::homePath().toStdString()));
};

#endif // INVOICE

