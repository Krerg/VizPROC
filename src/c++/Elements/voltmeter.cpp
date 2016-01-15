#include "voltmeter.h"
#include "math.h"
#include <QPainter>
#include <QGLWidget>
#include <QDebug>

Voltmeter::Voltmeter(QObject *parent) : QObject(parent)
{
    this->width = 35;
    this->height = 25;
    this->upTerminal = NULL;
    this->downTerminal = NULL;
}

Voltmeter::~Voltmeter()
{

}

void Voltmeter::paintComponent()
{
    glBegin(GL_LINES);
        glColor3f(0,0,0);

        glVertex3f(x,y,0.0f);
        glVertex3f(x+width,y,0.0f);

        glVertex3f(x+width,y,0.0f);
        glVertex3f(x+width,y+height,0.0f);

        glVertex3f(x,y,0.0f);
        glVertex3f(x,y+height,0.0f);

        glVertex3f(x,y+height,0.0f);
        glVertex3f(x+width,y+height/2,0.0f);

     glEnd();

}

void Voltmeter::setUpterminal(Terminal *terminal)
{
    this->upTerminal = terminal;
}

void Voltmeter::setDownTerminal(Terminal *terminal)
{
    this->downTerminal = terminal;
}

void Voltmeter::visualisation()
{

}

void Voltmeter::setPosition(int x, int y)
{
    this->x = x;
    this->y = y;
}

void Voltmeter::connect(int x, int y)
{

}

bool Voltmeter::isSelected(int x, int y)
{
    if(x<this->x || y<this->y || x>this->x+width || y>this->y+height) {
        return false;
    } else {
        return true;
    }
}

void Voltmeter::disableSelection()
{
    this->selected = false;
}

void Voltmeter::enableSelection()
{
    this->selected = true;
}

void Voltmeter::enablePointing()
{
    this->pointed = true;
}

void Voltmeter::disablePointing()
{
    this->pointed = false;
}

void Voltmeter::changeOrientation()
{

}

Connector *Voltmeter::connectorPointCheck(int x, int y)
{
    return NULL;
}

int Voltmeter::getX()
{
    return x;
}

int Voltmeter::getY()
{
    return y;
}

bool Voltmeter::getType()
{
    return false;
}

QString Voltmeter::getName()
{
    return "Voltmeter";
}

void Voltmeter::disconnectWire(Wire *w)
{

}

void Voltmeter::paintComponent(QPainter *painter)
{
    painter->setPen(Qt::black);
    painter->setBrush(Qt::white);
    painter->drawRect(x,y,width,height);
    painter->drawText(x+25,y+16,"V");
    if(this->downTerminal==NULL || this->upTerminal == NULL) {
        painter->drawText(x+6,y+16,"0.0");
    }
    if(this->upTerminal!=NULL && this->downTerminal !=NULL) {
        upTerminal->paintComponent(painter);
        downTerminal->paintComponent(painter);

        painter->drawText(x+3,y+16,QString::number(upTerminal->getValue()-downTerminal->getValue(),'f',2));
    }
}

QList<Connector *> *Voltmeter::getConnectors()
{
    return NULL;
}
















