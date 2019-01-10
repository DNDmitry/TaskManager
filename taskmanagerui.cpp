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

    ui->twMainTasksTable->horizontalHeader()->setSectionResizeMode(0, QHeaderView::Stretch);
    ui->twMainTasksTable->horizontalHeader()->setSectionResizeMode(1, QHeaderView::Stretch);
    ui->twMainTasksTable->setColumnWidth(0,150);
    ui->twMainTasksTable->setColumnWidth(1,300);
    ui->twMainTasksTable->setColumnWidth(2,100);
    ui->twMainTasksTable->setColumnWidth(3,220);
    ui->twMainTasksTable->setColumnWidth(4,100);

    fillTable();

    connect(ui->pbNew, &QPushButton::clicked, this, &TaskManagerUI::reactOnNewTask);
    connect(ui->twMainTasksTable, &QTableWidget::cellChanged, this, &TaskManagerUI::finishTask);
    connect(processor, SIGNAL(haveToCheckDeadlines()), this, SLOT(checkDeadLines()));
}

void TaskManagerUI::checkDeadLines()
{    
    if(ui->twMainTasksTable->item(0,0) != nullptr)
    {
        QString message = "Believe in yourself! Have faith in your abilities! Just do these tasks: ";
        QList<TaskStructure> urgentTasks;
        QVector<int> rowNumbers;
        getUrgentTasks(urgentTasks, rowNumbers);
        if(!urgentTasks.isEmpty())
        {
            for(int i : rowNumbers)
            {
                for(int j = 0; j < ui->twMainTasksTable->columnCount(); j++)
                {
                    ui->twMainTasksTable->item(i,j)->setBackgroundColor(Qt::red);
                    if(j == 0)
                    {
                        message += ui->twMainTasksTable->item(i,j)->text() + " ";
                    }
                }

            }
            popUp->setPopupText(message);
            popUp->show();
        }
    }

}

void TaskManagerUI::getUrgentTasks(QList<TaskStructure> &urgentTasks, QVector<int> &rowNumbers)
{
    for(int i = 0; i < ui->twMainTasksTable->rowCount(); i++)
    {
        QDateTime deadline = QDateTime::fromString(ui->twMainTasksTable->item(i,3)->text());
        QDateTime current = QDateTime::currentDateTime();
        qDebug() << current.secsTo(deadline);

        if(ui->twMainTasksTable->item(i, 4)->checkState() == Qt::Unchecked && current.secsTo(deadline) <= 1800 && ui->twMainTasksTable->item(i,4)->backgroundColor() != Qt::red)
        {
            TaskStructure task;
            task.name = ui->twMainTasksTable->item(i, 0)->text();
            urgentTasks.push_back(task);
            rowNumbers.push_back(i);
        }
    }
}

void TaskManagerUI::finishTask(int row, int col)
{
    if(ui->twMainTasksTable->item(row,col)->checkState() == Qt::Checked)
    {
        ui->twMainTasksTable->blockSignals(true);
        task->name = ui->twMainTasksTable->item(row,0)->text();
        task->done = true;
        qDebug() << "task->name => " + task->name;
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
        QTableWidgetItem *name = new QTableWidgetItem((*it)->name);
        ui->twMainTasksTable->setItem(ui->twMainTasksTable->rowCount()- 1,0,name);
        name->setFlags(name->flags() & ~Qt::ItemIsEditable);
        QTableWidgetItem *description = new QTableWidgetItem((*it)->description);
        ui->twMainTasksTable->setItem(ui->twMainTasksTable->rowCount()- 1,1,description);
        description->setFlags(description->flags() & ~Qt::ItemIsEditable);
        QTableWidgetItem *priority = new QTableWidgetItem((*it)->priority);
        ui->twMainTasksTable->setItem(ui->twMainTasksTable->rowCount()- 1,2,priority);
        priority->setFlags(priority->flags() & ~Qt::ItemIsEditable);
        priority->setTextAlignment(Qt::AlignHCenter);
        QTableWidgetItem *deadline = new QTableWidgetItem((*it)->deadLine);
        ui->twMainTasksTable->setItem(ui->twMainTasksTable->rowCount()- 1,3,deadline);
        deadline->setFlags(deadline->flags() & ~Qt::ItemIsEditable);
        deadline->setTextAlignment(Qt::AlignHCenter);

        QTableWidgetItem *done = new QTableWidgetItem((*it)->done);

        if((*it)->done)
            done->setCheckState(Qt::Checked);
        else
            done->setCheckState(Qt::Unchecked);
        ui->twMainTasksTable->setItem(ui->twMainTasksTable->rowCount()- 1,4,done);

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
