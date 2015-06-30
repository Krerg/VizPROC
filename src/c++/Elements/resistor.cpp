#include <QDebug>
#include "resistor.h"
#include <QtOpenGL/QGLWidget>
#include "src/c++/Elements/element.h"
#include <QLinearGradient>

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
    this->resistance = 1;
}

Resistor::~Resistor()
{
    qDebug()<<"Bye resistor";
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

void Resistor::enableSelection()
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

void Resistor::disconnectWire(Wire *w)
{
    if(c1->getConnectedWire()==w) {

    } else if(c2->getConnectedWire()==w) {

    }
}

void Resistor::disableSelection()
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

QList<Connector *> *Resistor::getConnectors()
{
    QList<Connector*>* connectors = new QList<Connector*>();
    connectors->append(c1);
    connectors->append(c2);
    return connectors;
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

void Resistor::setResistance(double resistance)
{
    this->resistance = resistance;
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

void Resistor::visualisation(int *container1, int *container2, QPainter *painter, int radius)
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
        QLinearGradient lg = QLinearGradient(QPointF(x,y+pinLength),QPointF(x,y+pinLength+width));
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
        painter->drawLine(QPointF(x+height/2,y),QPointF(x+height/2,y+pinLength)); // @1
        painter->drawLine(QPointF(x,y+pinLength),QPointF(x+height,y+pinLength));
        painter->drawLine(QPointF(x,y+pinLength),QPointF(x,y+pinLength+width)); // @1
        painter->drawLine(QPointF(x+height,y+pinLength),QPointF(x+height,y+pinLength+width));
        painter->drawLine(QPointF(x,y+width+pinLength),QPointF(x+height,y+width+pinLength));
        painter->drawLine(QPointF(x+height/2,y+width+pinLength),QPointF(x+height/2,y+width+2*pinLength));
    }
}

Wire *Resistor::getConnectedWire1()
{
    return this->c1->getConnectedWire();
}

Wire *Resistor::getConnectedWire2()
{
    return this->c2->getConnectedWire();
}

Wire *Resistor::getAnotherWire(Wire *w)
{
    if(this->c1->getConnectedWire()==w) {
        return c2->getConnectedWire();
    } else if(this->c2->getConnectedWire()==w) {
        return c1->getConnectedWire();
    } else {
        return NULL;
    }
}

double Resistor::getValue()
{
    return (double)1/resistance;
}

double Resistor::getResistance()
{
    return resistance;
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
