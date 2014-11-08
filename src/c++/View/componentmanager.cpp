#include "componentmanager.h"
#include <QDebug>

ComponentManager::ComponentManager(QObject *parent) :
    QObject(parent)
{
    this->elements = new QList<Element*>();
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
    Resistor* temp = new Resistor();
    temp->setPosition(x,y);
    elements->insert(elements->end(),(Element*)temp);
}
