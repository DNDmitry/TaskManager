#ifndef TASKMANAGERUI_H
#define TASKMANAGERUI_H

#include "newtaskdialog.h"
#include <QWidget>
#include "taskprocessor.h"
#include <memory>
#include <QTableWidgetItem>
#include <QDebug>
#include <string>
#include "popup.h"
#include <QCloseEvent>
#include <QSystemTrayIcon>
#include <QAction>
#include <QMenu>

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

public slots:
    void checkDeadLines();

private:
    Ui::TaskManagerUI *ui;

    TaskProcessor *processor;
    PopUp *popUp;
    void reactOnNewTask();
    void fillTable();
    void clearTable();
    void finishTask(int row, int col);

protected:
    void closeEvent(QCloseEvent * event);

private slots:
    void iconActivated(QSystemTrayIcon::ActivationReason reason);

private:

    QSystemTrayIcon *trayIcon;
};

#endif // TASKMANAGERUI_H
