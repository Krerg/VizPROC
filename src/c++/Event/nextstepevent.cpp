#include "nextstepevent.h"

NextStepEvent::NextStepEvent(QObject *parent) :
    QObject(parent)
{
}
QList<Wire *> *NextStepEvent::getWires() const
{
    return wires;
}

void NextStepEvent::setWires(QList<Wire *> *value)
{
    wires = value;
}
QList<Element *> *NextStepEvent::getElements() const
{
    return elements;
}

void NextStepEvent::setElements(QList<Element *> *value)
{
    elements = value;
}


