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

    auto a1 = new QAction("Project 1", this);
    auto a2 = new QAction("Project 2", this);
    auto a3 = new QAction("Project 3", this);

    a1->setCheckable(true);
    a1->setChecked(true);
    a2->setCheckable(true);
    a3->setCheckable(true);

    auto projectActGroup = new QActionGroup(this);
    projectActGroup->addAction(a1);
    projectActGroup->addAction(a2);
    projectActGroup->addAction(a3);

    projectSelectMenu->addAction(a1);
    projectSelectMenu->addAction(a2);
    projectSelectMenu->addAction(a3);

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

