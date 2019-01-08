#ifndef TASKMANAGERUI_H
#define TASKMANAGERUI_H

#include "newtaskdialog.h"
#include <QWidget>
#include "taskprocessor.h"
#include <memory>
#include <QTableWidgetItem>
#include <QDebug>

namespace Ui {
class TaskManagerUI;
}

class TaskManagerUI : public QWidget
{
    Q_OBJECT

public:
    explicit TaskManagerUI(QWidget *parent = nullptr);
    ~TaskManagerUI();


    NewTaskDialog* newTask;
    TaskStructure *task;

private:
    Ui::TaskManagerUI *ui;

    std::unique_ptr<TaskProcessor> processor;


    void reactOnNewTask();
    void fillTable();

};

#endif // TASKMANAGERUI_H
