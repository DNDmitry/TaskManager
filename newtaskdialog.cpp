#include "newtaskdialog.h"
#include "ui_newtaskdialog.h"

NewTaskDialog::NewTaskDialog(TaskProcessor* processor, TaskStructure* task, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NewTaskDialog)
{
    ui->setupUi(this);

    m_task = task;
    m_processor = processor;

    ui->dtDeadLine->setDateTime(QDateTime::currentDateTime());

    connect(ui->pbOk, &QPushButton::clicked, this, &NewTaskDialog::reactOnOk);
    connect(ui->pbCancel, &QPushButton::clicked, this, &NewTaskDialog::reactOnCancel);
}

void NewTaskDialog::reactOnOk()
{    
    m_task->name = ui->leName->text();
    m_task->description = ui->leDescription->text();
    m_task->deadLine = checkDeadLineTime(ui->dtDeadLine->date(), ui->dtDeadLine->time());
    m_task->priority = ui->cbPriotiry->currentText();
    m_processor->createTask(m_task);
    this->reject();
}

void NewTaskDialog::reactOnCancel()
{
    this->reject();
}

QString NewTaskDialog::checkDeadLineTime(const QDate &date, const QTime &time)
{
    QString deadline = date.toString();
    deadline.append(' ');
    deadline.append(time.toString());
    return deadline;
}

NewTaskDialog::~NewTaskDialog()
{
    delete ui;
}
