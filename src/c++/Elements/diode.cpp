#include "diode.h"
#include <QtOpenGL/QGLWidget>
#include <QPainter>

Diode::Diode(QObject *parent) : QObject(parent)
{
    this->selected = false;
    this->pointed = false;
    this->c1 = new Connector(this);
    this->c2 = new Connector(this);
    this->c1->setParentElement(this);
    this->c2->setParentElement(this);
    this->width = 13;
    this->height = 14;
    this->pinLength = 5;
    this->orientation = this->HORIZONTAL_ORIENTATION;
    this->opened = false;
    //this->render - new QPainter();
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

            glVertex3f(x+pinLength,y,0.0f);
            glVertex3f(x+pinLength,y+height,0.0f);

            glVertex3f(x+pinLength,y+height,0.0f);
            glVertex3f(x+pinLength+width,y+height/2,0.0f);

            glVertex3f(x+pinLength,y,0.0f);
            glVertex3f(x+pinLength+width,y+height/2,0.0f);

            glVertex3f(x+pinLength+width,y+height/2,0.0f);
            glVertex3f(x+2*pinLength+width,y+height/2,0.0f);

            glVertex3f(x+pinLength,y+height/2,0.0f);
            glVertex3f(x+pinLength+width,y+height/2,0.0f);

            glVertex3f(x+pinLength+width,y,0.0f);
            glVertex3f(x+pinLength+width,y+height,0.0f);

        } else {
//            glVertex3f(x+height/2,y,0.0f);
//            glVertex3f(x+height/2,y+pinLength,0.0f);

//            glVertex3f(x+height/2,y+pinLength,0.0f);
//            glVertex3f(x+height,y+pinLength,0.0f);

//            glVertex3f(x+height,y+pinLength,0.0f);
//            glVertex3f(x+height/2,y+pinLength+width,0.0f);

//            glVertex3f(x+height/2,y+pinLength,0.0f);
//            glVertex3f(x,y+pinLength,0.0f);

//            glVertex3f(x,y+pinLength,0.0f);
//            glVertex3f(x+height/2,y+pinLength+width,0.0f);

//            glVertex3f(x+height/2,y+pinLength,0.0f);
//            glVertex3f(x+height/2,y+pinLength+width,0.0f);
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

int Diode::getWidth()
{
    return this->width;
}

int Diode::getHeight()
{
    return this->height;
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

void Diode::disconnectWire(Wire *w)
{
    //TODO
}

void Diode::setPainter(QPainter *painter)
{
    this->painter = painter;
}

void Diode::open()
{
    this->opened = true;
}

void Diode::close()
{
    this->opened = false;
}

Connector *Diode::getConnector1()
{
    return c1;
}

Connector *Diode::getConnector2()
{
    return c2;
}

Wire *Diode::getAnotherWire(int number)
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

int Diode::getEmfDirection(int wireNumber)
{
    if(this->c1->getConnectedWire()->getNumber()==wireNumber) {
        return 1;
    } else if(this->c2->getConnectedWire()->getNumber()==wireNumber) {
        return -1;
    }
}

int Diode::getConductivity()
{
    return 100000;
}

double Diode::getVoltage()
{
    return 0.6;
}

bool Diode::isOpened()
{
    return opened;
}

void Diode::visualisation(int *container1, int *container2, QPainter *painter, int radius)
{
    if(this->orientation==this->HORIZONTAL_ORIENTATION)
    {
        //glow effect
        QRadialGradient gradient;
        gradient.setCoordinateMode(QGradient::ObjectBoundingMode);
        gradient.setCenter(0.5, 0.5);
        gradient.setFocalPoint(0.5, 0.5);
        gradient.setColorAt(0.0, QColor(255, 255, 0));
        gradient.setColorAt(0.5, QColor(255, 255, 255));
        painter->setPen(Qt::NoPen);
        painter->setBrush(gradient);
        painter->drawEllipse(x+pinLength+width/2-radius/2,y+height/2-radius/2,radius,radius);

        //gradient
        QLinearGradient lg = QLinearGradient(QPointF(x+pinLength,y),QPointF(x+pinLength+width,y));
        lg.setCoordinateMode(QGradient::ObjectBoundingMode );
        lg.setSpread(QGradient::PadSpread);
        lg.setColorAt(0.0,QColor(container1[0],container1[1],container1[2]));
        lg.setColorAt(1.0,QColor(container2[0],container2[1],container2[2]));
        QBrush brush = QBrush(lg);
        painter->setBrush(brush);
        QPen p;
        p.setBrush(brush);
        p.setWidth(2);
        painter->setPen(p);
        painter->drawLine(QPointF(x,y+height/2),QPointF(x+pinLength,y+height/2)); // @1
        painter->drawLine(QPointF(x+pinLength,y),QPointF(x+pinLength,y+height));
        painter->drawLine(QPointF(x+pinLength,y),QPointF(x+pinLength+width,y)); // @1
        painter->drawLine(QPointF(x+pinLength,y+height),QPointF(x+pinLength+width,y+height));
        painter->drawLine(QPointF(x+pinLength+width,y),QPointF(x+pinLength+width,y+height));
        painter->drawLine(QPointF(x+pinLength+width,y+height/2),QPointF(x+2*pinLength+width,y+height/2));


    } else {

    }
}

Diode::~Diode()
{

}

void Diode::setConnectorPosition()
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

