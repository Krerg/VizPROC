#include "particle.h"
#include <QDebug>

Particle::Particle(QObject *parent) : QObject(parent)
{

}

void Particle::setPath(QList<QPoint *> *path, int numb)
{
    this->path = path;
    this->pointNumber = numb;
}

void Particle::setPosition(int x, int y)
{
    this->x = x;
    this->y = y;
}

void Particle::visualisation(QPainter *painter)
{
     painter->setPen(QPen(QColor(255,0,0),2));
     painter->drawEllipse(x-1,y-1,2,2);
}

Particle::~Particle()
{
    //qDebug()<<"deleted";
}

