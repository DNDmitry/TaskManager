#include "newtaskdialog.h"
#include "ui_newtaskdialog.h"

NewTaskDialog::NewTaskDialog(TaskStructure* task, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NewTaskDialog)
{
    ui->setupUi(this);

    m_task = task;

    connect(ui->pbOk, &QPushButton::clicked, this, &NewTaskDialog::reactOnOk);
}

void NewTaskDialog::reactOnOk()
{    
    m_task->name = ui->leName->text();
    m_task->description = ui->leDescription->text();
    m_task->deadLine = ui->leDeadLine->text();
    m_task->priority = ui->cbPriotiry->currentText();


    this->reject();
}

NewTaskDialog::~NewTaskDialog()
{
    delete ui;
}
