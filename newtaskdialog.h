#ifndef NEWTASKDIALOG_H
#define NEWTASKDIALOG_H

#include "taskstructure.h"
#include <QDialog>
#include <QPushButton>

namespace Ui {
class NewTaskDialog;
}

class NewTaskDialog : public QDialog
{
    Q_OBJECT

public:
    explicit NewTaskDialog(TaskStructure* task, QWidget *parent = nullptr);
    virtual ~NewTaskDialog();



private:
    Ui::NewTaskDialog *ui;
    TaskStructure* m_task;


    void reactOnOk();
};

#endif // NEWTASKDIALOG_H
