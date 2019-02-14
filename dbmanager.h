#ifndef DBMANAGER_H
#define DBMANAGER_H

#include <QString>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QtDebug>
#include <vector>
#include "graph.h"

class DbManager
{
public:
    DbManager(const QString& path);
    std::vector<QString> getAllAirlineNames();
    std::vector<QString> getAllAirportNames();
    std::vector<int> getDestinationAirports(int id);
    void fillGraph(Graph& graph);
    int getAirportId(QString name);
    bool hasARoute(QString name);
    QString getAirportName(int id);
private:
    QSqlDatabase m_db;
};
#endif // DBMANAGER_H
