#include "taskmanagerui.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    TaskManagerUI w;
    w.show();

    return a.exec();
}
