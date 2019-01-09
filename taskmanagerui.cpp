#include "taskmanagerui.h"
#include "ui_taskmanagerui.h"

TaskManagerUI::TaskManagerUI(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TaskManagerUI)
{
    ui->setupUi(this);
    this->setWindowTitle("Task Manager 3C");
    trayIcon = new QSystemTrayIcon(this);
    trayIcon->setIcon(this->style()->standardIcon(QStyle::SP_ComputerIcon));
    trayIcon->setToolTip("Task Manager 3C");
    QMenu * menu = new QMenu(this);
    QAction * viewWindow = new QAction("Expand", this);
    QAction * quitAction = new QAction("Exit", this);

    connect(viewWindow, SIGNAL(triggered()), this, SLOT(show()));
    connect(quitAction, SIGNAL(triggered()), this, SLOT(close()));

    menu->addAction(viewWindow);
    menu->addAction(quitAction);

    trayIcon->setContextMenu(menu);
    trayIcon->show();

    connect(trayIcon, SIGNAL(activated(QSystemTrayIcon::ActivationReason)),
            this, SLOT(iconActivated(QSystemTrayIcon::ActivationReason)));


    processor = new TaskProcessor();
    task = new TaskStructure();
    popUp = new PopUp();

    ui->twMainTasksTable->setColumnWidth(0,30);
    ui->twMainTasksTable->setColumnWidth(1,100);
    ui->twMainTasksTable->setColumnWidth(2,340);
    ui->twMainTasksTable->setColumnWidth(3,110);
    ui->twMainTasksTable->setColumnWidth(4,110);
    ui->twMainTasksTable->setColumnWidth(5,50);

    fillTable();

    ui->dtStart->setDateTime(QDateTime::currentDateTime());


    connect(ui->pbNew, &QPushButton::clicked, this, &TaskManagerUI::reactOnNewTask);
    connect(ui->twMainTasksTable, &QTableWidget::cellChanged, this, &TaskManagerUI::finishTask);
    connect(processor, SIGNAL(haveToCheckDeadlines()), this, SLOT(checkDeadLines()));
}

void TaskManagerUI::checkDeadLines()
{
    QString epoh = QString::number(QDateTime::currentSecsSinceEpoch());
    popUp->setPopupText(epoh);
    ui->TestLabel->setText(epoh);
    popUp->show();
}

void TaskManagerUI::finishTask(int row, int col)
{
    if(ui->twMainTasksTable->item(row,col)->checkState() == Qt::Checked)
    {
        ui->twMainTasksTable->blockSignals(true);
        task->id = ui->twMainTasksTable->item(row,0)->text();
        task->done = true;
        processor->updateTask(task);
        fillTable();
    }
    ui->twMainTasksTable->blockSignals(false);
}

void TaskManagerUI::clearTable()
{
    ui->twMainTasksTable->setRowCount(0);
}

void TaskManagerUI::fillTable()
{
    clearTable();
    QList<TaskStructure*> tasks = processor->getAll();
    ui->twMainTasksTable->insertRow(0);
    for(auto it = tasks.begin(); it < tasks.end(); it++)
    {
        QTableWidgetItem *id = new QTableWidgetItem((*it)->id);
        ui->twMainTasksTable->setItem(ui->twMainTasksTable->rowCount()- 1,0,id);
        id->setFlags(id->flags() & ~Qt::ItemIsEditable);
        QTableWidgetItem *name = new QTableWidgetItem((*it)->name);
        ui->twMainTasksTable->setItem(ui->twMainTasksTable->rowCount()- 1,1,name);
        name->setFlags(name->flags() & ~Qt::ItemIsEditable);
        QTableWidgetItem *description = new QTableWidgetItem((*it)->description);
        ui->twMainTasksTable->setItem(ui->twMainTasksTable->rowCount()- 1,2,description);
        description->setFlags(description->flags() & ~Qt::ItemIsEditable);
        QTableWidgetItem *deadline = new QTableWidgetItem((*it)->deadLine);
        ui->twMainTasksTable->setItem(ui->twMainTasksTable->rowCount()- 1,3,deadline);
        deadline->setFlags(deadline->flags() & ~Qt::ItemIsEditable);
        QTableWidgetItem *priority = new QTableWidgetItem((*it)->priority);
        ui->twMainTasksTable->setItem(ui->twMainTasksTable->rowCount()- 1,4,priority);
        priority->setFlags(priority->flags() & ~Qt::ItemIsEditable);
        QTableWidgetItem *done = new QTableWidgetItem((*it)->done);

        if((*it)->done)
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

void TaskManagerUI::closeEvent(QCloseEvent * event)
{
    if(this->isVisible()){
        event->ignore();
        this->hide();
        QSystemTrayIcon::MessageIcon icon = QSystemTrayIcon::MessageIcon(QSystemTrayIcon::Information);

        trayIcon->showMessage("Tray Program",
                              ("The application is minimized to tray."),
                              icon,
                              2000);
    }
}

void TaskManagerUI::iconActivated(QSystemTrayIcon::ActivationReason reason)
{
    switch (reason){
    case QSystemTrayIcon::Trigger:
        if(!this->isVisible()){
            this->show();
        } else {
            this->hide();
        }
        break;
    default:
        break;
    }
}

TaskManagerUI::~TaskManagerUI()
{
    delete ui;
}
