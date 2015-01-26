#include "resistor.h"
#include <QtOpenGL/QGLWidget>
#include "src/c++/Elements/element.h"

Resistor::Resistor(QObject *parent) :
    QObject(parent)
{
    this->x=0;
    this->y=0;
    this->height=14;
    this->width=30;
    this->selected=false;
    this->pointed=false;
    this->pinLength=8;
    this->orientation=this->HORIZONTAL_ORIENTATION;
    this->c1 = new Connector(this);
    this->c2 = new Connector(this);
    this->c1->setParentElement(this);
    this->c2->setParentElement(this);
    this->c1->setPosition(x,y+height/2);
    this->c2->setPosition(x+width,y+height/2);
}

Element::~Element()
{

}

Resistor::~Resistor()
{

}

void Resistor::setPosition(int x, int y)
{

    this->x=x;
    this->y=y;
    this->setConnectorPosition();
}

void Resistor::setHeight(int height)
{
    this->height=height;
}

void Resistor::setWidth(int width)
{
    this->width=width;
}

int Resistor::getHeight()
{
    return this->height;
}

int Resistor::getWidth()
{
    return this->height;
}

void Resistor::connect(int x, int y)
{

}

Connector* Resistor::connectorPointCheck(int x, int y)
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

void Resistor::paintComponent()
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
        glVertex3f(x+pinLength+width,y+height,0.0f);

        glVertex3f(x+pinLength+width,y+height,0.0f);
        glVertex3f(x+pinLength+width,y+height/2,0.0f);

        glVertex3f(x+pinLength,y+height/2,0.0f);
        glVertex3f(x+pinLength,y,0.0f);

        glVertex3f(x+pinLength, y, 0.0f);
        glVertex3f(x+pinLength+width, y, 0.0f);

        glVertex3f(x+pinLength+width, y, 0.0f);
        glVertex3f(x+pinLength+width, y+height/2, 0.0f);

        glVertex3f(x+pinLength+width, y+height/2, 0.0f);
        glVertex3f(x+pinLength+width+pinLength, y+height/2, 0.0f);

        glColor3f(255,237,0); //желтый цвет

        } else {
        glVertex3f(x+height/2,y, 0.0f);
        glVertex3f(x+height/2,y+pinLength,0.0f);

        glVertex3f(x+height/2,y+pinLength,0.0f);
        glVertex3f(x,y+pinLength,0.0f);

        glVertex3f(x,y+pinLength,0.0f);
        glVertex3f(x,y+pinLength+width,0.0f);

        glVertex3f(x,y+pinLength+width,0.0f);
        glVertex3f(x+height/2,y+pinLength+width,0.0f);

        glVertex3f(x+height/2,y+pinLength,0.0f);
        glVertex3f(x+height,y+pinLength,0.0f);

        glVertex3f(x+height,y+pinLength,0.0f);
        glVertex3f(x+height,y+pinLength+width,0.0f);

        glVertex3f(x+height,y+pinLength+width,0.0f);
        glVertex3f(x+height/2,y+pinLength+width,0.0f);

        glVertex3f(x+height/2,y+pinLength+width,0.0f);
        glVertex3f(x+height/2,y+2*pinLength+width,0.0f);

        }

        glEnd();
        if(this->pointed)
        {
        this->c1->drawComponent();
        this->c2->drawComponent();
        }
}

void Resistor::enableSelected()
{
    this->selected=true;
}

void Resistor::enablePointing()
{
    this->pointed=true;
}

int Resistor::getX()
{
    return this->x;
}

int Resistor::getY()
{
    return this->y;
}

void Resistor::disableSelected()
{
    this->selected=false;
}

void Resistor::disablePointing()
{
    this->pointed=false;
}


bool Resistor::isSelected(int x, int y)
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

void Resistor::changeOrientation()
{
    if(this->orientation==this->HORIZONTAL_ORIENTATION)
    {
        this->orientation=this->VERTICAL_ORIENTATION;
    } else {
        this->orientation=this->HORIZONTAL_ORIENTATION;

    }
    this->setConnectorPosition();
}

void Resistor::setConnectorPosition()
{
    if(this->orientation==this->HORIZONTAL_ORIENTATION)
    {
        this->c1->setPosition(x,y+height/2);
        this->c2->setPosition(x+width+2*pinLength,y+height/2);
    } else {
        this->c1->setPosition(x+height/2,y);
        this->c2->setPosition(x+height/2,y+2*pinLength+width);
      }
}

bool Resistor::getType()
{
    if(this->orientation == this->HORIZONTAL_ORIENTATION)
    {
        return true;
    } else {
        return false;
    }
}

QString Resistor::getName()
{
    return this->name;
}

int Resistor::getValue()
{
    return 1;
}

Connector* Resistor::getAnotherConnector(Connector *c)
{
    if(c == this->c1)
    {
        return c2;
    }
    else if(c == this->c2)
    {
        return c1;
    } else {
        return NULL;
    }
}

Wire* Resistor::getAnotherWire(int number)
{
    if(number == this->c1->getConnectedWire()->getNumber())
    {
        return c2->getConnectedWire();
    }
    else if(number == this->c2->getConnectedWire()->getNumber())
    {
        return c1->getConnectedWire();
    } else {
        return NULL;
    }
}
