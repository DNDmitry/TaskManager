#include "taskprocessor.h"


TaskProcessor::TaskProcessor()
{
    connector = std::make_unique<TaskDBConnector>();

    timer = std::make_unique<QTimer>(this);
    connect(timer.get(), &QTimer::timeout, this, &TaskProcessor::isDeadlinesCheckingNeeded);
    timer->start(5000); //provides a change QTime readings over time (second)
}

void TaskProcessor::isDeadlinesCheckingNeeded()
{
    emit haveToCheckDeadlines();
}

void TaskProcessor::createTask(TaskStructure* task)
{
    connector->insert(task->name, task->description, task->priority, task->deadLine, false);
}

void TaskProcessor::updateTask(TaskStructure* task)
{
    QString done = task->done ? "true" : "false";
    qDebug() << done;
    connector->update(task->id, done);
}

QList<TaskStructure*> TaskProcessor::getAll()
{
    QList<TaskStructure*> tasks;
    std::shared_ptr<QSqlQuery> q = connector->readAll();
    while(q->next())
    {
        TaskStructure *task = new TaskStructure();

        task->id = q->value(0).toString();
        task->name = q->value(1).toString();
        task->description = q->value(2).toString();
        task->priority = priorities.find(q->value(3).toInt())->second;
        task->deadLine = q->value(4).toString();
        task->done = q->value(5).toBool();
        qDebug() << task->done;
        if(q->value(5).toBool())
            tasks.push_back(task);
        else
            tasks.push_front(task);
    }
    return tasks;
}


