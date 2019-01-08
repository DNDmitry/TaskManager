#include "taskmanagerui.h"
#include "ui_taskmanagerui.h"

TaskManagerUI::TaskManagerUI(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TaskManagerUI)
{
    ui->setupUi(this);
    processor = new TaskProcessor();
    task = new TaskStructure();

    ui->twMainTasksTable->setColumnWidth(0,30);
    ui->twMainTasksTable->setColumnWidth(1,100);
    ui->twMainTasksTable->setColumnWidth(2,340);
    ui->twMainTasksTable->setColumnWidth(3,110);
    ui->twMainTasksTable->setColumnWidth(4,110);
    ui->twMainTasksTable->setColumnWidth(5,50);

    fillTable();

    ui->dtStart->setDateTime(QDateTime::currentDateTime());


    connect(ui->pbNew, &QPushButton::clicked, this, &TaskManagerUI::reactOnNewTask);
}

void TaskManagerUI::clearTable()
{
    ui->twMainTasksTable->setRowCount(0);
}


void TaskManagerUI::fillTable()
{
    clearTable();
    QList<TaskStructure> tasks = processor->getAll();
    ui->twMainTasksTable->insertRow(0);
    for(auto it = tasks.begin(); it < tasks.end(); it++)
    {

        QTableWidgetItem *id = new QTableWidgetItem(it->id);
        ui->twMainTasksTable->setItem(ui->twMainTasksTable->rowCount()- 1,0,id);
        id->setFlags(id->flags() & ~Qt::ItemIsEditable);
        QTableWidgetItem *name = new QTableWidgetItem(it->name);
        ui->twMainTasksTable->setItem(ui->twMainTasksTable->rowCount()- 1,1,name);
        name->setFlags(name->flags() & ~Qt::ItemIsEditable);
        QTableWidgetItem *description = new QTableWidgetItem(it->description);
        ui->twMainTasksTable->setItem(ui->twMainTasksTable->rowCount()- 1,2,description);
        description->setFlags(description->flags() & ~Qt::ItemIsEditable);
        QTableWidgetItem *deadline = new QTableWidgetItem(it->deadLine);
        ui->twMainTasksTable->setItem(ui->twMainTasksTable->rowCount()- 1,3,deadline);
        deadline->setFlags(deadline->flags() & ~Qt::ItemIsEditable);
        QTableWidgetItem *priority = new QTableWidgetItem(it->priority);
        ui->twMainTasksTable->setItem(ui->twMainTasksTable->rowCount()- 1,4,priority);
        priority->setFlags(priority->flags() & ~Qt::ItemIsEditable);
        QTableWidgetItem *done = new QTableWidgetItem(it->done);

        if(it->done)
            done->setCheckState(Qt::Checked);
        else
            done->setCheckState(Qt::Unchecked);
        ui->twMainTasksTable->setItem(ui->twMainTasksTable->rowCount()- 1,5,done);

        if(it != --tasks.end())
            ui->twMainTasksTable->insertRow(ui->twMainTasksTable->rowCount());
    }
}

void TaskManagerUI::reactOnNewTask()
{    
    newTask = new NewTaskDialog(processor, task, this);
    newTask->setAttribute(Qt::WA_DeleteOnClose);
    newTask->exec();
    fillTable();
}

TaskManagerUI::~TaskManagerUI()
{
    delete ui;
}
