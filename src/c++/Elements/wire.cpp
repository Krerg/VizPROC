#include "wire.h"
#include <QtOpenGL/QGLWidget>
#include <math.h>
#include <QDebug>
#include <QMutex>
#include <QPainter>
#include "src/c++/Util/geometry.h"
#include <math.h>
#include "src/c++/Elements/emf.h"

Wire::Wire(QObject *parent) :
    QObject(parent)
{
    this->number = -1;
    this->path = new QList<QPoint*>;
    this->wires = new QList<Wire*>;
    this->wires->append(this);
    this->connected1 = NULL;
    this->connected2 = NULL;
    this->selected = false;
    this->pointed = false;
    this->connectedPointNumber = 0;
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

void Wire::setNumber(int number, bool root)
{
    if(this->wires->size() == 0 || !root)
    {
        this->number = number;
    }
    else if (root)
    {
        QList<Wire*>::iterator i;
        for(i=wires->begin();i!=wires->end();i++)
        {
            (*i)->setNumber(number,false);
        }
    }
}

void Wire::paintComponent()
{
    //рисуем если длина провода хотя бы больше 1
    if(this->path->size()>1) {
    QPoint *start = this->path->at(0);

    glBegin(GL_LINES);

    //если наведен провод выделен то будет отображен синим цветом
    if(!pointed && !selected) {
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

int Wire::isSelected(int x, int y)
{
    //требуется реализация
    //ну окей поехали
    int m=0;
    QList<QPoint*>::iterator i;
    for(i=path->begin(); i != path->end();)
    {
        ++m;
        QPoint* tmp1 = (*i);
        i++;
        QPoint* tmp2 = (*i);
        if(m>=path->length())
        {
            break;
        }
        if(tmp1->x() == tmp2->x())
        {
            //если 2 точки на одной линии по оси абсцисс
            if(abs(x-tmp1->x())>2 || (y>tmp1->y() && y>tmp2->y()) || (y<tmp1->y() && y<tmp2->y()))
            {
                continue;
            } else {
                return m;
            }
        } else {
            //если 2 точки на одной линии по оси ординат
            if(abs(y-tmp1->y())>2 || (x>tmp1->x() && x>tmp2->x()) || (x<tmp1->x() && x<tmp2->x()))
            {
                continue;
            } else {
                return m;
            }
        }
    }
    return 0;
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
                if(abs(second->y()-newY)<3)
                {
                    qDebug()<<"A1";
                    //двигаем 3 точку если оно нужно
                    QPoint* third = this->path->at(2);
                    if(path->size()==3) {
                        //добавляем еще одну точку если не хватает
                        QPoint* extendPoint = new QPoint();
                        extendPoint->setX(third->x());
                        extendPoint->setY(third->y());
                        path->append(extendPoint);
                    }
                    int diff = newY - oldY;
                    third->setY(newY+diff*5);
                    second->setY(newY+diff*5);
                }
                qDebug()<<"A2";
                second->setX(newX);

                temp->setX(newX);
                temp->setY(newY);
            } else {
                if(abs(second->x()-newX)<3)
                {
                    //двигаем 3 точку если вторая точка достигла её
                    QPoint* third = this->path->at(2);
                    if(path->size()==3) {
                        //добавляем еще одну точку если не хватает
                        QPoint* extendPoint = new QPoint();
                        extendPoint->setX(third->x());
                        extendPoint->setY(third->y());
                        path->append(extendPoint);
                    }
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
                if(abs(second->y()-newY)<3)
                {
                    //двигаем 3 точку если оно нужно
                    QPoint* third = this->path->at(path->size()-3);
                    if(path->size()==3) {
                        //добавляем еще одну точку если не хватает
                        QPoint* extendPoint = new QPoint();
                        extendPoint->setX(third->x());
                        extendPoint->setY(third->y());
                        path->insert(0,extendPoint);
                    }
                    int diff = newY - oldY;
                    third->setY(newY+diff*5);
                    second->setY(newY+diff*5);
                }
                second->setX(newX);

                temp->setX(newX);
                temp->setY(newY);
            } else {
                if(abs(second->x()-newX)<3)
                {
                    //двигаем 3 точку если оно нужно
                    QPoint* third = this->path->at(path->size()-3);
                    if(path->size()==3) {
                        //добавляем еще одну точку если не хватает
                        QPoint* extendPoint = new QPoint();
                        extendPoint->setX(third->x());
                        extendPoint->setY(third->y());
                        path->insert(0,extendPoint);
                    }
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

void Wire::connectWire(Wire *w, int wirePart)
{
    //добавляем провод в список проводов
    this->wires->append(w);
    //устанавливаем такой же список и на присоединяемый провод
    w->setWireList(wires);

    QPoint *tmp1 = this->path->at(--wirePart);
    QPoint *tmp2 = this->path->at(++wirePart);
    if(tmp1->x() == tmp2->x())
    {
        w->getPath()->last()->setX(tmp1->x());
    }
    else
    {
        w->getPath()->last()->setY(tmp1->y());
    }
}


void Wire::enableSelection()
{
    this->selected = true;
}

void Wire::enablePointing()
{
    this->pointed = true;
}

void Wire::disablePointing()
{
    this->pointed = false;
}

void Wire::disableSelection()
{
    this->selected = false;
}

QList<QPoint*>* Wire::getPath()
{
    return this->path;
}

QList<Wire*>* Wire::getConnectedWires()
{
    return this->wires;
}

void Wire::setWireList(QList<Wire *> *t)
{
    this->wires = t;
}

QList<Element*>* Wire::getConnectedElements()
{
    QList<Element*>* list = new QList<Element*>();
    if(this->connected1!=NULL)
    {
        list->append(this->connected1->getParentElement());
    }
    if(this->connected2!=NULL)
    {
        list->append(this->connected2->getParentElement());
    }
    return list;
}

QList<Element*>* Wire::getAllConnectedElements()
{
    QList<Element*>* list = new QList<Element*>();

    if(this->wires->size()!=0)
    {
        QList<Wire*>::iterator i;
        for(i=wires->begin();i!=wires->end();i++)
        {
            list->append(*((*i)->getConnectedElements()));
        }
    } else {
        list->append(this->connected1->getParentElement());
        list->append(this->connected2->getParentElement());
        QString name = this->connected1->getParentElement()->getName();
    }
    return list;
}

int Wire::getNumber()
{
    return this->number;
}

int Wire::isGround()
{
    QList<Element*>* list = this->getAllConnectedElements();
    QList<Element*>::iterator i;
    for(i = list->begin();i!=list->end();i++)
    {
        if((*i)->getName()=="Emf")
        {
            EMF* temp = (EMF*)(*i);
            if(temp->isGround(this))
            {
                return 1;
            } else {
                return 2;
            }
        }
    }
    return 0;
}
