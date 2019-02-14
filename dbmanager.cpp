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
        result.push_back(query.value(nameAirline).toString());
    }

    return result;
}

std::vector<QString> DbManager::getAllAirportNames() {
    QSqlQuery query("select name from Airport order by name");
    int nameAirline = query.record().indexOf("name");
    std::vector<QString> result;

    while (query.next()) {
        result.push_back(query.value(nameAirline).toString());
    }

    return result;
}

void DbManager::fillGraph(Graph& graph) {
    QSqlQuery query{"select airport1, airport2 from route"};

    auto airport1 = query.record().indexOf("airport1");
    auto airport2 = query.record().indexOf("airport2");

    while(query.next()){
        graph.addKante(
                       query.value(airport1).toInt(),
                       query.value(airport2).toInt()
                      );
    }
}

int DbManager::getAirportId(QString name) {
    QSqlQuery query("select * from Airport");
    int idAirline = query.record().indexOf("id");
    auto nameAriline = query.record().indexOf("name");


    int result{-1};

    while (query.next()) {
        if (query.value(nameAriline).toString() == name) {
            result = query.value(idAirline).toInt();
        }

    }

    return result;
}

bool DbManager::hasARoute(int id) {
    bool result{false};
    QSqlQuery query{"select airport1, airport2 from route"};

    auto airport1 = query.record().indexOf("airport1");
    auto airport2 = query.record().indexOf("airport2");

    while(query.next()){
        if (query.value(airport1).toInt() == id ||
                query.value(airport2).toInt() == id) {
            result = true;
        }
    }
    return result;
}

QString DbManager::getAirportName(int id){
    QSqlQuery query("select * from Airport");
    int idAirline = query.record().indexOf("id");
    auto nameAriline = query.record().indexOf("name");


    QString result{""};

    while (query.next()) {
        if (query.value(idAirline).toInt() == id) {
            result = query.value(nameAriline).toString();
        }
    }

    return result;
}
