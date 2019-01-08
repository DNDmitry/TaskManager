#include "taskmanagerui.h"
#include "ui_taskmanagerui.h"

TaskManagerUI::TaskManagerUI(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TaskManagerUI)
{
    ui->setupUi(this);
    processor = std::make_unique<TaskProcessor>();

    ui->twMainTasksTable->setColumnWidth(0,30);
    ui->twMainTasksTable->setColumnWidth(1,100);
    ui->twMainTasksTable->setColumnWidth(2,340);
    ui->twMainTasksTable->setColumnWidth(3,110);
    ui->twMainTasksTable->setColumnWidth(4,110);
    ui->twMainTasksTable->setColumnWidth(5,50);
    ui->TestLabel->setText(processor->ReturnTestString());

}

TaskManagerUI::~TaskManagerUI()
{
    delete ui;
}
