#include "updatethread.h"

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
        this->msleep(45);
    }
}
