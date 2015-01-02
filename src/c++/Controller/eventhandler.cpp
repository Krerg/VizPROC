#include "eventhandler.h"
#include <QDebug>

EventHandler::EventHandler(QObject *parent) :
    QObject(parent)
{
    this->selectedElem = NULL;
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
    emit moveElement(event->x(),event->y());
}


void EventHandler::mouseDoubleClicked(QMouseEvent *event)
{
   emit changeOrientation(event->x(),event->y());
}

void EventHandler::setQComboBox(QComboBox *c)
{
    this->selectedElem = c;
}
