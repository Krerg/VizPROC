#include "emf.h"
#include <QtOpenGL/QGLWidget>

EMF::EMF(QObject *parent) :
    QObject(parent)
{
    this->x=0;
    this->y=0;
    this->height=26;
    this->width=20;
    this->pointed=false;
    this->selected=false;
    this->pinLength=6;
    this->orientation=this->HORIZONTAL_ORIENTATION;
    this->c1 = new Connector(this);
    this->c2 = new Connector(this);
    this->setConnectorPosition();
}

EMF::~EMF()
{

}

void EMF::setPosition(int x, int y)
{
    this->x=x;
    this->y=y;
    this->setConnectorPosition();
}

void EMF::setHeight(int height)
{
    this->height=height;
}

void EMF::setWidth(int width)
{
    this->width=width;
}

int EMF::getHeight()
{
    return this->height;
}

int EMF::getWidth()
{
    return this->height;
}

void EMF::connect(int x, int y)
{

}

void EMF::paintComponent()
{
    glBegin(GL_LINES);
        if(!selected) {
        glColor3f(0,0,0);
        } else {
            glColor3f(0,0,8.0f);
        }
        if(this->orientation==this->HORIZONTAL_ORIENTATION) {
            glVertex3f(x,y+height/2,0.0f);
            glVertex3f(x+pinLength,y+height/2,0.0f);

            glVertex3f(x+pinLength,y,0.0f);
            glVertex3f(x+pinLength,y+height,0.0f);

            glVertex3f(x+pinLength+width/4,y+height/4,0.0f);
            glVertex3f(x+pinLength+width/4,y+3*height/4,0.0f);

            glVertex3f(x+pinLength+width/4,y+height/2,0.0f);
            glVertex3f(x+2*pinLength+width/4,y+height/2,0.0f);
        } else {
            glVertex3f(x+height/2,y,0.0f);
            glVertex3f(x+height/2,y+pinLength,0.0f);

            glVertex3f(x,y+pinLength,0.0f);
            glVertex3f(x+height,y+pinLength,0.0f);

            glVertex3f(x+height/4,y+pinLength+width/4,0.0f);
            glVertex3f(x+3*height/4,y+pinLength+width/4,0.0f);

            glVertex3f(x+height/2,y+pinLength+width/4,0.0f);
            glVertex3f(x+height/2,y+2*pinLength+width/4,0.0f);
        }
        glEnd();
        if(this->pointed)
        {
        this->c1->drawComponent();
        this->c2->drawComponent();
        }
}

void EMF::enableSelected()
{
    this->selected=true;
}

int EMF::getX()
{
    return this->x;
}

int EMF::getY()
{
    return this->y;
}

void EMF::disableSelected()
{
    this->selected=false;
}

bool EMF::isSelected(int x, int y)
{
    if(this->orientation==this->HORIZONTAL_ORIENTATION) {
        if(x<this->x || x>((this->x)+2*pinLength+width/4) || y<this->y || y>this->y+this->height)
        {
            return false;
        } else {
            return true;
        }
    } else {
        if(x<this->x || x>((this->x)+(this->height)) || y<this->y || y>this->y+this->width+2*pinLength)
        {
            return false;
        } else {
            return true;
        }
    }
}

void EMF::changeOrientation()
{
    if(this->orientation==this->HORIZONTAL_ORIENTATION)
    {
        this->orientation=this->VERTICAL_ORIENTATION;
    } else {
        this->orientation=this->HORIZONTAL_ORIENTATION;
    }
    this->setConnectorPosition();
}

void EMF::enablePointing()
{
    this->pointed=true;
}

void EMF::disablePointing()
{
    this->pointed=false;
}

Connector* EMF::connectorPointCheck(int x, int y)
{
    if(this->c1->checkPointing(x,y))
    {
        return c1;
    } else if (this->c2->checkPointing(x,y)) {
        return c2;
    } else {
        return NULL;
    }
}


void EMF::setConnectorPosition()
{
    if(this->orientation==this->HORIZONTAL_ORIENTATION)
    {
        this->c1->setPosition(x,y+height/2);
        this->c2->setPosition(x+2*pinLength+width/4,y+height/2);
    } else {
        this->c1->setPosition(x+height/2,y);
        this->c2->setPosition(x+height/2,y+2*pinLength+width/4);
    }
}

bool EMF::getType()
{
    return false;
}
