#include "dbmanager.h"

DbManager::DbManager(const QString& path)
{
   m_db = QSqlDatabase::addDatabase("QSQLITE");
   m_db.setDatabaseName(path);

   if (!m_db.open()) {
      qDebug() << "Error: connection with database fail";
   } else {
      qDebug() << "Database: connection ok";
   }
}

std::vector<QString> DbManager::getAllAirlineNames() {
    QSqlQuery query("select name from Airline");
    int nameAirline = query.record().indexOf("name");
    std::vector<QString> result;

    while (query.next()) {
        result.push_back(query.value(nameAirline).toString().trimmed());
    }

    return result;
}

std::vector<QString> DbManager::getAllAirportNames() {
    QSqlQuery query("select name from Airport order by name");
    int nameAirline = query.record().indexOf("name");
    std::vector<QString> result;

    while (query.next()) {
        result.push_back(query.value(nameAirline).toString().trimmed());
    }

    return result;
}
