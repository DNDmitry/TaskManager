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
};

#endif // TASKDBCONNECTOR_H
