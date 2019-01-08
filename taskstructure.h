#ifndef TASKSTRUCTURE_H
#define TASKSTRUCTURE_H


#include <QDateTime>

class TaskStructure
{
public:
    TaskStructure();
    ~TaskStructure();

    QString Id;
    QString name;
    QString description;
    QDateTime deadLine;
    QString Priority;
    bool done;
};

#endif // TASKSTRUCTURE_H
