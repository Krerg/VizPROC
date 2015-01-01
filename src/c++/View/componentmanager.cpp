#include "componentmanager.h"
#include <QDebug>
#include "src/c++/Elements/emf.h"

ComponentManager::ComponentManager(QObject *parent) :
    QObject(parent)
{
    this->elements = new QList<Element*>();
    this->selected = NULL;
    this->pointed = NULL;
    this->pointedConnector = NULL;
    this->leftClick = false;
    this->drawingWire = false;
}
void ComponentManager::paintComponents()
{

    QList<Element*>::iterator i;
    for(int i=0;i<elements->size();i++)
    {
        elements->at(i)->paintComponent();
    }
}
void ComponentManager::addResistor(int x, int y)
{
    this->leftClick=false;
    Resistor* temp = new Resistor();
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
    if(this->pointed!=NULL)
    this->pointed->disablePointing();
    if(this->pointedConnector!=NULL)
    this->pointedConnector->disablePointing();

    Element* temp = this->getElementByCoordinates(x,y);
    if(temp!=NULL)
    {
       temp->enablePointing();
       this->pointed=temp;

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
    if(elem == "res")
    {
        this->addResistor(x,y);
    }
}

void ComponentManager::connect(int x, int y)
{


}
