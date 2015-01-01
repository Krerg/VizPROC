#include "eventhandler.h"

EventHandler::EventHandler(QObject *parent) :
    QObject(parent)
{
}

void EventHandler::mouseClicked(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton)
    {
        emit click(event->x(), event->y());
    }
}

void EventHandler::mouseReleased(QMouseEvent *event)
{
    if(event->button() == Qt::RightButton)
    {
        emit addElement("res",event->x(),event->y());
    } else if(event->button() == Qt::LeftButton)
    {
        emit leftClickReleased();
    }
}

void EventHandler::mouseMoved(QMouseEvent *event)
{
    emit moveElement(event->x(),event->y());
}


void EventHandler::mouseDoubleClicked(QMouseEvent *event)
{
   emit changeOrientation(event->x(),event->y());
}
