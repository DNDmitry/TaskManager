#ifndef TASKSTRUCTURE_H
#define TASKSTRUCTURE_H


#include <QDateTime>

class TaskStructure
{
public:
    TaskStructure() = default;
    ~TaskStructure() = default;

    QString id;
    QString name;
    QString description;
    QString deadLine;
    QString priority;
    bool done;
};

#endif // TASKSTRUCTURE_H
