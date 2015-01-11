#include "componentmanager.h"
#include <QDebug>
#include "src/c++/Elements/emf.h"
#include "src/c++/Elements/wire.h"

ComponentManager::ComponentManager(QObject *parent) :
    QObject(parent)
{
    this->elements = new QList<Element*>();
    this->wires = new QList<Wire*>();
    this->selected = NULL;
    this->pointed = NULL;
    this->pointedConnector = NULL;
    this->leftClick = false;
    this->drawingWire = false;
    this->wireEnd1 = NULL;
    this->wireEnd2 = NULL;
}

void ComponentManager::paintComponents()
{
    //отрисовка элементов схемы
    QList<Element*>::iterator i;
    for(int i=0;i<elements->size();i++)
    {
        elements->at(i)->paintComponent();
    }

    //отрисовка проводов
    QList<Wire*>::iterator j;
    for(int j=0;j<wires->size();j++)
    {
        wires->at(j)->paintComponent();
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
    elements->insert(elements->end(),(Element*)temp);
}

void ComponentManager::mouseClick(int x, int y)
{
    this->leftClick=true;
    if(selected!=NULL)
    this->selected->disableSelected();
    this->selected=NULL;

    Element* temp = this->getElementByCoordinates(x,y);

    if(temp!=NULL)
    {
        dx = x-temp->getX();
        dy = y-temp->getY();
        temp->enableSelected();
        this->selected=temp;
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
    for(int i=0;i<elements->size();i++)
    {
        if(elements->at(i)->isSelected(x,y))
        {
            return elements->at(i);
        }
    }
    return NULL;
}

void ComponentManager::leftClickReleased()
{
    this->leftClick=false;
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
    }
}

void ComponentManager::addElement(QString elem, int x, int y)
{
    if(elem == "Резистор")  {
        this->addResistor(x,y);
    } else if(elem == "ЭДС") {
        this->addEMF(x,y);
    } else if(elem == "Провод") {
        this->connect(x,y);
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
            drawWire->startConnection(pointedConnector);
            drawingWire=true;

            //делаем 2 точки для построения провода
            this->wireEnd1 = new QPoint(x,y);
            this->wireEnd2 = new QPoint(x,y);
            drawWire->addPoint(wireEnd1);
            drawWire->addPoint(wireEnd2);
            this->drawType=true;

            this->wires->insert(wires->end(),drawWire);
        }
    } else {
        //заверившаем отрисовку проводв
        if(pointedConnector!=NULL)
        {
            drawWire->endConnection(pointedConnector);
            this->drawingWire = false;
            this->wireEnd1 = NULL;
            this->wireEnd2 = NULL;
        } else {
            //в другом случае мы продолжаем его рисовать
            this->drawType=!this->drawType;
            this->wireEnd1=this->wireEnd2;
            this->wireEnd2 = new QPoint(x,y);
            this->drawWire->addPoint(wireEnd2);
        }
    }
    qDebug()<<"Соединение проводом";
}




//поскорее бы все это закончить
