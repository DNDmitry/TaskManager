#include "taskmanagerui.h"
#include "ui_taskmanagerui.h"

TaskManagerUI::TaskManagerUI(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TaskManagerUI)
{
    ui->setupUi(this);
    processor = std::make_unique<TaskProcessor>();
    name = new QString();

    ui->twMainTasksTable->setColumnWidth(0,30);
    ui->twMainTasksTable->setColumnWidth(1,100);
    ui->twMainTasksTable->setColumnWidth(2,340);
    ui->twMainTasksTable->setColumnWidth(3,110);
    ui->twMainTasksTable->setColumnWidth(4,110);
    ui->twMainTasksTable->setColumnWidth(5,50);


    ui->TestLabel->setText(processor->ReturnTestString());

    connect(ui->pbNew, &QPushButton::clicked, this, &TaskManagerUI::reactOnNewTask);
}

void TaskManagerUI::reactOnNewTask()
{    
    newTask = new NewTaskDialog(name, this);
    newTask->setAttribute(Qt::WA_DeleteOnClose);
    newTask->exec();

    ui->TestLabel->setText(*name);
}

TaskManagerUI::~TaskManagerUI()
{
    delete ui;
}
