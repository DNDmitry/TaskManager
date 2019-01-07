#include "taskmanagerui.h"
#include "ui_taskmanagerui.h"

TaskManagerUI::TaskManagerUI(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TaskManagerUI)
{
    ui->setupUi(this);
    processor = std::make_unique<TaskProcessor>();
    ui->TestLabel->setText(processor->ReturnTestString());


}

TaskManagerUI::~TaskManagerUI()
{
    delete ui;
}
