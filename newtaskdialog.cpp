#include "newtaskdialog.h"
#include "ui_newtaskdialog.h"

NewTaskDialog::NewTaskDialog(QString* name, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NewTaskDialog)
{
    ui->setupUi(this);

    m_name = name;

    connect(ui->pbOk, &QPushButton::clicked, this, &NewTaskDialog::reactOnOk);
}

void NewTaskDialog::reactOnOk()
{    
    *m_name = ui->leName->text();
    this->reject();
}

NewTaskDialog::~NewTaskDialog()
{
    delete ui;
}