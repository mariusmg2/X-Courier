#include "courierdatabase.h"

bool CourierDatabase::isOpen() const {
    return db.isOpen();
}

bool CourierDatabase::isOkToUse() const {
    return db.isOpen() && db.isValid();
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

    if(this->isOkToUse()) {
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

QVector<QString> CourierDatabase::checkStatus(const QString& nameORcode) const {
    QVector<QString> result;

    if(this->isOkToUse()) {
        QSqlQuery query(db);
        query.prepare("SELECT * FROM status WHERE lname = :lname OR code = :code");
        query.bindValue(":lname", nameORcode);
        query.bindValue(":code", nameORcode);
        query.exec();

        if(query.first()) {
            for(int i = 0; i < 15; i++) {
                result.push_back(query.value(i).toString());
            }
        }
        else {
            result.push_back("No such client in database.");
        }
    }
    else {
        result.push_back("Some database error (not oppened, or not valid).");
    }

    return result;
}
