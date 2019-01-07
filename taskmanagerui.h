#ifndef TASKMANAGERUI_H
#define TASKMANAGERUI_H

#include <QWidget>

namespace Ui {
class TaskManagerUI;
}

class TaskManagerUI : public QWidget
{
    Q_OBJECT

public:
    explicit TaskManagerUI(QWidget *parent = nullptr);
    ~TaskManagerUI();

private:
    Ui::TaskManagerUI *ui;
};

#endif // TASKMANAGERUI_H
