#include "componentmanager.h"
#include <QDebug>
#include "src/c++/Elements/emf.h"

ComponentManager::ComponentManager(QObject *parent) :
    QObject(parent)
{
    this->elements = new QList<Element*>();
    this->selected = NULL;
    this->leftClick = false;
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
