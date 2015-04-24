#ifndef COURIERDATABASE
#define COURIERDATABASE

#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QDebug>
#include <QSqlError>
#include <QFileInfo>
#include <QString>
#include <QVector>

class CourierDatabase {
public:
    CourierDatabase(const QString& databaseType = "QSQLITE", const QString& databaseName = "database.sqlite3",
                    const QString& connectionName = "Default X-Courier connection") {
        db = QSqlDatabase::addDatabase(databaseType, connectionName);
        db.setDatabaseName(databaseName);
        db.open();
        qDebug() << "CourierDatabase()";
        qDebug() << "Connection " << db.connectionName() << " has been created.";
    }
    ~CourierDatabase() {
        db.close();
        qDebug() << "~CourierDatabase()";
    }
    bool isOpen() const;
    bool isOkToUse() const;
    QString getAbsoluteDatabaseFilePath() const;
    QString getError() const;
    QVector<QString>& getAllDestinations() const;
    QVector<QString> checkStatus(const QString&) const;

private:
    QSqlDatabase db;
};

#endif // COURIERDATABASE
