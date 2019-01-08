#ifndef TASKPROCESSOR_H
#define TASKPROCESSOR_H

#include "taskstructure.h"
#include "taskdbconnector.h"
#include "taskprocessor_global.h"
#include <QString>

class TASKPROCESSORSHARED_EXPORT TaskProcessor
{

public:
    TaskProcessor();

    void createTask(TaskStructure* task);
    void updateTask(TaskStructure* task);

private:
    std::unique_ptr<TaskDBConnector> connector;

};

#endif // TASKPROCESSOR_H
