#include "componentmanager.h"
#include <QDebug>
#include "src/c++/Elements/emf.h"
#include "src/c++/Elements/wire.h"
#include "src/c++/Elements/ground.h"
#include "src/c++/Elements/diode.h"

ComponentManager::ComponentManager(QObject *parent) :
    QObject(parent)
{
    this->elements = new QList<Element*>();
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

void ComponentManager::addDiode(int x, int y)
{
    this->leftClick=false;
    Diode *temp = new Diode(this);
    temp->setPosition(x-temp->getWidth()/2,y-temp->getHeight()/2);
    temp->setPainter(painter);
    elements->append((Element*)temp);
}

void ComponentManager::addGround(int x, int y)
{
    this->leftClick=false;
    Ground *temp = new Ground();
    temp->setPosition(x-temp->getWidth()/2,y-temp->getHeight()/2);
    this->elements->append((Element*)temp);
}

void ComponentManager::setPainter(QPainter *painter)
{
    this->painter = painter;
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
        dx = x-pointed->getX();
        dy = y-pointed->getY();
        pointed->enableSelection();
        this->selected=pointed;
    } else if(pointedWire!=NULL) {
        pointedWire->enableSelection();
        this->selectedWire = pointedWire;
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

void ComponentManager::addElement(QString elem, int x, int y)
{
    if(elem == "Резистор")  {
        this->addResistor(x,y);
    } else if(elem == "ЭДС") {
        this->addEMF(x,y);
    } else if(elem == "Провод") {
        this->connect(x,y);
    } else if(elem == "Заземление") {
        this->addGround(x,y);
    } else if(elem == "Диод") {
        this->addDiode(x,y);
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
            pointedConnector->setConnection(drawWire);
            drawingWire=true;
            //делаем 2 точки для построения провода
            this->wireEnd1 = new QPoint(pointedConnector->getX(),pointedConnector->getY());
            this->wireEnd2 = new QPoint(pointedConnector->getX(),pointedConnector->getY());
            drawWire->addPoint(wireEnd1);
            drawWire->addPoint(wireEnd2);
            this->drawType=pointed->getType();

            this->wires->insert(wires->end(),drawWire);

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
            this->drawWire==NULL;
            emit wireAdded(drawWire);
            this->drawWire=NULL;
        } else if(pointedWire!=NULL) {
            pointedWire->connectWire(drawWire,this->wirePart);
            this->drawingWire = false;
            this->wireEnd1 = NULL;
            this->wireEnd2 = NULL;
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

//поскорее бы все это закончить
