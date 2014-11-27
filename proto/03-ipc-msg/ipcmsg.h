#ifndef IPCMSG_H
#define IPCMSG_H

#include <QThread>
#include <QSystemSemaphore>
#include <QSharedMemory>
#include <QString>
#include <QChar>
#include <QTextStream>

class IpcMsg : public QThread
{
    Q_OBJECT
public:
    explicit IpcMsg(QObject *parent = 0);
    ~IpcMsg();
    bool masterStatus();
    void sendMessage(QString msg);
    void run();

signals:
    void incomingMsg(QString);

private:
    QSharedMemory *shmMaster;

};

#endif // IPCMSG_H
