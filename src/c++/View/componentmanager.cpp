#include "componentmanager.h"
#include <QDebug>
#include "src/c++/Elements/emf.h"
#include "src/c++/Elements/wire.h"
#include "src/c++/Elements/ground.h"
#include "src/c++/Elements/amperemeter.h"
#include "src/c++/Elements/voltmeter.h"
#include "src/c++/Elements/terminal.h"

ComponentManager::ComponentManager(QObject *parent) :
    QObject(parent)
{
    this->elements = new QList<Element*>();
    this->meters = new QList<Element*>();
    this->wires = new QList<Wire*>();
    this->selected = NULL;
    this->pointed = NULL;
    this->pointedConnector = NULL;
    this->pointedWire = NULL;
    this->selectedWire = NULL;
    this->leftClick = false;
    this->drawingWire = false;
    this->wireEnd1 = NULL;
    this->wireEnd2 = NULL;
    this->ground = NULL;
}

void ComponentManager::paintComponents()
{
    //отрисовка элементов схемы
    QList<Element*>::iterator i;
    for(i=elements->begin();i!=elements->end();i++)
    {
        if(deleteMutex) {
            break;
        }
        (*i)->paintComponent();
    }

    //отрисовка проводов
    QList<Wire*>::iterator j;
    for(j=wires->begin();j!=wires->end();j++)
    {
        (*j)->paintComponent();
    }

    //отрисовка зазелмения, если оно есть
    if(this->ground!=NULL)
    {
        this->ground->paintComponent();
    }
}

void ComponentManager::paintMeters(QPainter *painter)
{
    QList<Element*>::iterator i;
    for(i=meters->begin();i!=meters->end();i++)
    {
        if((*i)->getName() == "Amper") {
            ((Amperemeter*)(*i))->paintComponent(painter);
        } else if((*i)->getName() == "Voltmeter") {
            ((Voltmeter*)(*i))->paintComponent(painter);
        }
    }
}

void ComponentManager::addResistor(int x, int y)
{
    this->leftClick=false;
    Resistor* temp = new Resistor(this);
    temp->setPosition(x-temp->getWidth()/2,y-temp->getHeight()/2);
    elements->insert(elements->end(),(Element*)temp);
}

void ComponentManager::addEMF(int x, int y)
{
    this->leftClick=false;
    EMF *temp = new EMF(this);
    temp->setPosition(x-temp->getWidth()/2,y-temp->getHeight()/2);
    elements->append((Element*)temp);
}

void ComponentManager::addDiode(int x, int y)
{
    this->leftClick=false;
    Diode *temp = new Diode(this);
    temp->setPosition(x-temp->getWidth()/2,y-temp->getHeight()/2);
    temp->setPainter(painter);
    elements->append((Element*)temp);
    emit addedDiode(temp);
}

void ComponentManager::addDiode(Diode *d)
{
    elements->insert(elements->end(),(Element*)d);
    emit addedDiode(d);
}

void ComponentManager::addGround(int x, int y)
{
    this->leftClick=false;
    Ground *temp = new Ground();
    temp->setPosition(x-temp->getWidth()/2,y-temp->getHeight()/2);
    this->elements->append((Element*)temp);
}

void ComponentManager::addAmperemeter(int x, int y)
{
    this->leftClick = false;
    Amperemeter* temp = new Amperemeter();
    temp->setPosition(x,y);
    this->meters->append((Element*)temp);
}

void ComponentManager::addVoltmeter(int x, int y)
{
    this->leftClick = false;
    Voltmeter* voltmeter = new Voltmeter();
    Terminal* upTerminal = new Terminal();
    Terminal* downTerminal = new Terminal();
    voltmeter->setDownTerminal(downTerminal);
    voltmeter->setUpterminal(upTerminal);
    voltmeter->setPosition(x,y);
    upTerminal->setPosition(x-20,y);
    downTerminal->setPosition(x+30,y);
    upTerminal->setColor(QColor("Red"));
    downTerminal->setColor(QColor("Blue"));
    this->meters->append((Element*)voltmeter);
    this->meters->append((Element*)upTerminal);
    this->meters->append((Element*)downTerminal);
}

void ComponentManager::setPainter(QPainter *painter)
{
    this->painter = painter;
}

void ComponentManager::addResistor(Resistor *res)
{
    elements->insert(elements->end(),(Element*)res);
}

void ComponentManager::addEMF(EMF *emf)
{
    elements->insert(elements->end(),(Element*)emf);
}

void ComponentManager::addGround(Ground *ground)
{
    elements->insert(elements->end(),(Element*)ground);
}

void ComponentManager::mouseClick(int x, int y)
{
    this->leftClick=true;
    if(selected!=NULL)
    {
        this->selected->disableSelection();
        this->selected = NULL;
    }

    if(selectedWire!=NULL)
    {
        this->selectedWire->disableSelection();
        this->selectedWire = NULL;
    }

    if(pointed!=NULL)
    {
        if(pointed->getName()=="Amper") {
            ((Amperemeter*)pointed)->setWire(NULL);
        }
        dx = x-pointed->getX();
        dy = y-pointed->getY();
        pointed->enableSelection();
        this->selected=pointed;
        //говорим о том, что надо бы открыть окошко для параметров :)
        emit onElementClick(selected);
    } else if(pointedWire!=NULL) {
        pointedWire->enableSelection();
        this->selectedWire = pointedWire;
        emit onWireClick(selectedWire);
   }
}

void ComponentManager::moveElement(int x, int y)
{
    if(selected!=NULL && leftClick)
    {
        selected->setPosition(x-dx,y-dy);
    }
}

Element* ComponentManager::getElementByCoordinates(int x, int y)
{
    QList<Element*>::iterator i;
    for(i=elements->begin();i!=elements->end();i++)
    {
        if(deleteMutex) {
            break;
        }
        try {
        if((*i)!=NULL && (*i)->isSelected(x,y))
            return (*i);
        } catch(...) {
            continue;
        }
    }
    for(i=meters->begin();i!=meters->end();i++) {
        if((*i)->isSelected(x,y)) {
            return (*i);
        }
    }

    return NULL;
}

void ComponentManager::deleteItem()
{
    if(selected!=NULL) {
        deleteMutex = true;
        QList<Element*>::Iterator i;
        int elemIndex=0;
        for(i=elements->begin();i!=elements->end();i++) {
            if((*i)==selected) {
                delete (*i);
                elements->removeAt(elemIndex);
                break;
            }
            elemIndex++;
        }
        this->pointed = NULL;
        this->selected = NULL;
    } else if(selectedWire!=NULL) {
        QList<Wire*>* deleteWires = selectedWire->getConnectedWires();
        QList<Wire*>::Iterator i;
        for(i=deleteWires->begin();i!=deleteWires->end();i++) {
            wires->removeAll((*i));
            emit deleteWire((*i));
            (*i)->clear();
            delete (*i);
        }
        delete deleteWires;
    }
    emit elementDeleted();
    deleteMutex=false;
}

void ComponentManager::leftClickReleased()
{
    if(selected!=NULL && selected->getName()=="Amper") {
        QList<Wire*>::iterator j;
        for(j=wires->begin();j!=wires->end();j++)
        {
           if((this->wirePart=(*j)->isSelected(selected->getX()+10,selected->getY()+10))>0)
           {
              ((Amperemeter*)selected)->setWire((*j));
           }
        }
    } else if(selected!=NULL && selected->getName()=="Terminal") {
        QList<Wire*>::iterator j;
        for(j=wires->begin();j!=wires->end();j++)
        {
           if((this->wirePart=(*j)->isSelected(selected->getX()+10,selected->getY()+10))>0)
           {
              ((Terminal*)selected)->setConnectedWire((*j));
               this->leftClick=false;
               return;
           }
        }
        ((Terminal*)(selected))->setConnectedWire(NULL);
    }
    this->leftClick=false;
}

void ComponentManager::addWire(Wire *w)
{
    QObject::connect(w,SIGNAL(addWire(Wire*)),this,SLOT(addWire(Wire*)));
    this->wires->append(w);
    emit wireAdded(w);
}

void ComponentManager::changeOrientation(int x, int y)
{
    if(selected!=NULL)
    {
        selected->changeOrientation();
    }
}

void ComponentManager::mouseMoved(int x, int y)
{
    //снимаем выделение с выделенного элемента если оно есть
    if(this->pointed!=NULL)
    {
        this->pointed->disablePointing();
        this->pointed = NULL;
    }

    //снимаем выделение с выделенного коннектора если оно есть
    if(this->pointedConnector!=NULL)
    {
        this->pointedConnector->disablePointing();
        this->pointedConnector = NULL;
    }

    if(this->pointedWire!=NULL)
    {
        this->pointedWire->disablePointing();
        this->pointedWire = NULL;
    }

    //если в данный момент мы риисуем провод
    if(this->drawingWire)
    {
       if(drawType)
       {
            wireEnd1->setX(x);

            wireEnd2->setX(x);
            wireEnd2->setY(y);

       } else {
           wireEnd1->setY(y);

           wireEnd2->setX(x);
           wireEnd2->setY(y);
       }
    }

    //достаем элемент по координатам и если такой есть делаем на нем выделение
    Element* temp = this->getElementByCoordinates(x,y);
    if(temp!=NULL)
    {
       temp->enablePointing();
       this->pointed=temp;

       //проверяем не находится ли курсор на коннекторе
       Connector* temp2 = temp->connectorPointCheck(x,y);
       if(temp2!=NULL)
       {
           temp2->enablePointing();
           this->pointedConnector=temp2;
       }


    } else  {
         //проверяем провода
         QList<Wire*>::iterator j;
         for(j=wires->begin();j!=wires->end();j++)
         {
            if((*j)!=drawWire && (this->wirePart=(*j)->isSelected(x,y))>0)
            {
                this->pointedWire = (*j);
                (*j)->enablePointing();
                break;
            }
         }
    }
}

void ComponentManager::addElement(int elemType, int x, int y)
{
    switch (elemType) {
    case 0:
        this->addResistor(x,y);
        break;
    case 1:
        this->addEMF(x,y);
        break;
    case 2:
        this->addDiode(x,y);
        break;
    case 3:
        this->addGround(x,y);
        break;
    case 4:
        this->connect(x,y);
        break;
    case 5:
        this->addAmperemeter(x,y);
        break;
    case 6:
        this->addVoltmeter(x,y);
        break;
    default:
        break;
    }
}

void ComponentManager::connect(int x, int y)
{
    //если в данный момент мы только начали рисовать провод
    if(!drawingWire)
    {
        //если мы наведены на коннектор в данный момент
        if(pointedConnector!=NULL)
        {
            drawWire = new Wire(this);

            drawWire->getPath()->append(new QPoint(pointedConnector->getX(),pointedConnector->getY()));
            pointedConnector->setConnection(drawWire);
            drawingWire=true;
            //делаем 2 точки для построения провода
            this->wireEnd1 = new QPoint(pointedConnector->getX(),pointedConnector->getY());
            this->wireEnd2 = new QPoint(pointedConnector->getX(),pointedConnector->getY());
            drawWire->addPoint(wireEnd1);
            drawWire->addPoint(wireEnd2);
            drawWire->startConnection(pointedConnector);
            this->drawType=pointed->getType();
            this->wires->append(drawWire);
            QObject::connect(drawWire,SIGNAL(addWire(Wire*)),this,SLOT(addWire(Wire*)));

        }
    } else {
        //заверившаем отрисовку провода
        if(pointedConnector!=NULL)
        {
            drawWire->endConnection(pointedConnector);
            pointedConnector->setConnection(drawWire);
            this->drawingWire = false;
            this->wireEnd1 = NULL;
            this->wireEnd2 = NULL;
            emit wireAdded(drawWire);
            this->drawWire=NULL;
            this->pointed = NULL;
            this->pointedConnector = NULL;
            this->selected = NULL;
            this->selectedWire = NULL;
        } else if(pointedWire!=NULL) {
            pointedWire->connectWire(drawWire,this->wirePart);
            this->drawingWire = false;
            this->wireEnd1 = NULL;
            this->wireEnd2 = NULL;
            emit wireAdded(drawWire);
            this->drawWire = NULL;
        } else {
            //в другом случае мы продолжаем его рисовать
            this->drawType=!this->drawType;
            this->wireEnd1=this->wireEnd2;
            this->wireEnd2 = new QPoint(x,y);
            this->drawWire->addPoint(wireEnd2);
        }
    }
}

QList<Element *>* ComponentManager::getElements()
{
    return this->elements;
}

QList<Element *> *ComponentManager::getMeters()
{
    return this->meters;
}

QList<Wire *>* ComponentManager::getWires()
{
    return this->wires;
}

//поскорее бы все это закончить
