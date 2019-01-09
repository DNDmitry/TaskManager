#ifndef TASKPROCESSOR_H
#define TASKPROCESSOR_H

#include "taskstructure.h"
#include "taskdbconnector.h"
#include "taskprocessor_global.h"
#include <QString>
#include <QList>
#include <QTimer>


class TASKPROCESSORSHARED_EXPORT TaskProcessor : public QObject
{
    Q_OBJECT

public:
    TaskProcessor();

    void createTask(TaskStructure* task);
    void updateTask(TaskStructure* task);
    QList<TaskStructure*> getAll();

signals:
    void haveToCheckDeadlines();

private:
    std::unique_ptr<TaskDBConnector> connector;

    std::map<int, QString> priorities = {
        {0,"Low"},
        {1,"Medium"},
        {2,"High"},
        {3,"Fatal"}
};
    std::unique_ptr<QTimer> timer;
    void isDeadlinesCheckingNeeded();

};

#endif // TASKPROCESSOR_H
