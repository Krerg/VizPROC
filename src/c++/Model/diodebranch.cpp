#include "diodebranch.h"

DiodeBranch::DiodeBranch(QObject *parent) : QObject(parent)
{

}

DiodeBranch::~DiodeBranch()
{
    this->diodes = new QList<Diode*>();
    this->wires = new QList<Wire*>();
}

void DiodeBranch::open()
{
    QList<Wire*>::Iterator i;
    for(i=wires->begin();i!=wires->end();i++) {
        this->graph->value((*i))[1]=0;
    }
}

void DiodeBranch::addWire(Wire *w)
{
    this->wires->append(w);
}

void DiodeBranch::addDiode(Diode *diode)
{
    this->diodes->append(diode);
}

void DiodeBranch::setGraph(QMap<Wire *, int *> *graph)
{
    this->graph = graph;
}

bool DiodeBranch::checkBranch()
{
    if((upWire->getPotential()-downWire->getPotential())>0.6)
    {
        return true;
    } else {
        return false;
    }
}

void DiodeBranch::setUpWire(Wire *w)
{
    this->upWire = w;
}

void DiodeBranch::setDownWire(Wire *w)
{
    this->downWire = w;
}

