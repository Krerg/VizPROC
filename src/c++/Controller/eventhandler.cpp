#include "eventhandler.h"
#include <QDebug>

EventHandler::EventHandler(QObject *parent) :
    QObject(parent)
{
    this->selectedElem = NULL;
    this->locked = false;
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
        if(selectedElem!=NULL)
        {
        qDebug() << selectedElem->currentText();
        emit addElement(selectedElem->currentText(),event->x(),event->y());
        }
    } else if(event->button() == Qt::LeftButton)
    {
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
