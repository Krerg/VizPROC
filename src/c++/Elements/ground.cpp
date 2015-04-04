#include "ground.h"
#include <QtOpenGL/QGLWidget>

Ground::Ground(QObject *parent) :
    QObject(parent)
{
    this->width = 20;
    this->height=32;
    this->selected = false;
    this->pointed = false;
    this->c1 = new Connector();
    this->setConnectorPosition();
}

Ground::~Ground()
{

}

void Ground::setPosition(int x, int y)
{
    this->x = x;
    this->y = y;
    this->setConnectorPosition();
}

void Ground::paintComponent()
{
    glBegin(GL_LINES);

        //если элемент выделене, то рисуем его другим цветом
        if(!selected) {
        glColor3f(0,0,0);
        } else {
            glColor3f(0,0,8.0f);
        }

        glVertex3f(x+width/2,y,0.0f);
        glVertex3f(x+width/2,y+height*3/4,0.0f);

        glVertex3f(x,y+height*3/4,0.0f);
        glVertex3f(x+width,y+height*3/4,0.0f);

        glVertex3f(x+width/4,y+height,0.0f);
        glVertex3f(x+3*width/4,y+height,0.0f);

    glEnd();
}

bool Ground::isSelected(int x, int y)
{
    if(x<this->x || x>((this->x)+(this->width)) || y<this->y || y>this->y+this->height)
    {
        return false;
    } else {
        return true;
    }
}

void Ground::setConnectorPosition()
{
    this->c1->setPosition(x+width/2,y);
}

int Ground::getHeight()
{
    return this->height;
}

int Ground::getWidth()
{
    return this->width;
}

int Ground::getY()
{
    return this->y;
}

int Ground::getX()
{
    return this->x;
}

void Ground::enablePointing()
{
    this->pointed = true;
}

void Ground::disablePointing()
{
    this->pointed = false;
}

void Ground::enableSelection()
{
    this->selected = true;
}

void Ground::disableSelection()
{
    this->selected = false;
}

Connector* Ground::connectorPointCheck(int x, int y)
{
    if(this->c1->checkPointing(x,y)) {
        return c1;
    } else {
        return NULL;
    }
}

void Ground::connect(int x, int y)
{

}

QString Ground::getName()
{
    return "ground";
}

void Ground::changeOrientation()
{

}

bool Ground::getType()
{
    //требует доработки)
    return true;
}
