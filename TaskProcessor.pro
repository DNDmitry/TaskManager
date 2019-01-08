#-------------------------------------------------
#
# Project created by QtCreator 2019-01-08T00:02:39
#
#-------------------------------------------------
QT += sql
QT       -= gui

TARGET = TaskProcessor
TEMPLATE = lib

DEFINES += TASKPROCESSOR_LIBRARY

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
        taskprocessor.cpp

HEADERS += \
        taskprocessor.h \
        taskprocessor_global.h \
    taskstructure.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../bin/debug/release/ -lTaskDBConnector
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../bin/debug/debug/ -lTaskDBConnector
else:unix: LIBS += -L$$PWD/../bin/debug/ -lTaskDBConnector

INCLUDEPATH += $$PWD/../bin/debug/debug
DEPENDPATH += $$PWD/../bin/debug/debug
