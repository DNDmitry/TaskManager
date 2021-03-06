#-------------------------------------------------
#
# Project created by QtCreator 2019-01-07T23:31:26
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = TaskManager
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11 c++14

SOURCES += \
        main.cpp \
        taskmanagerui.cpp \
    newtaskdialog.cpp \
    popup.cpp

HEADERS += \
        taskmanagerui.h \
    newtaskdialog.h \
    popup.h

FORMS += \
        taskmanagerui.ui \
    newtaskdialog.ui


win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../bin/debug/release/ -lTaskProcessor
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../bin/debug/debug/ -lTaskProcessor
else:unix: LIBS += -L$$PWD/../bin/debug/ -lTaskProcessor

INCLUDEPATH += $$PWD/../bin/debug/debug
DEPENDPATH += $$PWD/../bin/debug/debug
