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
        q->exec("CREATE TABLE Tasks(ID INTEGER PRIMARY KEY AUTOINCREMENT, Name VARCHAR(50), Description VARCHAR(100), Prior VARCHAR(10), EndTime VARCHAR(20), Done VARCHAR(1))");

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
    q->exec("SELECT DISTINCT Id, Name, Description, Prior, EndTime, Done "
            "FROM Tasks "
            "ORDER BY Prior DESC;");
    return q;
}

void TaskDBConnector::insert(const QString &szName, const QString &szDescription, const QString &szPrior, const QString &szDeadLineTime, const bool &szDone)
{
    QString done = szDone ? "true" : "false";
    QString queryString = "INSERT INTO Tasks (Name,Description,Prior,EndTime,Done) values('"
            + szName + "', '"
            + szDescription + "', '"
            + szPrior + "', '"
            + szDeadLineTime + "', '"
            + done + "')";
    q->exec(queryString);
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
