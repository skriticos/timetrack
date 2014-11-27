#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QLabel>
#include <QCoreApplication>

#include "ipcmsg.h"

class MainWindow : public QLabel
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    IpcMsg *ipc;
    bool shutdownStarted;

private slots:
    void onIncoming(QString msg);
};

#endif // MAINWINDOW_H
