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
    this->pinLength=8;
    this->orientation=this->HORIZONTAL_ORIENTATION;
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
        } else {

        }
        glEnd();

}

void Resistor::enableSelected()
{
    this->selected=true;
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

bool Resistor::isSelected(int x, int y)
{
    if(x<this->x-pinLength || x>((this->x)+(this->width)+pinLength) || y<this->y-this->height/2 || y>this->y+this->height/2)
    {
        return false;
    } else {
        return true;
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
}
