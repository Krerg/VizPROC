#include "wireconnector.h"

WireConnector::WireConnector(int x, int y,QObject *parent) : QObject(parent)
{
    this->x = x;
    this->y = y;
}

WireConnector::~WireConnector()
{

}

void WireConnector::paintComponent()
{

}

int WireConnector::getX()
{
    return this->x;
}

int WireConnector::getY()
{
    return this->y;
}

