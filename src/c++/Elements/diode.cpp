#include "diode.h"
#include <QtOpenGL/QGLWidget>

Diode::Diode(QObject *parent) : QObject(parent)
{
    this->selected = false;
    this->pointed = false;
    this->c1 = new Connector(this);
    this->c2 = new Connector(this);
    this->c1->setParentElement(this);
    this->c2->setParentElement(this);
}

void Diode::paintComponent()
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

            glVertex3f(x+pinLength,y+height/2,0.0f);
            glVertex3f(x+pinLength,y+height,0.0f);

            glVertex3f(x+pinLength,y+height,0.0f);
            glVertex3f(x+pinLength+width,y+height/2,0.0f);

            glVertex3f(x+pinLength,y+height/2,0.0f);
            glVertex3f(x+pinLength,y,0.0f);

            glVertex3f(x+pinLength,y,0.0f);
            glVertex3f(x+pinLength+width,y+height/2,0.0f);

            glVertex3f(x+pinLength+width,y+height/2,0.0f);
            glVertex3f(x+2*pinLength+width,y+height/2,0.0f);

            glVertex3f(x+pinLength,y+height/2,0.0f);
            glVertex3f(x+pinLength+width,y+height/2,0.0f);
        } else {
            glVertex3f(x+height/2,y,0.0f);
            glVertex3f(x+height/2,y+pinLength,0.0f);

            glVertex3f(x+height/2,y+pinLength,0.0f);
            glVertex3f(x+height,y+pinLength,0.0f);

            glVertex3f(x+height,y+pinLength,0.0f);
            glVertex3f(x+height/2,y+pinLength+width,0.0f);

            glVertex3f(x+height/2,y+pinLength,0.0f);
            glVertex3f(x,y+pinLength,0.0f);

            glVertex3f(x,y+pinLength,0.0f);
            glVertex3f(x+height/2,y+pinLength+width,0.0f);

            glVertex3f(x+height/2,y+pinLength,0.0f);
            glVertex3f(x+height/2,y+pinLength+width,0.0f);
        }
    glEnd();

    if(this->pointed)
    {
    this->c1->drawComponent();
    this->c2->drawComponent();
    }
}

void Diode::setPosition(int x, int y)
{
    this->x = x;
    this->y = y;
    setConnectorPosition();
}

void Diode::connect(int x, int y)
{

}

bool Diode::isSelected(int x, int y)
{
    if(this->orientation==this->HORIZONTAL_ORIENTATION) {
        if(x<this->x || x>((this->x)+(this->width)+2*pinLength) || y<this->y || y>this->y+this->height)
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

void Diode::enableSelection()
{
    this->selected = true;
}

void Diode::disableSelection()
{
    this->selected = false;
}

void Diode::enablePointing()
{
    this->pointed = true;
}

void Diode::disablePointing()
{
    this->pointed = false;
}

void Diode::changeOrientation()
{
    if(this->orientation==this->HORIZONTAL_ORIENTATION)
    {
        this->orientation=this->VERTICAL_ORIENTATION;
    } else {
        this->orientation=this->HORIZONTAL_ORIENTATION;
    }
    this->setConnectorPosition();
}

Connector *Diode::connectorPointCheck(int x, int y)
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

int Diode::getX()
{
    return this->x;
}

int Diode::getY()
{
    return this->y;
}

QString Diode::getName()
{
    return "Diode";
}

bool Diode::getType()
{
    if(this->orientation == this->HORIZONTAL_ORIENTATION)
    {
        return true;
    } else {
        return false;
    }
}

Diode::~Diode()
{

}

void Diode::setConnectorPosition()
{

}

