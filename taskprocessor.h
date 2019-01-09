#ifndef TASKPROCESSOR_H
#define TASKPROCESSOR_H

#include "taskstructure.h"
#include "taskdbconnector.h"
#include "taskprocessor_global.h"
#include <QString>
#include <QList>


class TASKPROCESSORSHARED_EXPORT TaskProcessor
{

public:
    TaskProcessor();

    void createTask(TaskStructure* task);
    void updateTask(TaskStructure* task);
    QList<TaskStructure*> getAll();

private:
    std::unique_ptr<TaskDBConnector> connector;

    std::map<int, QString> priorities = {
        {0,"Low"},
        {1,"Medium"},
        {2,"High"},
        {3,"Fatal"}
};

};

#endif // TASKPROCESSOR_H
