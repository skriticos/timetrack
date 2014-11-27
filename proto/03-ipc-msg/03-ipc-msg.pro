QT += widgets
CONFIG += c++11

TARGET = 03-ipc-msg
TEMPLATE = app

SOURCES += main.cpp mainwindow.cpp \
    ipcmsg.cpp
HEADERS  += mainwindow.h \
    ipcmsg.h
