#include "geometry.h"
#include <QDebug>

Geometry::Geometry(QObject *parent) :
    QObject(parent)
{
}

bool Geometry::pointCrossX(int oldX, int staticX, int newX)
{
    if(newX == staticX)
    {
        return true;
    }
    int temp1 = staticX - oldX;
    int temp2 = staticX - newX;

    if((temp1>0 && temp2<0) || (temp1<0 && temp2>0))
    {
        return true;
    }
    return false;
}

bool Geometry::pointCrossY(int oldY, int staticY, int newY)
{
    return false;
}
