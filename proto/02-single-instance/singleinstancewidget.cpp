#include "singleinstancewidget.h"

SingleInstanceWidget::SingleInstanceWidget(QWidget *parent) : QLabel(parent)
{
    setText("Primary Instance..");
    setAlignment(Qt::AlignCenter);
    resize(300, 200);

    auto shm = new QSharedMemory("TimeTrack", this);
    auto success = shm->create(1024);
    if(success == false){
        auto reason = shm->error();
        if(reason == QSharedMemory::AlreadyExists){
            QMessageBox::critical(this, "error", "secondary instance..");
            exit(EXIT_FAILURE);
        } else {
            // handle system errors
        }
    }
}

SingleInstanceWidget::~SingleInstanceWidget(){}
