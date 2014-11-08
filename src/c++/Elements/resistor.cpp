#include "resistor.h"
#include <QtOpenGL/QGLWidget>
#include "src/c++/Elements/element.h"

Resistor::Resistor(QObject *parent) :
    QObject(parent)
{
    this->x=50;
    this->y=50;
    this->height=8;
    this->width=30;
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
        glColor3f(0,0,0);

        glVertex3f(x, y, 0.0f);
        glVertex3f(x-10, y, 0.0f);

        glVertex3f(x, y, 0.0f);
        glVertex3f(x, y+height, 0.0f);

        glVertex3f(x, y+height, 0.0f);
        glVertex3f(x+width, y+height, 0.0f);

        glVertex3f(x+width, y+height, 0.0f);
        glVertex3f(x+width, y, 0.0f);

        glVertex3f(x, y, 0.0f);
        glVertex3f(x, y-height, 0.0f);

        glVertex3f(x, y-height, 0.0f);
        glVertex3f(x+width, y-height, 0.0f);

        glVertex3f(x+width, y-height, 0.0f);
        glVertex3f(x+width, y, 0.0f);

        glVertex3f(x+width, y, 0.0f);
        glVertex3f(x+40, y, 0.0f);

        glEnd();
}

