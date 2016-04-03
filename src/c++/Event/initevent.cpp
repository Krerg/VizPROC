#include "src/c++/Event/initevent.h"

InitEvent::InitEvent(QObject *parent) :
    QObject(parent)
{
}
QList<Branch *> *InitEvent::getBranches() const
{
    return branches;
}

void InitEvent::setBranches(QList<Branch *> *value)
{
    branches = value;
}
double *InitEvent::getX() const
{
    return x;
}

void InitEvent::setX(double *value)
{
    x = value;
}



