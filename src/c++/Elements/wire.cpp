#include "wire.h"
#include <QtOpenGL/QGLWidget>
#include <math.h>
#include <QDebug>
#include <QMutex>
#include <QPainter>
#include "src/c++/Util/geometry.h"
#include <math.h>
#include "src/c++/Elements/emf.h"
#include "src/c++/Elements/resistor.h"
#include "src/c++/Elements/wireconnector.h"
#include "src/c++/Util/constvalues.h"
#include "src/c++/Util/stringvalues.h"

Wire::Wire(QObject *parent) :
    QObject(parent)
{
    this->number = -2;
    this->path = new QList<QPoint*>;
    this->wires = new QList<Wire*>;
    this->particleList = new QList<Particle*>;
    this->wires->append(this);
    this->connected1 = NULL;
    this->connected2 = NULL;
    this->selected = false;
    this->pointed = false;
    this->connectedPointNumber = 0;
    this->lastStep = 0;
    this->speed = 0;
    this->potential = 0.0;
    this->wireConnector = NULL;
    this->savedFlag = false;
    this->opened = true;
    this->amperage = ConstValues::BRANCH_AMPERAGE_UNKNOWN;
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
    if(this->path==NULL) {
        return;
    }
    //рисуем если длина провода хотя бы больше 1
    if(this->path->size()>1) {
        QPoint *start = this->path->at(0);
        //glLineWidth(2.0f);
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
        //glLineWidth(1.0f);
        glEnd();

        if(this->wireConnector!=NULL) {
            wireConnector->paintComponent();
        }
    }
}

void Wire::visualisation(int *color, QPainter* painter)
{
    if(this->path==NULL) {
        return;
    }
    painter->setPen(QPen(QColor(color[0],color[1],color[2]),2));
    QPoint *start = this->path->at(0);
    for(int i=1;i<path->size();i++) {
        painter->drawLine(*start,*path->at(i));
        start = path->at(i);
    }
    if(opened) {
        QList<Particle*>::iterator j;
        for(j=particleList->begin();j!=particleList->end();j++) {
            (*j)->visualisation(painter);
        }
    }
    if(this->wireConnector!=NULL) {
        wireConnector->paintComponent();
    }
}

void Wire::startConnection(Connector *c)
{
    this->connected1=c;
    this->path->first()->setX(c->getX());
    this->path->first()->setY(c->getY());
    c->setConnection(this);
    //QObject::connect(c,SIGNAL(changePosition(int,int,int,int)),this,SLOT(changePosition(int,int,int,int)));
}

void Wire::endConnection(Connector *c)
{
    //QObject::connect(c,SIGNAL(changePosition(int,int,int,int)),this,SLOT(changePosition(int,int,int,int)));
    this->path->last()->setX(c->getX());
    this->path->last()->setY(c->getY());
    this->connected2=c;
    c->setConnection(this);
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
    if(this->path->length()>1)
    {
        QPoint* first;
        //смотрим какая точка должна поменять положение (какая-то из боковых поэтому индекс 0 или последний)
        if(this->path->at(0)->x()==oldX && this->path->at(0)->y()==oldY)
        {

            first = this->path->at(0);
            //берем следующую точку
            QPoint* second = this->path->at(1);
            QPoint* third = this->path->at(2);
            if(second->x()==first->x() && second->y()==first->y() && third->y()==second->y() && third->x()!=second->x())
            {
                second->setX(newX);
                first->setX(newX);
                first->setY(newY);
                return;
            }

            if(second->x()==first->x() && second->y()==first->y() && third->x()==second->x() && third->y()!=second->y())
            {
                second->setY(newY);
                first->setX(newX);
                first->setY(newY);
                return;
            }

            if(second->x()==first->x())
            {
                second->setX(newX);
                first->setX(newX);
                first->setY(newY);
            } else {
                second->setY(newY);
                first->setX(newX);
                first->setY(newY);
            }
        } else {
            //значит должна поменять позицию последняя точка
            first = this->path->last();
            //берем предпоследнюю точку
            QPoint* second = this->path->at(path->size()-2);
            QPoint* third = this->path->at(path->size()-3);

            if(second->x()==first->x() && second->y()==first->y() && third->y()==second->y() && third->x()!=second->x())
            {
                second->setX(newX);
                first->setX(newX);
                first->setY(newY);
                return;
            }

            if(second->x()==first->x() && second->y()==first->y() && third->x()==second->x() && third->y()!=second->y())
            {
                second->setY(newY);
                first->setX(newX);
                first->setY(newY);
                return;
            }

            if(second->x()==first->x())
            {
                second->setX(newX);
                first->setX(newX);
                first->setY(newY);
            } else {
                second->setY(newY);
                first->setX(newX);
                first->setY(newY);
            }
        }
    }
}

void Wire::connectWire(Wire *w, int wirePart)
{
    //добавляем провод в список проводов
    this->wires->append(w);
    //устанавливаем такой же список и на присоединяемый провод
    delete w->getConnectedWires();
    w->setWireList(wires);
    QPoint* last = w->getPath()->last();
    QPoint* beforeLast = w->getPath()->at(w->getPath()->size()-2);

        //присоединяем в ближайшей точке
    QPoint *tmp1 = this->path->at(--wirePart);
    QPoint *tmp2 = this->path->at(++wirePart);

    //делим провод на 2
    Wire* secondWire = new Wire();
    int index=0;
    if(abs(tmp1->x()-last->x())+abs(tmp1->y()-last->y())<10) {
         if(last->x()==beforeLast->x()) {
                last->setX(tmp1->x());
                last->setY(tmp1->y());
                beforeLast->setX(tmp1->x());
                index = wirePart-1;
            } else {
                last->setX(tmp1->x());
                last->setY(tmp1->y());
                beforeLast->setY(tmp1->y());
                index = wirePart-1;
            }
        } else if (abs(tmp2->x()-last->x())+abs(tmp2->y()-last->y())<10){
            index = wirePart;
            if(last->x()==beforeLast->x()) {
                last->setX(tmp2->x());
                last->setY(tmp2->y());
                beforeLast->setX(tmp2->x());
            } else {
                last->setX(tmp2->x());
                last->setY(tmp2->y());
                beforeLast->setY(tmp2->y());
            }
        } else {
            //если нету ближайшей точки, то присоединяем так
            if(tmp1->x()==tmp2->x()) {
                last->setX(tmp1->x());
            } else if(tmp1->y()==tmp2->y()) {
                last->setY(tmp1->y());
            } else {
                //emmit error
            }
            index = wirePart;
            secondWire->addPoint(new QPoint(last->x(),last->y()));
        }


    if(this->wireConnector!=NULL) {
        secondWire->setWireConnector(this->wireConnector);
    }

    //надо добавить в список отрисовываемых объектов
    this->wireConnector = new WireConnector(last->x(),last->y());

    for(int i=index;i!=this->path->size();i++) {
        QPoint *point = path->at(i);
        secondWire->addPoint(point);
    }

    if(connected2!=NULL) {
        secondWire->endConnection(this->connected2);
        //вот это поворот
        this->connected2=NULL;
    }

    int count = this->path->size()-index;

    for(int i=0;i<(count);i++) {
        this->path->removeLast();
    }
    this->path->append(new QPoint(last->x(),last->y()));

    this->wires->append(secondWire);
    secondWire->setWireList(wires);

    emit addWire(secondWire);
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

void Wire::setWireConnector(WireConnector *wireConnector)
{
    this->wireConnector = wireConnector;
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

bool Wire::isGround()
{
    QList<Element*>* list = this->getAllConnectedElements();
    QList<Element*>::iterator i;
    for(i = list->begin();i!=list->end();i++)
    {
        if((*i)->getName()=="Ground")
        {
            delete list;
            return true;
        }
    }
    delete list;
    return false;
}

void Wire::setPotential(double potential)
{
    this->potential = potential;
}

double Wire::getPotential()
{
    return this->potential;
}

void Wire::initParticles()
{
    if(this->connected1!=NULL && this->connected1->getParentElement()->getName()=="Ground" || !opened) {
        return;
    }
    //вот это надор убрать по-хорошему
    QList<Particle*>::iterator t;
    for(t=particleList->begin();t!=particleList->end();t++) {
        delete (*t);
    }
    particleList->clear();


    int dist = 6;
    QPoint* start = path->at(0);
    QPoint* next = path->at(1);
    int currentX;
    int currentY;
    int d;
    int xDir=next->x()-start->x();
    if(xDir!=0)
    xDir/=abs(xDir);
    int yDir=next->y()-start->y();
    if(yDir!=0)
    yDir/=abs(yDir);
    if(speed>0) {
        lastStep%=dist;
        currentX = start->x()+lastStep*xDir;
        currentY = start->y()+lastStep*yDir;
    } else {
        if(lastStep<0)
            lastStep+=dist;

        currentX = start->x()+lastStep*xDir;
        currentY = start->y()+lastStep*yDir;

    }
    int newX;
    int newY;

    int i=2;
    while(true) {
        Particle* tmp = new Particle();
        particleList->append(tmp);
        tmp->setPosition(currentX,currentY);
        xDir=next->x()-start->x();
        if(xDir!=0)
        xDir/=abs(xDir);
        yDir=next->y()-start->y();
        if(yDir!=0)
        yDir/=abs(yDir);
        newX = currentX+dist*xDir;
        newY = currentY+dist*yDir;
        if(((next->x()-currentX)*(next->x()-newX)<0)||((next->y()-currentY)*(next->y()-newY)<0)||(next->x()==currentX&&next->y()==currentY)) {
            if(path->last()==next) {
                break;
            }

            int dx = abs(next->x()-newX);
            int dy = abs(next->y()-newY);
            start = next;
            next = path->at(i);
            i++;
            if(next->x()==start->x()&&next->y()==start->y()) {
                next = path->at(i);
                i++;
            }

            xDir=next->x()-start->x();
            if(xDir!=0)
            xDir/=abs(xDir);
            yDir=next->y()-start->y();
            if(yDir!=0)
            yDir/=abs(yDir);
            d = dx+dy;
            currentX=start->x()+d*xDir;
            currentY=start->y()+d*yDir;
        } else {
          currentX = newX;
          currentY = newY;
        }
    }
    lastStep+=speed;
}

int Wire::initSpeed()
{
    if(this->speed!=0) {
        return this->speed;
    }

    if(this->connected1!=NULL && this->connected1->getParentElement()->getName()=="Ground") {
        setSpeed(0);
        return 0;
    }

    if(this->connected1!=NULL) {
        if(connected1->getParentElement()->getName()=="Res") {
            Resistor* resTemp = (Resistor*)connected1->getParentElement();
            double tmpPotential = resTemp->getAnotherWire(this)->getPotential();
            if(tmpPotential>this->potential) {
                double i = abs(tmpPotential-this->potential)*resTemp->getValue();
                //i%=10;
                this->setSpeed((int)i);
                return i;
            } else {
                double i = abs(tmpPotential-this->potential)*resTemp->getValue();
                //i%=10;
                this->setSpeed((int)-i);
                return i;
            }
        } else if (connected1->getParentElement()->getName()=="Emf") {
            if(this->connected2==NULL) {
                EMF* emfTemp = (EMF*)connected1->getParentElement();
                int direction = emfTemp->getEmfDirection(this);
                QList<Wire*>::Iterator i;
                for(i=this->wires->begin();i!=wires->end();i++) {
                    if((*i)==this) {
                        continue;
                    }
                    this->speed+=(*i)->initSpeed();
                }
                this->speed*direction;
                return speed;
            }
    }
    }
        if(this->connected2!=NULL) {
            if(connected2->getParentElement()->getName()=="Res") {
                Resistor* resTemp = (Resistor*)connected2->getParentElement();
                double tmpPotential = resTemp->getAnotherWire(this)->getPotential();
                if(tmpPotential>this->potential) {
                    double i = abs(tmpPotential-this->potential)*resTemp->getValue();
                    //i%=10;
                    this->setSpeed((int)-i);
                    return i;
                } else {
                    double i = abs(tmpPotential-this->potential)*resTemp->getValue();
                    //i%=10;
                    this->setSpeed((int)i);
                    return i;
                }

           } else if (connected2->getParentElement()->getName()=="Emf") {
                if(this->connected1==NULL) {
                    EMF* emfTemp = (EMF*)connected2->getParentElement();
                    int direction = emfTemp->getEmfDirection(this);
                    QList<Wire*>::Iterator i;
                    for(i=this->wires->begin();i!=wires->end();i++) {
                        if((*i)==this) {
                            continue;
                        }
                        this->speed+=(*i)->initSpeed();
                    }
                    this->speed*direction;

                    return speed;
                }
        }
    }
}

void Wire::setSpeed(int speed)
{
    this->speed = speed;
}

int Wire::getSpeed()
{
    return speed;
}

bool Wire::groundConnected()
{
    if(this->getConneted1()!=NULL && this->getConneted1()->getParentElement()->getName()==StringValues::GROUND_NAME) {
        return true;
    } else if (this->getConneted2()!=NULL && this->getConneted2()->getParentElement()->getName()==StringValues::GROUND_NAME) {
        return true;
    }
    return false;
}

void Wire::removeConnector(Connector *c)
{
    if(this->connected1 == c) {
        connected1 = NULL;
    } else if(this->connected2 == c) {
        connected2 = NULL;
    }
}

WireConnector* Wire::getWireConnector()
{
    return this->wireConnector;
}

Connector *Wire::getConneted1()
{
    return this->connected1;
}

Connector *Wire::getConneted2()
{
    return this->connected2;
}

bool Wire::isOpened()
{
    return opened;
}

bool Wire::isSaved()
{
    return savedFlag;
}

void Wire::setSavedFlag()
{
    savedFlag = true;
}

void Wire::resetSavingFlag()
{
    this->savedFlag = false;
}

void Wire::clear()
{
    if(this->connected1!=NULL) {
        connected1->setConnection(NULL);
        this->connected1=NULL;
    }
    if(this->connected2!=NULL) {
        connected2->setConnection(NULL);
        this->connected2=NULL;
    }
    delete this->path;
    this->path=NULL;
    if(this->wireConnector!=NULL) {
        delete wireConnector;
    }
    if(this->particleList!=NULL) {
        delete particleList;
    }
}

void Wire::close()
{
    this->opened = false;
}

void Wire::open()
{
    this->opened = true;
}
double Wire::getAmperage() const
{
    return amperage;
}

void Wire::setAmperage(double value)
{
    amperage = value;
}

