#include "graph.h"

Graph::Graph(QObject *parent) :
    QObject(parent)
{
    this->lastFreeNumber = 0;
    this->graph = new QList<Wire*>();
}

void Graph::addVertex(Wire *w)
{
    if(w->getConnectedWires()->size()==0)
    {
        /*
         * Добавлем в граф только те провода, который не присоединены к дургим,
         * то есть который образуют новый потенциал
         *
         */
        this->graph->append(w);
    }
}

void Graph::deleteVertex(Wire *w)
{

}

int Graph::getNewNumber()
{
    return lastFreeNumber++;
}

void Graph::start()
{

}
