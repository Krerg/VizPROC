#include "diodebranch.h"

DiodeBranch::DiodeBranch(QObject *parent) : QObject(parent)
{
    this->diodes = new QList<Diode*>();
    this->wires = new QList<Wire*>();
}

DiodeBranch::~DiodeBranch()
{

}

void DiodeBranch::open()
{
    QList<Diode*>::iterator j;
    for(j=diodes->begin();j!=diodes->end();j++) {
        (*j)->open();
    }
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

bool DiodeBranch::checkBranch(double* array)
{
    double upPotential;
    double downPotential;
    if(upWire->isGround()) {
        upPotential = 0;
    } else {
        upPotential = array[upWire->getNumber()];
    }

    if(downWire->isGround()) {
        downPotential = 0;
    } else {
        downPotential = array[downWire->getNumber()];
    }
    if((upPotential-downPotential)>0.6)
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

