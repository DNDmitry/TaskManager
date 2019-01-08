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
    QList<TaskStructure> getAll();

private:
    std::unique_ptr<TaskDBConnector> connector;

};

#endif // TASKPROCESSOR_H
