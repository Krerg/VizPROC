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
        this->msleep(125);
    }
}
