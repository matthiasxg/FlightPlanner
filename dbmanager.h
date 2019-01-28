#ifndef DBMANAGER_H
#define DBMANAGER_H

#include <QString>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QtDebug>
#include <vector>

class DbManager
{
public:
    DbManager(const QString& path);
    std::vector<QString> getAllAirlineNames();
    std::vector<QString> getAllAirportNames();
private:
    QSqlDatabase m_db;
};
#endif // DBMANAGER_H
