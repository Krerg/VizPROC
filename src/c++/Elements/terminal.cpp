#include "terminal.h"
#include "math.h"
#include <QDebug>

Terminal::Terminal(QObject *parent) : QObject(parent)
{
    this->connectedWire = NULL;
}

Terminal::~Terminal()
{

}

void Terminal::setConnectedWire(Wire *w)
{
    this->connectedWire = w;
}

bool Terminal::isConnected()
{
    if(connectedWire == NULL) {
        return false;
    } else {
        return true;
    }
}

double Terminal::getValue()
{
    if(connectedWire!=NULL) {
        if(connectedWire->isGround()) {
            return 0.0;
        }

        return connectedWire->getPotential();
    } else {
        return 0.0;
    }
}

void Terminal::paintComponent(QPainter *painter)
{
    painter->setBrush(QBrush(color));
    if(connectedWire==NULL) {
        painter->drawEllipse(x,y,15,15);
    } else {
        painter->drawEllipse(x,y,16,16);
    }
}

void Terminal::setColor(QColor color)
{
    this->color = color;
}

void Terminal::setPosition(int x, int y)
{
    this->x = x;
    this->y = y;
}

void Terminal::connect(int x, int y)
{

}

void Terminal::paintComponent()
{

}

bool Terminal::isSelected(int x, int y)
{
    if((pow((x-this->x),2)+pow((y-this->y),2))<=225) {
        return true;
    } else {
        return false;
    }
}

void Terminal::disableSelection()
{

}

void Terminal::enableSelection()
{

}

void Terminal::enablePointing()
{

}

void Terminal::disablePointing()
{

}

void Terminal::changeOrientation()
{

}

Connector *Terminal::connectorPointCheck(int x, int y)
{

}

int Terminal::getX()
{
    return this->x;
}

int Terminal::getY()
{
    return this->y;
}

bool Terminal::getType()
{
    return false;
}

QString Terminal::getName()
{
    return "Terminal";
}

void Terminal::disconnectWire(Wire *w)
{

}

QList<Connector *> *Terminal::getConnectors()
{

}



