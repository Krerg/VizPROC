#include "visualisationmanager.h"
#include "src/c++/Elements/emf.h"
#include "src/c++/Elements/resistor.h"
#include "src/c++/Elements/ground.h"
#include "src/c++/Elements/diode.h"
#include <math.h>
#include <QDebug>

VisualisationManager::VisualisationManager(QObject *parent) : QObject(parent)
{

}

VisualisationManager::~VisualisationManager()
{

}

void VisualisationManager::setWires(QList<Wire *> *wires)
{
    this->wires = wires;
}

void VisualisationManager::setElements(QList<Element *> *elements)
{
    this->elements = elements;
}

int *VisualisationManager::getColor(int potential, int maxPotential, int *container)
{
    if(potential>0) {
        int color = (double)potential/maxPotential*255;
        container[0]=color;
        container[1]=0;
        container[2]=0;
    } else if(potential<0) {
        int color = (double)potential/maxPotential*255;
        container[0]=0;
        container[1]=0;
        container[2]=color;
    } else {
        container[0]=0;
        container[1]=0;
        container[2]=0;
    }
    return container;
}

int VisualisationManager::getRadius(int maxPower, int power)
{
    return power/maxPower*50;
}

void VisualisationManager::updateVusualisation(QPainter *painter)
{
    //поиск максимального потенциала
    int maxPotential=potentials[0];
    for(int i=0;i<numb;i++) {
        if(potentials[i]>maxPotential) {
            maxPotential=potentials[i];
        }
    }

    //поиск максимальной мощности
    QVector<int> power;
    int maxPower=0;
    QList<Element*>::iterator j;
    for(j=elements->begin();j!=elements->end();j++) {
        //p=U^2/R
        if((*j)->getName()=="Res") {
            Resistor* resTemp = (Resistor*)(*j);
            if(potentials[resTemp->getConnectedWire1()->getNumber()]-potentials[resTemp->getConnectedWire2()->getNumber()]>maxPower) {
                maxPower=pow(potentials[resTemp->getConnectedWire1()->getNumber()]-potentials[resTemp->getConnectedWire2()->getNumber()],2)*resTemp->getValue();
            }
            power.append(potentials[resTemp->getConnectedWire1()->getNumber()]-potentials[resTemp->getConnectedWire2()->getNumber()]);
        }
    }

    int* colorContainer1 = new int[3];
    int* colorContainer2 = new int[3];

    //визуализация элементов
     for(j=elements->begin();j!=elements->end();j++) {
        if((*j)->getName()=="Res") {
            Resistor* resTemp = (Resistor*)(*j);
            int tmpNumb = resTemp->getConnectedWire1()->getNumber();
            if(tmpNumb<0) {
              colorContainer1[0]=0;
              colorContainer1[1]=0;
              colorContainer1[2]=0;
            } else {
              colorContainer1 = getColor(potentials[tmpNumb],maxPotential,colorContainer1);
            }
            tmpNumb = resTemp->getConnectedWire2()->getNumber();
            if(tmpNumb<0) {
              colorContainer2[0]=0;
              colorContainer2[1]=0;
              colorContainer2[2]=0;
            } else {
              colorContainer2 = getColor(potentials[tmpNumb],maxPotential,colorContainer2);
            }
            //int power = pow(potentials[resTemp->getConnectedWire1()->getNumber()]-potentials[resTemp->getConnectedWire2()->getNumber()],2)*resTemp->getValue();
            resTemp->visualisation(colorContainer1,colorContainer2,painter,getRadius(maxPower,pow(potentials[resTemp->getConnectedWire1()->getNumber()]-potentials[resTemp->getConnectedWire2()->getNumber()],2)*resTemp->getValue()));
        } else if((*j)->getName()=="Emf") {
            EMF* emfTemp = (EMF*)(*j);
            int tmpNumb = emfTemp->getConnectedWire1()->getNumber();
            if(tmpNumb<0) {
              colorContainer1[0]=0;
              colorContainer1[1]=0;
              colorContainer1[2]=0;
            } else {
              colorContainer1 = getColor(potentials[tmpNumb],maxPotential,colorContainer1);
            }
            tmpNumb = emfTemp->getConnectedWire2()->getNumber();
            if(tmpNumb<0) {
              colorContainer2[0]=0;
              colorContainer2[1]=0;
              colorContainer2[2]=0;
            } else {
              colorContainer2 = getColor(potentials[tmpNumb],maxPotential,colorContainer2);
            }
            emfTemp->visualisation(colorContainer1,colorContainer2,painter,0);
        } else if((*j)->getName()=="Ground") {
            Ground* groundTemp = (Ground*)(*j);
            groundTemp->visualisation(painter);
        } else if((*j)->getName()=="Diode") {
            Diode* diodeTemp = (Diode*)(*j);
            diodeTemp->visualisation(painter);
        }
    }

    //визуализация проводов
    QList<Wire*>::iterator i;
    for(i=wires->begin();i!=wires->end();i++) {
        if(!(*i)->isGround()) {
            (*i)->setSpeed(1);
            (*i)->initParticles();
            (*i)->visualisation(getColor(potentials[(*i)->getNumber()],maxPotential,colorContainer1),painter);
        } else {
            colorContainer1[0]=0;
            colorContainer1[1]=0;
            colorContainer1[2]=0;
            (*i)->setSpeed(1);
            (*i)->initParticles();
            (*i)->visualisation(colorContainer1,painter);
        }
    }



    delete colorContainer1;
    delete colorContainer2;
}


void VisualisationManager::startVisualisation(QMap<Wire *, int *> *graph, double *x, int numb)
{
    this->graph = graph;
    this->potentials = x;
    this->numb = numb;

    //установка значений скорости движения частиц
    QList<Wire*>::iterator i;
    for(i=wires->begin();i!=wires->end();i++) {
        (*i)->setPotential(potentials[(*i)->getNumber()]);
    }

    for(i=wires->begin();i!=wires->end();i++) {
        qDebug()<<(*i)->initSpeed();
    }

    emit enableVisualisation();
}

