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
    this->c1->setParentElement(this);
    this->c2 = new Connector(this);
    this->c2->setParentElement(this);
    this->setConnectorPosition();
    this->conductivity = 100000;
    this->voltage = 10;
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

void EMF::enableSelection()
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

void EMF::disconnectWire(Wire *w)
{

}

void EMF::visualisation(int *container1, int *container2, QPainter *painter, int radius)
{
//    glColor3f(container1[0],container1[1],container1[2]);
//    glLineWidth(2.0f);
//    glBegin(GL_LINES);

        if(this->orientation==this->HORIZONTAL_ORIENTATION) {
            painter->setPen(QPen(QColor(container1[0],container1[1],container1[2]),2));

            painter->drawLine(x,y+height/2,x+pinLength,y+height/2);
            painter->drawLine(x+pinLength,y,x+pinLength,y+height);

            painter->setPen(QPen(QColor(container2[0],container2[1],container2[2]),2));

            painter->drawLine(x+pinLength+width/4,y+height/4,x+pinLength+width/4,y+3*height/4);
            painter->drawLine(x+pinLength+width/4,y+height/2,x+2*pinLength+width/4,y+height/2);


//            glVertex3f(x,y+height/2,0.0f);
//            glVertex3f(x+pinLength,y+height/2,0.0f);

//            glVertex3f(x+pinLength,y,0.0f);
//            glVertex3f(x+pinLength,y+height,0.0f);

//            glColor3f(container2[0],container2[1],container2[2]);
//            glVertex3f(x+pinLength+width/4,y+height/4,0.0f);
//            glVertex3f(x+pinLength+width/4,y+3*height/4,0.0f);

//            glVertex3f(x+pinLength+width/4,y+height/2,0.0f);
//            glVertex3f(x+2*pinLength+width/4,y+height/2,0.0f);
        } else {

            painter->setPen(QPen(QColor(container1[0],container1[1],container1[2]),2));

            painter->drawLine(x+height/2,y,x+height/2,y+pinLength);
            painter->drawLine(x,y+pinLength,x+height,y+pinLength);

            painter->setPen(QPen(QColor(container2[0],container2[1],container2[2]),2));

            painter->drawLine(x+height/4,y+pinLength+width/4,x+3*height/4,y+pinLength+width/4);
            painter->drawLine(x+height/2,y+pinLength+width/4,x+height/2,y+2*pinLength+width/4);

//            glVertex3f(x+height/2,y,0.0f);
//            glVertex3f(x+height/2,y+pinLength,0.0f);

//            glVertex3f(x,y+pinLength,0.0f);
//            glVertex3f(x+height,y+pinLength,0.0f);

//            glColor3f(container2[0],container2[1],container2[2]);
//            glVertex3f(x+height/4,y+pinLength+width/4,0.0f);
//            glVertex3f(x+3*height/4,y+pinLength+width/4,0.0f);

//            glVertex3f(x+height/2,y+pinLength+width/4,0.0f);
//            glVertex3f(x+height/2,y+2*pinLength+width/4,0.0f);
        }
        //glEnd();
        if(this->pointed)
        {
        //this->c1->drawComponent();
        //this->c2->drawComponent();
        }
}

Wire *EMF::getConnectedWire1()
{
    return this->c1->getConnectedWire();
}

Wire *EMF::getConnectedWire2()
{
    return this->c2->getConnectedWire();
}

Wire *EMF::getAnotherWire(Wire *w)
{
    if(this->c1->getConnectedWire()==w) {
        return c2->getConnectedWire();
    } else if(this->c2->getConnectedWire()==w) {
        return c1->getConnectedWire();
    } else {
        return NULL;
    }
}

void EMF::disableSelection()
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
    if(this->orientation == this->HORIZONTAL_ORIENTATION)
    {
        return true;
    } else {
        return false;
    }
}

QString EMF::getName()
{
    return "Emf";
}

bool EMF::isGround(Wire* w)
{
    QList<Wire*>* temp1 = this->c2->getConnectedWire()->getConnectedWires();
    QList<Wire*>* temp2 = w->getConnectedWires();
    if(temp1->size()>1)
    {
        QList<Wire*>::iterator i;
        QList<Wire*>::iterator j;
        for(i=temp1->begin();i!=temp1->end();i++)
        {
            for(j=temp2->begin();j!=temp2->end();j++)
            {
                if((*i)==(*j))
                {
                return true;
                }
            }
        }
        }
     else
     {
        if(w == this->c2->getConnectedWire())
        {
            return true;
        }
     }
    return false;
}

Wire* EMF::getAnotherWire(int number)
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

int EMF::getConductivity()
{
    return this->conductivity;
}

void EMF::setConductivity(int conductivity)
{
    this->conductivity = conductivity;
}

double EMF::getVoltage()
{
    return this->voltage;
}

void EMF::setVoltage(double voltage)
{
    this->voltage = voltage;
}

int EMF::getEmfDirection(int wireNumber)
{
    if(this->c1->getConnectedWire()->getNumber()==wireNumber) {
        return 1;
    } else if(this->c2->getConnectedWire()->getNumber()==wireNumber) {
        return -1;
    }
}

int EMF::getEmfDirection(Wire *w)
{
    if(this->c1->getConnectedWire()==w) {
        return 1;
    } else {
        return -1;
    }
}

