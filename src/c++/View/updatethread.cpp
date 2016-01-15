#include "updatethread.h"
#include <QDebug>

UpdateThread::UpdateThread(QObject *parent) :
    QThread(parent)
{

}

void UpdateThread::run()
{
    while(true)
    {
        emit update();
        //задержка
        this->msleep(30);
    }
}
