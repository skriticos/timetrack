#ifndef SINGLEINSTANCEWIDGET_H
#define SINGLEINSTANCEWIDGET_H

#include <QLabel>
#include <QMessageBox>
#include <QSharedMemory>
#include <QCoreApplication>

class SingleInstanceWidget : public QLabel
{
    Q_OBJECT

public:
    SingleInstanceWidget(QWidget *parent = 0);
    ~SingleInstanceWidget();
};

#endif // SINGLEINSTANCEWIDGET_H
