#include "graphhandler.h"

GraphHandler::GraphHandler(QObject *parent) : QObject(parent)
{

}

GraphHandler::~GraphHandler()
{
    this->elements = NULL;
}

void GraphHandler::setElements(QList<Element *> *elements)
{
    this->elements = elements;
}

bool GraphHandler::handleElement(Element *elem)
{
    QList<Connector*> *connectors = elem->getConnectors();
    QList<Connector*>::Iterator i;
    for(i=connectors->begin();i!=connectors->end();i++) {
        if((*i)->getConnectedWire()==NULL) {
            delete connectors;
            return true;
        }
    }
    delete connectors;
    return false;
}

void GraphHandler::handle()
{
    if(elements==NULL) {
        return;
    }
    QList<Element*>::Iterator i;
    for(i=elements->begin();i!=elements->end();i++) {
        if(handleElement((*i))) {
            emit cohesionError();
            return;
        }
    }
    emit start();
}

