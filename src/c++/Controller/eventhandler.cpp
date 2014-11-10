#include "eventhandler.h"

EventHandler::EventHandler(QObject *parent) :
    QObject(parent)
{
}

void EventHandler::mouseClicked(QMouseEvent *event)
{

}

void EventHandler::mouseReleased(QMouseEvent *event)
{
    if(event->button() == Qt::RightButton)
    {
        emit addResistor(event->x(),event->y());
    }
}

void EventHandler::mouseMoved(QMouseEvent *event)
{

}
