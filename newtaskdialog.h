#ifndef NEWTASKDIALOG_H
#define NEWTASKDIALOG_H


#include <QDialog>
#include <QPushButton>

namespace Ui {
class NewTaskDialog;
}

class NewTaskDialog : public QDialog
{
    Q_OBJECT

public:
    explicit NewTaskDialog(QString* name, QWidget *parent = nullptr);
    virtual ~NewTaskDialog();



private:
    Ui::NewTaskDialog *ui;
    QString* m_name;


    void reactOnOk();
};

#endif // NEWTASKDIALOG_H
