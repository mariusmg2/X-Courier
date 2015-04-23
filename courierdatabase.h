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
    CourierDatabase(const QString& databaseType = "QSQLITE", const QString& databaseName = "database.sqlite3") {
        db = QSqlDatabase::addDatabase(databaseType);
        db.setDatabaseName(databaseName);
        db.open();
    }
    ~CourierDatabase() {
        db.close();
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
