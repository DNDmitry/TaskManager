#include "taskmanagerui.h"
#include "ui_taskmanagerui.h"

TaskManagerUI::TaskManagerUI(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TaskManagerUI)
{
    ui->setupUi(this);
}

TaskManagerUI::~TaskManagerUI()
{
    delete ui;
}
