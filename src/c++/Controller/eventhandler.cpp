#include "eventhandler.h"
#include <QDebug>

EventHandler::EventHandler(QObject *parent) :
    QObject(parent)
{
    this->selectedElem = NULL;
    this->locked = false;
    this->elementType = -1;
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
    qDebug()<<"Mouse released";
    if(event->button() == Qt::RightButton && !locked) {
        if(elementType>=0) {
            emit addElement(elementType,event->x(),event->y());
        }
    } else if(event->button() == Qt::LeftButton) {
        emit leftClickReleased();
    }
}

void EventHandler::mouseMoved(QMouseEvent *event)
{
    if(!locked)
        emit moveElement(event->x(),event->y());
}


void EventHandler::mouseDoubleClicked(QMouseEvent *event)
{
    if(!locked)
        emit changeOrientation(event->x(),event->y());
}

void EventHandler::keyPressed(QKeyEvent *event)
{
    if(!locked && event->key()==16777223) {
        emit deleteItem();
    }
}

void EventHandler::resistorActivate()
{
    this->elementType = 0;
}

void EventHandler::emfActivate()
{
    this->elementType = 1;
}

void EventHandler::diodeActivate()
{
    this->elementType = 2;
}

void EventHandler::groundActivate()
{
    this->elementType = 3;
}

void EventHandler::wireActivate()
{
    this->elementType = 4;
}

void EventHandler::amperemeterActivate()
{
    this->elementType = 5;
}

void EventHandler::voltmeterActivate()
{
    this->elementType = 6;
}

void EventHandler::setQComboBox(QComboBox *c)
{
    this->selectedElem = c;
}

void EventHandler::setLock()
{
    this->locked = true;
}

void EventHandler::releaseLock()
{
    this->locked = false;
}
