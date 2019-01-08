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
    connector->update(task->id, done);
}

QList<TaskStructure> TaskProcessor::getAll()
{
    QList<TaskStructure> tasks;
    std::shared_ptr<QSqlQuery> q = connector->readAll();
    while(q->next())
    {
        TaskStructure task;
        task.id = q->value(0).toInt();
        task.name = q->value(1).toString();
        task.description = q->value(2).toString();
        task.priority = q->value(3).toString();
        task.deadLine = q->value(4).toString();
        task.done = q->value(5).toBool();

        tasks.push_back(task);
    }
    return tasks;
}


