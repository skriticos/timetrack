#include "systrayproto.h"

SysTrayProto::SysTrayProto(QWidget *parent)
    : QWidget(parent)
{
    systray = new QSystemTrayIcon(this);
    systray->setIcon(QIcon(":off.png"));
    systray->show();

    onOffState = false;

    auto contextMenu = new QMenu(this);
    contextMenu->addAction(new QAction("Config", this));
    contextMenu->addAction(new QAction("Project Manager", this));
    contextMenu->addAction(new QAction("Analytics", this));

    systray->setContextMenu(contextMenu);

    projectSelectMenu = new QMenu(this);
    projectSelectMenu->addAction(new QAction("Project 1", this));
    projectSelectMenu->addAction(new QAction("Project 2", this));
    projectSelectMenu->addAction(new QAction("Project 3", this));

    systray->setToolTip("Project: Project 1");

    connect(systray, &QSystemTrayIcon::activated,
            this, &SysTrayProto::onActivated);
}

void SysTrayProto::onActivated(QSystemTrayIcon::ActivationReason reason)
{
    if (reason == QSystemTrayIcon::Trigger) {
        if (onOffState == true) {
            systray->setIcon(QIcon(":off.png"));
            onOffState = false;
        } else {
            systray->setIcon(QIcon(":on.png"));
            onOffState = true;
        }
    }

    if (reason == QSystemTrayIcon::MiddleClick) {
        projectSelectMenu->exec(QCursor::pos());
    }
}

