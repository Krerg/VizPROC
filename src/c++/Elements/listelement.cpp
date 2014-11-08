#include "listelement.h"

ListElement::ListElement(QObject *parent) :
    QObject(parent)
{

}
void ListElement::setElement(QObject *element)
{
    this->element=element;
}
void ListElement::setType(QString type)
{
    this->type=type;
}

QString ListElement::getType()
{
    return this->type;
}

QObject* ListElement::getElement()
{
    return this->element;
}
