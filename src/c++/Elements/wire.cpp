#include "wire.h"
#include <QtOpenGL/QGLWidget>
#include <math.h>
#include <QDebug>
#include <QMutex>
#include "src/c++/Util/geometry.h"

Wire::Wire(QObject *parent) :
    QObject(parent)
{
    this->path = new QList<QPoint*>;
    this->connected1 = NULL;
    this->connected2 = NULL;
    this->selected = false;
}

void Wire::addPoint(QPoint *point)
{
    this->path->insert(path->end(),point);
}

void Wire::addPoint(int x, int y)
{
    QPoint *temp = new QPoint(x,y);
    this->path->insert(this->path->end(),temp);
}

void Wire::setNumber(int number)
{
    this->number = number;
}

void Wire::paintComponent()
{
    //рисуем если длина провода хотя бы больше 1
    if(this->path->size()>1) {
    QPoint *start = this->path->at(0);


    glBegin(GL_LINES);

    //если наведен провод выделен то будет отображен синим цветом
    if(!selected) {
    glColor3f(0,0,0);
    } else {
        glColor3f(0,0,8.0f);
    }

    for(int i = 1;i<this->path->size();i++)
    {
         glVertex3f(start->x(),start->y(),0.0f);
         glVertex3f(path->at(i)->x(),path->at(i)->y(),0.0f);

         start = path->at(i);
    }
    glEnd();
    }
}

void Wire::startConnection(Connector *c)
{
    this->connected1=c;
    QObject::connect(c,SIGNAL(changePosition(int,int,int,int)),this,SLOT(changePosition(int,int,int,int)));
    this->path->insert(path->end(),new QPoint(c->getX(),c->getY()));
}

void Wire::endConnection(Connector *c)
{
    QObject::connect(c,SIGNAL(changePosition(int,int,int,int)),this,SLOT(changePosition(int,int,int,int)));
    this->connected2=c;
}

bool Wire::isSelected(int x, int y)
{
    //требуется реализация
    return false;
}

void Wire::changePosition(int oldX, int oldY, int newX, int newY)
{
    QMutex mut;
    mut.lock();
    if(this->path->length()>1)
    {
        QPoint* temp;
        //смотрим какая точка должна поменять положение (какая-то из боковых поэтому индекс 0 или последний)
        if(this->path->at(0)->x()==oldX && this->path->at(0)->y()==oldY)
        {
            temp = this->path->at(0);
            //берем следующую точку
            QPoint* second = this->path->at(1);
            if(second->x()==temp->x())
            {
                if(abs(second->y()-newY)<2)
                {
                    //двигаем 3 точку если оно нужно
                    QPoint* third = this->path->at(2);
                    int diff = newY - oldY;
                    third->setY(newY+diff*5);
                    second->setY(newY+diff*5);
                }
                second->setX(newX);

                temp->setX(newX);
                temp->setY(newY);
            } else {
                if(abs(second->x()-newX)<2)
                {
                    //двигаем 3 точку если оно нужно
                    QPoint* third = this->path->at(2);
                    int diff = newX - oldX;
                    third->setX(newX+diff*5);
                    second->setX(newX+diff*5);
                }
                second->setY(newY);

                temp->setX(newX);
                temp->setY(newY);
            }
        } else {
            //значит должна поменять позицию почледняя точка
            temp = this->path->last();
            //берем предпоследнюю точку
            QPoint* second = this->path->at(path->size()-2);
            if(second->x()==temp->x())
            {
                if(abs(second->y()-newY)<2)
                {
                    //двигаем 3 точку если оно нужно
                    QPoint* third = this->path->at(path->size()-3);
                    int diff = newY - oldY;
                    third->setY(newY+diff*5);
                    second->setY(newY+diff*5);
                }
                second->setX(newX);

                temp->setX(newX);
                temp->setY(newY);
            } else {
                if(abs(second->x()-newX)<2)
                {
                    //двигаем 3 точку если оно нужно
                    QPoint* third = this->path->at(path->size()-3);
                    int diff = newX - oldX;
                    third->setX(newX+diff*5);
                    second->setX(newX+diff*5);
                }
                second->setY(newY);

                temp->setX(newX);
                temp->setY(newY);
            }
        }
    }
    mut.unlock();
}
