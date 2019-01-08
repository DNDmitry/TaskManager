#include "taskdbconnector.h"

TaskDBConnector::TaskDBConnector()
{
    connect();
}
bool TaskDBConnector::connect()
{
    db = std::make_unique<QSqlDatabase>(QSqlDatabase::addDatabase("QSQLITE"));
    db->setDatabaseName("TaskDB");
    if(db->open())
    {
        qDebug() << "Im connected!";
        q = std::make_shared<QSqlQuery>(*db);

        q->exec("CREATE DATABASE TaskDB");
        q->exec("USE TaskDB");
        q->exec("CREATE TABLE Tasks(Name VARCHAR(50), Description VARCHAR(100), Prior VARCHAR(10), EndTime VARCHAR(20), Done VARCHAR(1), ID int NOT NULL AUTO_INCREMENT, PRIMARY KEY (ID)");

        return true;
    }
    else
    {
        qDebug() << "Cannot create DB:::";
        return false;
    }
}

std::shared_ptr<QSqlQuery> TaskDBConnector::readAll()
{
    q->exec("SELECT DISTINCT Name, Description, Prior, EndTime, Done "
            "FROM Tasks "
            "ORDER BY Prior DESC;");
    return q;
}

void TaskDBConnector::insert(const QString &szName, const QString &szDescription, const QString &szPrior, const QString &szEndTime, const QString &szDone)
{
    q->exec("INSERT INTO Tasks values('"
            + szName + "', '"
            + szDescription + "', '"
            + szPrior + "', '"
            + szEndTime + "', '"
            + szDone + "')");
}

void TaskDBConnector::update(const QString &szRecordId, const QString &szDone)
{
    q->exec("UPDATE Tasks SET Done = '" + szDone + "' WHERE ID = " + szRecordId + ";");
}

void TaskDBConnector::deleteRow(const QString &szRecordId)
{
    q->exec("DELETE FROM Tasks WHERE ID = '" + szRecordId + "';");
}

void TaskDBConnector::disconnect()
{
    db->close();
    qDebug() << "Im disconnected!";
}

TaskDBConnector::~TaskDBConnector()
{
    disconnect();
}
