#include "courierdatabase.h"

/**
 * @brief CourierDatabase::isOpen Wrapper method, used for simplify some calls. It will check
 *        if database is open.
 * @return If db is opened true will be returned, otherwise false is returned.
 */

bool CourierDatabase::isOpen() const {
    return db.isOpen();
}

/**
 * @brief CourierDatabase::isOkToUse Wrapper method, used for simplify some calls. It will check
 *        if database is open and is valid.
 * @return If db is opened and valid, true will be returned, otherwise false is returned.
 */

bool CourierDatabase::isOkToUse() const {
    return db.isOpen() && db.isValid();
}

/**
 * @brief CourierDatabase::shippingExist Method that checks if **code** value exists in db as a shipping ID.
 * @param code - Represents shipping code.
 * @return Will return true if shipping with **code** ID exists in DB, otherwise, false will be returned.
 */

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

/**
 * @brief CourierDatabase::getAbsoluteDatabaseFilePath Method that will retrive the URI of database.
 * @return Will return a QString, representing the URI to the actual used database file.
 */

QString CourierDatabase::getAbsoluteDatabaseFilePath() const {
    QFileInfo checkFile(db.databaseName());
    return checkFile.absoluteFilePath();
}

/**
 * @brief CourierDatabase::getError Method that will get the last error from a prev. query applied
 *        to the current database.
 * @return A QString, containing the error message.
 */

QString CourierDatabase::getError() const {
    QSqlQuery query(db);
    return query.lastError().driverText();
}

/**
 * @brief CourierDatabase::getAllDestinations Method used for getting all the route destinations from db.
 * @return Will return a reference to a QVector of QString, representing all the destinations.
 *         OBS: The QVector is dinamically allocated, so it must be deleted by the method caller user,
 *         otherwise memory leak will occur.
 */

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

/**
 * @brief CourierDatabase::getPackageStatus Method used for getting a package status from db.
 * @param nameORcode - Representing the name or the shipping id of a potential client.
 * @return If there is a client with name or code **nameORcode, the method will return
 *         a QVector of QString representing all information, otherwise, only the first element
 *         of QVector will contain a specific message, ("No such client in database.").
 */

QVector<QString> CourierDatabase::getPackageStatus(const QString& nameORcode) const {
    QVector<QString> result;

    if(this->isOkToUse()) {
        QSqlQuery query(db);
        query.prepare("SELECT * FROM status WHERE lname = :lname OR r_lname = :r_lname OR code = :code");
        query.bindValue(":lname", nameORcode.toLower());
        query.bindValue(":r_lname", nameORcode.toLower());
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

/**
 * @brief CourierDatabase::insertShippingIntoDatabase Method used for inserting one shipping into database.
 * @param client - Containing informations acout the person who sends the package.
 * @param recipient - Containing info. about the pers. that will recive the package.
 * @param route - Containing info. about the route that the package will be sent.
 * @return On success (shipping was successfully added into database) true will be returned.
 *         Otherwise (database is not opened, or is corrupt, or any other reasons), false will be returned.
 */

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

            if(query.isActive()) {
                qDebug() << "CourierDatabase::insertShippingIntoDatabase(): Client successfully added in database.";
                query.finish();
                return true;
            }
            qDebug() << "CourierDatabase::insertShippingIntoDatabase(): There was some error: " << query.lastError();
            return false;
        }
        else {
            qDebug() << "CourierDatabase::insertShippingIntoDatabase(): This shipping already exists in DB.";
            return false;
        }
    }
    return false;
}

/**
 * @brief CourierDatabase::getShortestRouteDistance Method used to get the shortest distance between two towns.
 * @param source - Param. that will contain the name of the first town.
 * @param destination - Param. with the name of the second town.
 * @return On success, will return one integer value, representing the shortest distance between this two towns.
 *         Otherwise (database problems) 0 will be returned.
 */

int CourierDatabase::getShortestRouteDistance(const QString& source, const QString& destination) const {
    if(this->isOkToUse()) {
        QVector<int> temp;

        QSqlQuery query(db);

        query.prepare("SELECT distance FROM routes WHERE startpoint = :startpoint AND endpoint = :endpoint");
        query.bindValue(":startpoint", source);
        query.bindValue(":endpoint", destination);

        query.exec();

        if(query.isActive()) {
            qDebug() << "CourierDatabase::getShortestRouteDistance(): Successfully obtained shortest route distance!";
        }
        else {
            qDebug() << "CourierDatabase::getShortestRouteDistance(): OBS: There was a problem...";
            qDebug() << query.lastError();
        }

       while(query.next()) {
           temp.push_back(query.value(0).toInt());
       }

       int aux = std::numeric_limits<qint32>::max();

       for(auto i : temp) {
           if(i < aux) {
               aux = i;
           }
       }
       query.finish();
       return aux != std::numeric_limits<qint32>::max() ? aux : 0;
    }
    return 0;
}

/**
 * @brief CourierDatabase::getUniqueShippingID Used for getting pseudorandom numbers (integers)
 *        that will be used as shipping IDs. Numbers are generated based on number of existing
 *        active shippings.
 * @param startNo, multiplyNo - Param. used for getting bigger numbers.
 * @return Will return one integer, representing a unique shipping ID.
 */

int CourierDatabase::getUniqueShippingID(int startNo, int multiplyNo) const {
    if(this->isOkToUse()) {
        QSqlQuery query(db);
        int code_id = 0;

        query.prepare("SELECT code FROM status");
        query.exec();

        while(query.next()) {
            code_id++;
        }

        int code = code_id + startNo;

        if(!this->shippingExist(code)) {
            return code;
        }
        else {
            return (code * multiplyNo) - multiplyNo;
        }
    }
    return 0;
}

/**
 * @brief CourierDatabase::updateDatabaseStatus
 * This method (with all this system implementation) will work only if the database will
 * be updated once in 10 days.
 * If not, there will remain some records that this method will not delete them.
 * One possible fix: change **pick_date** (the date when the package will arrive at some
 * center) representation with some kinda number, so I can compare more easy.
 */

void CourierDatabase::updateDatabaseStatus() const {
    if(this->isOkToUse()) {
        QDate currentDate = QDate::currentDate();
        QSqlQuery query(db);

        query.prepare("UPDATE status SET status = :msg WHERE pick_date = :pickdate");
        query.bindValue(":msg", "Waiting");
        query.bindValue(":pickdate", currentDate.toString("dd.MMM.yyyy"));

        query.exec();

        QSqlQuery query2(db);

        query2.prepare("UPDATE status SET status = :msg, price = price * 2 WHERE pick_date = :pickdate"
                       " OR pick_date = :pickdate2 OR pick_date = :pickdate3"
                       " OR pick_date = :pickdate4 or pick_date = :pickdate5");
        query2.bindValue(":msg", "Returning");
        query2.bindValue(":pickdate", currentDate.addDays(-3).toString("dd.MMM.yyyy"));
        query2.bindValue(":pickdate2", currentDate.addDays(-4).toString("dd.MMM.yyyy"));
        query2.bindValue(":pickdate3", currentDate.addDays(-5).toString("dd.MMM.yyyy"));
        query2.bindValue(":pickdate4", currentDate.addDays(-6).toString("dd.MMM.yyyy"));
        query2.bindValue(":pickdate5", currentDate.addDays(-7).toString("dd.MMM.yyyy"));

        query2.exec();

        QSqlQuery query3(db);

        query3.prepare("DELETE FROM status WHERE pick_date = :p1 OR pick_date = :p2 OR"
                       " pick_date = :p3 OR pick_date = :p4");
        query3.bindValue(":p1", currentDate.addDays(-8).toString("dd.MMM.yyyy"));
        query3.bindValue(":p2", currentDate.addDays(-9).toString("dd.MMM.yyyy"));
        query3.bindValue(":p3", currentDate.addDays(-10).toString("dd.MMM.yyyy"));
        query3.bindValue(":p4", currentDate.addDays(-11).toString("dd.MMM.yyyy"));

        query3.exec();

        if(query.isActive() && query2.isActive() && query3.isActive()) {
            qDebug() << "CourierDatabase::updateDatabaseStatus(): DB Successfully updated!";
            query.finish();
            query2.finish();
            query3.finish();
        }
        else {
            qDebug() << "CourierDatabase::updateDatabaseStatus(): OBS: There was an error updating DB...";
        }
    }
}

/**
 * @brief CourierDatabase::addRoute Used for inserting routes into database.
 * @param source
 * @param destination
 * @param distance
 * @return Will return true if everything was ok, otherwise (database/query problems), false is returned.
 */

bool CourierDatabase::addRoute(const QString& source, const QString& destination, int distance) {
    if(this->isOkToUse()) {
        QSqlQuery query(db);

        query.prepare("INSERT INTO routes (startpoint, endpoint, distance) VALUES"
                      " (:startpoint, :endpoint, :distance)");

        query.bindValue(":startpoint", source.toUpper());
        query.bindValue(":endpoint", destination.toUpper());
        query.bindValue(":distance", distance);

        query.exec();
        if(query.isActive()) {
            qDebug() << "CourierDatabase::addRoute(): Route " << source.toUpper() << " - " << destination.toUpper() << " successfully added!";
            query.finish();
            return true;
        }
        qDebug() << "CourierDatabase::addRoute(): There was some errors: " << query.lastError();
        return false;
    }
    return false;
}
