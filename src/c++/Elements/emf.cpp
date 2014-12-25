#include "emf.h"
#include <QtOpenGL/QGLWidget>

EMF::EMF(QObject *parent) :
    QObject(parent)
{
    this->x=0;
    this->y=0;
    this->height=26;
    this->width=20;
    this->selected=false;
    this->pinLength=6;
    this->orientation=this->HORIZONTAL_ORIENTATION;
}



EMF::~EMF()
{

}

void EMF::setPosition(int x, int y)
{
    this->x=x;
    this->y=y;
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

            glVertex3f(x+pinLength+width/4,y,0.0f);
            glVertex3f(x+pinLength+width/4,y+height,0.0f);

            glVertex3f(x+pinLength+width/4,y+height/2,0.0f);
            glVertex3f(x+2*pinLength+width/4,y+height/2,0.0f);
        }
        glEnd();
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

}

void EMF::changeOrientation()
{
    if(this->orientation==this->HORIZONTAL_ORIENTATION)
    {
        this->orientation=this->VERTICAL_ORIENTATION;
    } else {
        this->orientation=this->HORIZONTAL_ORIENTATION;
    }
}

