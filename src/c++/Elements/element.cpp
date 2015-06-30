#include "element.h"

Element::~Element() {

}


int Element::getSavingNumber()
{
    return this->savingNumber;
}

void Element::setSavingNumber(int number)
{
    this->savingNumber = number;
}

QString Element::getPosition()
{
    return this->orientation;
}

void Element::setPosition(QString position)
{
    this->orientation = position;
}
