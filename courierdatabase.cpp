#include "courierdatabase.h"

bool CourierDatabase::isOpen() const {
    return db.isOpen();
}

bool CourierDatabase::isOkToUse() const {
    return db.isOpen() && db.isValid();
}

bool CourierDatabase::shippingExist(int code) const {
    if(this->isOkToUse()) {
        QSqlQuery query(db);
        query.prepare("SELECT * FROM status WHERE code = :code");
        query.bindValue(":code", code);
        query.exec();

        if(query.first()) {
            return true;
        }
    }
    return false;
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

QVector<QString> CourierDatabase::getPackageStatus(const QString& nameORcode) const {
    QVector<QString> result;

    if(this->isOkToUse()) {
        QSqlQuery query(db);
        query.prepare("SELECT * FROM status WHERE lname = :lname OR code = :code");
        query.bindValue(":lname", nameORcode.toLower());
        query.bindValue(":code", nameORcode);
        query.exec();

        if(query.first()) {
            for(int i = 0; i < 16; i++) {
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

bool CourierDatabase::insertShippingIntoDatabase(const Client& client, const Client& recipient, const Route& route) {
    if(this->isOkToUse()) {
        if(!this->shippingExist(client.getPackage().getCode())) {
            QSqlQuery query(db);
            query.prepare("INSERT INTO status (fname, lname, email, phone, r_fname, r_lname, r_email, r_phone, sourcepoint, endpoint,"
                          " price, code, name, weight, status, pkgtype, pick_date) VALUES (:fname, :lname, :email, :phone, :r_fname, :r_lname,"
                          " :r_email, :r_phone, :sourcepoint, :endpoint, :price, :code, :name, :weight, :status, :pkgtype, :pick_date)");

            query.bindValue(":fname", client.getFirstName().toLower());
            query.bindValue(":lname", client.getLastName().toLower());
            query.bindValue(":email", client.getEmail().toLower());
            query.bindValue(":phone", client.getPhone());

            query.bindValue(":r_fname", recipient.getFirstName().toLower());
            query.bindValue(":r_lname", recipient.getLastName().toLower());
            query.bindValue(":r_email", recipient.getEmail().toLower());
            query.bindValue(":r_phone", recipient.getPhone());

            query.bindValue(":sourcepoint", route.getSource().toUpper());
            query.bindValue(":endpoint", route.getDestination().toUpper());

            query.bindValue(":price", client.getPackage().getPrice());
            query.bindValue(":code", client.getPackage().getCode());
            query.bindValue(":name", client.getPackage().getPackageName().toLower());
            query.bindValue(":weight", client.getPackage().getWeight());
            query.bindValue(":status", client.getPackage().getStatus());
            query.bindValue(":pkgtype", client.getPackage().getType());
            query.bindValue(":pick_date", route.getPickUpDate().toString("dd.MMM.yyyy"));

            query.exec();
            qDebug() << "Client successfully added in database.";
            return true;
        }
        else {
            qDebug() << "This shipping already exists in DB.";
            return false;
        }
    }
    return false;
}

int CourierDatabase::getShortestRouteDistance(const QString& source, const QString& destination) const {
    if(this->isOkToUse()) {
        QVector<int> temp;

        QSqlQuery query(db);

        query.prepare("SELECT distance FROM routes WHERE startpoint = :startpoint AND endpoint = :endpoint");
        query.bindValue(":startpoint", source);
        query.bindValue(":endpoint", destination);

        query.exec();

       while(query.next()) {
           temp.push_back(query.value(0).toInt());
       }

       int aux = 99999999; // TODO: Fix this shit.

       for(auto i : temp) {
           if(i < aux) {
               aux = i;
           }
       }
       return aux != 99999999 ? aux : 0;
    }
    return 0;
}

int CourierDatabase::getUniqueShippingID() const {
    if(this->isOkToUse()) {
        QSqlQuery query(db);
        int code_id = 0;

        query.prepare("SELECT code FROM status");
        query.exec();

        while(query.next()) {
            code_id++;
        }

        return code_id + 74877; //TODO: This is shit, it will be invalid when deleted some records from DB.
    }
    return 0;
}

void CourierDatabase::updateDatabaseStatus() const {
    if(this->isOkToUse()) {
        QDate currentDate = QDate::currentDate();
        QSqlQuery query(db);

        query.prepare("UPDATE status SET status = :msg WHERE pick_date = :pickdate");
        query.bindValue(":msg", "Waiting");
        query.bindValue(":pickdate", currentDate.toString("dd.MMM.yyyy"));

        query.exec();

        QSqlQuery query2(db);

        query2.prepare("UPDATE status SET status = :msg WHERE pick_date = :pickdate"
                       " OR pick_date = :pickdate2 OR pick_date = :pickdate3"
                       " OR pick_date = :pickdate4 or pick_date = :pickdate5");
        query2.bindValue(":msg", "Returning");
        query2.bindValue(":pickdate", currentDate.addDays(-1).toString("dd.MMM.yyyy"));
        query2.bindValue(":pickdate2", currentDate.addDays(-2).toString("dd.MMM.yyyy"));
        query2.bindValue(":pickdate3", currentDate.addDays(-3).toString("dd.MMM.yyyy"));
        query2.bindValue(":pickdate4", currentDate.addDays(-4).toString("dd.MMM.yyyy"));
        query2.bindValue(":pickdate5", currentDate.addDays(-5).toString("dd.MMM.yyyy"));

        query2.exec();
    }
}
