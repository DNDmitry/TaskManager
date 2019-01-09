#ifndef TASKDBCONNECTOR_H
#define TASKDBCONNECTOR_H
#include <QtSql/QSql>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlError>
#include <QtSql/QSqlQuery>
#include <QDate>
#include <QDebug>
#include <iostream>
#include <memory>
#include <map>
#include "taskdbconnector_global.h"

class TaskDBConnector
{
public:
    bool connect();
    std::unique_ptr<QSqlDatabase> db;
    std::shared_ptr<QSqlQuery> q;
    TaskDBConnector();
    std::shared_ptr<QSqlQuery> readAll();
    void insert(const QString &szName, const QString &szDescription, const QString &szPrior, const QString &szDeadLineTime, const bool &szDone);
    void update(const QString &szRecordId, const QString &szDone);
    void deleteRow(const QString &szRecordId);
    void disconnect();
    virtual ~TaskDBConnector();

private:
    std::map<QString, int> priorities = {
        {"Low",0},
        {"Medium",1},
        {"High",2},
        {"Fatal",3}
};



};

#endif // TASKDBCONNECTOR_H
