#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
{
    resize(300, 200);
    setText("Waiting for message..");
    setAlignment(Qt::AlignCenter);

    ipc = new IpcMsg(this);

    // check master instance status
    auto isMaster = ipc->masterStatus();
    if(isMaster == false){ // secondary instance
        auto args = QCoreApplication::arguments();
        if(args.size()>1){
            ipc->sendMessage(args.at(1));
        }
        exit(EXIT_SUCCESS);
    }

    // master instance
    connect(ipc, &IpcMsg::incomingMsg,
            this, &MainWindow::onIncoming);
    ipc->start();
}

MainWindow::~MainWindow()
{
    // shutdown listener thread when main window is closed
    if(shutdownStarted == false){
        ipc->sendMessage("exit");
        ipc->wait();
    }
}

void MainWindow::onIncoming(QString msg)
{
    if(msg == "exit" && shutdownStarted == false){
        // exit application when exit message is receaved
        QCoreApplication::quit();
    } else {
        // else, set the label to the message
        setText(msg);
    }
}
