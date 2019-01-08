#ifndef NEWTASKDIALOG_H
#define NEWTASKDIALOG_H

#include "taskstructure.h"
#include "taskprocessor.h"
#include <QDialog>
#include <QPushButton>

namespace Ui {
class NewTaskDialog;
}

class NewTaskDialog : public QDialog
{
    Q_OBJECT

public:
    explicit NewTaskDialog(TaskProcessor* processor, TaskStructure* task, QWidget *parent = nullptr);
    virtual ~NewTaskDialog();



private:
    Ui::NewTaskDialog *ui;
    TaskStructure* m_task;
    TaskProcessor* m_processor;


    QString checkDeadLineTime(const QDate &date, const QTime &time);
    void reactOnOk();
    void reactOnCancel();
};

#endif // NEWTASKDIALOG_H
