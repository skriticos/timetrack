#ifndef SYSTRAYPROTO_H
#define SYSTRAYPROTO_H

#include <QWidget>
#include <QSystemTrayIcon>
#include <QIcon>
#include <QMenu>
#include <QAction>
#include <QCursor>

class SysTrayProto : public QWidget
{
    Q_OBJECT

public:
    SysTrayProto(QWidget *parent = 0);

private:
    QSystemTrayIcon* systray;
    QMenu *projectSelectMenu;

    bool onOffState;

private slots:
    void onActivated(QSystemTrayIcon::ActivationReason reason);
};

#endif // SYSTRAYPROTO_H
