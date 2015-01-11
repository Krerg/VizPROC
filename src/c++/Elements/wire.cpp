#include "wire.h"
#include <QtOpenGL/QGLWidget>

Wire::Wire(QObject *parent) :
    QObject(parent)
{
    this->path = new QList<QPoint*>;
    this->connected1 = NULL;
    this->connected2 = NULL;
}

void Wire::addPoint(QPoint *point)
{
    this->path->insert(path->end(),point);
}

void Wire::addPoint(int x, int y)
{
    QPoint *temp = new QPoint(x,y);
    this->path->insert(this->path->end(),temp);
}

void Wire::setNumber(int number)
{
    this->number = number;
}

void Wire::paintComponent()
{
    //рисуем если длина провода хотя бы больше 1
    if(this->path->size()>1) {
    QPoint *start = this->path->at(0);


    glBegin(GL_LINES);
    for(int i = 1;i<this->path->size();i++)
    {
         glVertex3f(start->x(),start->y(),0.0f);
         glVertex3f(path->at(i)->x(),path->at(i)->y(),0.0f);

         start = path->at(i);
    }
    glEnd();
    }
}

void Wire::startConnection(Connector *c)
{
    this->connected1=c;
    this->path->insert(path->end(),new QPoint(c->getX(),c->getY()));
}

void Wire::endConnection(Connector *c)
{
    this->connected2=c;
}
