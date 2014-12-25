#include "mousetrackerthread.h"
#include <QPoint>
#include <QCursor>
#include <QDebug>

MouseTrackerThread::MouseTrackerThread(QGLWidget *widget, QObject *parent) :
    QThread(parent)
{
    this->widget=widget;
}

void MouseTrackerThread::run()
{
    //координаты мыши, которые были до этого
    int x=0;
    int y=0;

    //новые координаты мыши
    int newX=0;
    int newY=0;

    QPoint mousePoint;
    while(true)
    {
        newX = widget->mapFromGlobal(QCursor::pos()).x();;
        newY = widget->mapFromGlobal(QCursor::pos()).y();;
        qDebug() << newX;
        qDebug() << newY;
        if(x!=newX || y!=newY)
        {
         //   emit mouseMoved(newX, newY);
            x = newX;
            y = newY;
        }
        this->msleep(20);
    }
}
