#include "ipcmsg.h"

IpcMsg::IpcMsg(QObject *parent) : QThread(parent)
{
    shmMaster = new QSharedMemory("TimeTrackShm");
}

IpcMsg::~IpcMsg()
{
    delete shmMaster;
}

bool IpcMsg::masterStatus()
{
    auto success = shmMaster->create(1024);
    if(success == false){ // not master
        auto reason = shmMaster->error();
        if(reason == QSharedMemory::AlreadyExists){
            return false;
        } else {
            // panic!
            exit(EXIT_FAILURE);
        }
    }
    return true;
}

void IpcMsg::sendMessage(QString msg)
{
    auto shm = new QSharedMemory("TimeTrackShm");
    shm->attach();
    shm->lock();

    // send the message
    char *to = (char*)shm->data();
    QChar *data = msg.data();
    while(!data->isNull()){
        memset(to, data->toLatin1(), 1);
        ++data;
        ++to;
    }
    memset(to, 0, 1);

    shm->unlock();
    delete shm;

    // unlock the listener
    auto sem = new QSystemSemaphore(
                "TimeTrackSem", 0, QSystemSemaphore::Open);
    sem->release();
    delete sem;
}

void IpcMsg::run()
{
    auto sem = new QSystemSemaphore(
                "TimeTrackSem", 0, QSystemSemaphore::Create);
    while(true){
        sem->acquire(); // blocks until message arrives

        // read message from shared memery
        QString msg;
        QTextStream stream(&msg);
        const char *from = (char const*)shmMaster->data();
        while(from && *from){
            stream << *from;
            ++from;
        }

        // send message to main thread
        emit incomingMsg(msg);

        // if message is "exit", break loop
        if(msg == "exit"){
            break;
        }
    }
    // cleanup on exit
    delete sem;
}
