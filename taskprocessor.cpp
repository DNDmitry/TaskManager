#include "taskprocessor.h"


TaskProcessor::TaskProcessor()
{
    connector = std::make_unique<TaskDBConnector>();
}

void TaskProcessor::createTask(TaskStructure* task)
{
    connector->insert(task->name, task->description, task->priority, task->deadLine, false);
}

void TaskProcessor::updateTask(TaskStructure* task)
{
    QString done = task->done ? "true" : "false";
    connector->update(task->id, done);//const QString &szRecordId, const QString &szDone
}


