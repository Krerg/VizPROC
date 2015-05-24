#include "amperemeter.h"
#include <QDebug>
#include <math.h>

Amperemeter::Amperemeter(QObject *parent) : QObject(parent)
{
    this->selected = false;
    this->pointed = false;
    this->attachedWire = NULL;
    this->enabled = false;
}

Amperemeter::~Amperemeter()
{

}

void Amperemeter::paintComponent(QPainter *painter)
{
    painter->setBrush(Qt::white);
    painter->drawEllipse(x,y,20,20);
    painter->drawText(x+7,y+13,"А");
    if(attachedWire!=NULL) {
        painter->drawText(x+5,y+29,"4А");
    }
}

void Amperemeter::paintComponent()
{

}

void Amperemeter::setPosition(int x, int y)
{
    this->x = x;
    this->y = y;
}

void Amperemeter::connect(int x, int y)
{

}

bool Amperemeter::isSelected(int x, int y)
{
    if((pow((x-this->x),2)+pow((y-this->y),2))<=400) {
        return true;
    }
}

void Amperemeter::enableSelection()
{
    this->selected = true;
}

void Amperemeter::disableSelection()
{
    this->selected = false;
}

void Amperemeter::enablePointing()
{
    this->pointed = true;
}

void Amperemeter::disablePointing()
{
    this->pointed = false;
}

void Amperemeter::changeOrientation()
{

}

void Amperemeter::setEnabled()
{
    this->enabled = true;
}

void Amperemeter::setWire(Wire *w)
{
    this->attachedWire = w;
}

Connector *Amperemeter::connectorPointCheck(int x, int y)
{
    return NULL;
}

int Amperemeter::getX()
{
    return x;
}

int Amperemeter::getY()
{
    return y;
}

QString Amperemeter::getName()
{
    return "Amper";
}

bool Amperemeter::getType()
{
    return false;
}


