#include "connector.h"
#include <QtOpenGL/QGLWidget>
#include <QDebug>

Connector::Connector(QObject *parent) :
    QObject(parent)
{
    this->width=5;
    this->height=5;
}

Connector::~Connector() {
    qDebug()<<"Bye connector";
    if(connectedWire!=NULL) {
        //нужна реализация
    }
}

void Connector::drawComponent()
{
    glBegin(GL_LINES);

        if(!pointed)
        {
         glColor3f(255,237,0); //желтый цвет
        } else {
         glColor3f(255,0,0); //красный цвет
        }

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
    emit changePosition(this->x,this->y,x,y);
    this->x=x;
    this->y=y;
}

void Connector::setConnection(Wire* w)
{
    this->connectedWire = w;
}

Wire* Connector::getConnectedWire()
{
    return this->connectedWire;
}

void Connector::getConnectedElement()
{

}

bool Connector::checkPointing(int x, int y)
{
    if(x<this->x-width/2 || x>this->x+width/2 || y<this->y-height/2 || y>this->y+height/2)
    {
        return false;
    } else {
        return true;
    }
}

void Connector::enablePointing()
{
    this->pointed=true;
}

void Connector::disablePointing()
{
    this->pointed=false;
}

void Connector::setParentElement(Element *parent)
{
    this->parent = parent;
}

Element* Connector::getParentElement()
{
    return this->parent;
}
