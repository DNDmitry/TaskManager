#include "taskmanagerui.h"
#include "ui_taskmanagerui.h"

TaskManagerUI::TaskManagerUI(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TaskManagerUI)
{
    ui->setupUi(this);
    processor = std::make_unique<TaskProcessor>();
    task = new TaskStructure();

    ui->twMainTasksTable->setColumnWidth(0,30);
    ui->twMainTasksTable->setColumnWidth(1,100);
    ui->twMainTasksTable->setColumnWidth(2,340);
    ui->twMainTasksTable->setColumnWidth(3,110);
    ui->twMainTasksTable->setColumnWidth(4,110);
    ui->twMainTasksTable->setColumnWidth(5,50);

    fillTable();


    connect(ui->pbNew, &QPushButton::clicked, this, &TaskManagerUI::reactOnNewTask);
}


void TaskManagerUI::fillTable()
{
    QList<TaskStructure> tasks = processor->getAll();
    ui->twMainTasksTable->insertRow(0);
    for(TaskStructure task : tasks)
    {

        QTableWidgetItem *id = new QTableWidgetItem(task.id);
        ui->twMainTasksTable->setItem(ui->twMainTasksTable->rowCount()- 1,0,id);
        id->setFlags(id->flags() & ~Qt::ItemIsEditable);
        QTableWidgetItem *name = new QTableWidgetItem(task.name);
        ui->twMainTasksTable->setItem(ui->twMainTasksTable->rowCount()- 1,1,name);
        name->setFlags(name->flags() & ~Qt::ItemIsEditable);
        QTableWidgetItem *description = new QTableWidgetItem(task.description);
        ui->twMainTasksTable->setItem(ui->twMainTasksTable->rowCount()- 1,2,description);
        description->setFlags(description->flags() & ~Qt::ItemIsEditable);
        QTableWidgetItem *deadline = new QTableWidgetItem(task.deadLine);
        ui->twMainTasksTable->setItem(ui->twMainTasksTable->rowCount()- 1,3,deadline);
        deadline->setFlags(deadline->flags() & ~Qt::ItemIsEditable);
        QTableWidgetItem *priority = new QTableWidgetItem(task.priority);
        ui->twMainTasksTable->setItem(ui->twMainTasksTable->rowCount()- 1,4,priority);
        priority->setFlags(priority->flags() & ~Qt::ItemIsEditable);
        QTableWidgetItem *done = new QTableWidgetItem(task.done);

        if(task.done)
            done->setCheckState(Qt::Checked);
        else
            done->setCheckState(Qt::Unchecked);
        ui->twMainTasksTable->setItem(ui->twMainTasksTable->rowCount()- 1,5,done);

        ui->twMainTasksTable->insertRow(ui->twMainTasksTable->rowCount());
    }
}

void TaskManagerUI::reactOnNewTask()
{    
    newTask = new NewTaskDialog(task, this);
    newTask->setAttribute(Qt::WA_DeleteOnClose);
    newTask->exec();

    processor->createTask(task);
}

TaskManagerUI::~TaskManagerUI()
{
    delete ui;
}
