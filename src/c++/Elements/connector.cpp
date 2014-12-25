#include "connector.h"
#include <QtOpenGL/QGLWidget>

Connector::Connector(QObject *parent) :
    QObject(parent)
{
    this->connectedWith=NULL;
    this->width=5;
    this->height=5;
}

void Connector::drawComponent()
{
    glBegin(GL_LINES);

       glColor3f(255,237,0); //желтый цвет

        //Рисуем крест
        glVertex3f(x-width/2,y-height/2,0.0f);
        glVertex3f(x+width/2,y+height/2,0.0f);

        glVertex3f(x-width/2,y+height/2,0.0f);
        glVertex3f(x+width/2,y-height/2,0.0f);

    glEnd();
}

int Connector::getX()
{
    return this->x;
}

int Connector::getY()
{
    return this->y;
}

void Connector::setPosition(int x, int y)
{
    this->x=x;
    this->y=y;
}

void Connector::setConnection(Element *elem)
{
    this->connectedWith = elem;
}

Element* Connector::getConnectedElement()
{
    return this->connectedWith;
}
