#include "courierdatabase.h"

bool CourierDatabase::isOpen() const {
    return db.isOpen();
}

QString CourierDatabase::getAbsoluteDatabaseFilePath() const {
    QFileInfo checkFile(db.databaseName());
    return checkFile.absoluteFilePath();
}

QString CourierDatabase::getError() const {
    QSqlQuery query(db);
    return query.lastError().driverText();
}

QVector<QString>& CourierDatabase::getAllDestinations() const {
    QVector<QString> *destinations = new QVector<QString>;

    if(db.isOpen() && db.isValid()) {
        QSqlQuery query(db);
        query.exec("SELECT * FROM destinations");

        while(query.next()) {
            destinations->push_back(query.value(0).toString());
        }
    }
    else {
        destinations->push_back("Database error :(");
    }

    return *destinations;
}
