#include "graphhandler.h"
#include "src/c++/Util/stringvalues.h"

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
        emit error("Внутренняя ошибка");
        return;
    }

    if(elements->size()==0) {
        emit error("Пустая схема");
        return;
    }

    bool hasEmf = false;
    bool hasGround = false;
    QList<Element*>::Iterator i;
    for(i=elements->begin();i!=elements->end();i++) {
        if(handleElement((*i))) {
            emit error("Не все элементы соединены");
            return;
        }

        if((*i)->getName()==StringValues::EMF_NAME) {
            hasEmf = true;
        }

        if((*i)->getName()==StringValues::GROUND_NAME) {
            hasGround = true;
        }

    }

    if(!hasEmf) {
        emit error("Нету ЭДС");
        return;
    }

    if(!hasGround) {
        emit error("Нету заземления");
        return;
    }

    emit start();
}

