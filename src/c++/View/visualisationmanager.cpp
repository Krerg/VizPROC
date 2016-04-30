#include "visualisationmanager.h"
#include "src/c++/Elements/emf.h"
#include "src/c++/Elements/resistor.h"
#include "src/c++/Elements/ground.h"
#include "src/c++/Elements/diode.h"
#include "src/c++/Elements/amperemeter.h"
#include "src/c++/Elements/terminal.h"
#include "src/c++/Elements/voltmeter.h"
#include <math.h>
#include <QDebug>
#include "src/c++/Controller/applicationcontext.h"
#include "src/c++/Event/nextstepevent.h"

VisualisationManager::VisualisationManager(QObject *parent) : QObject(parent)
{
    this->meters = NULL;
    this->elements = NULL;
    this->handlers = new QList<Visualization*>();
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

void VisualisationManager::setMeters(QList<Element *> *meters)
{
    this->meters = meters;
}

void VisualisationManager::subscribe(Visualization *handler)
{
    this->handlers->append(handler);
}

void VisualisationManager::unsubscribe(Visualization *handler)
{
    this->handlers->removeAll(handler);
}

int *VisualisationManager::getColor(double potential, double maxPotential, int *container)
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

int VisualisationManager::getRadius(double maxPower, double power)
{
    return static_cast<int>((power/maxPower)*50+0.5);
}

void VisualisationManager::stop()
{
    DestroyEvent* destroyEvent = new DestroyEvent();
    foreach (Visualization* vis, *handlers) {
        vis->destroy(destroyEvent);
    }
    delete destroyEvent;
}

void VisualisationManager::updateVusualisation(QPainter *painter)
{
    //поиск максимального потенциала
    double maxPotential=potentials[0];
    for(int i=0;i<numb;i++) {
        if(potentials[i]>maxPotential) {
            maxPotential=potentials[i];
        }
    }

    //поиск максимальной мощности
    QVector<int> power;
    double maxPower=0;
    double tmpPower;
    QList<Element*>::iterator j;
    for(j=elements->begin();j!=elements->end();j++) {
        //p=U^2/R
        if((*j)->getName()=="Res") {
            Resistor* resTemp = (Resistor*)(*j);
            tmpPower = pow(potentials[resTemp->getConnectedWire1()->getNumber()]-potentials[resTemp->getConnectedWire2()->getNumber()],2)*resTemp->getValue();
            if(tmpPower>maxPower) {
                maxPower=tmpPower;
            }
            //power.append(potentials[resTemp->getConnectedWire1()->getNumber()]-potentials[resTemp->getConnectedWire2()->getNumber()]);
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
            //double power = pow(potentials[resTemp->getConnectedWire1()->getNumber()]-potentials[resTemp->getConnectedWire2()->getNumber()],2)*resTemp->getValue();
            //qDebug()<<"Power:"<<power;
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
            if(!diodeTemp->isOpened()) {
                colorContainer1[0]=0;
                colorContainer1[1]=0;
                colorContainer1[2]=0;

                colorContainer2[0]=0;
                colorContainer2[1]=0;
                colorContainer2[2]=0;
            }

            diodeTemp->visualisation(colorContainer1,colorContainer2,painter,5);
        }
    }

    //визуализация проводов
    QList<Wire*>::iterator i;
    for(i=wires->begin();i!=wires->end();i++) {
        if(!(*i)->isGround() && (*i)->isOpened()) {
            (*i)->visualisation(getColor(potentials[(*i)->getNumber()],maxPotential,colorContainer1),painter);
        } else {
            colorContainer1[0]=0;
            colorContainer1[1]=0;
            colorContainer1[2]=0;
            (*i)->visualisation(colorContainer1,painter);
        }
    }

    NextStepEvent* nse = new NextStepEvent();

    foreach (Visualization* vis, *handlers) {
        vis->nextStep(NULL);
    }
    delete nse;

    //визуализация измеряющих устройств
    if(meters!=NULL) {
        for(j=meters->begin();j!=meters->end();j++) {
            if((*j)->getName()=="Amper") {
                Amperemeter* amper = (Amperemeter*)(*j);
                amper->paintComponent(painter);
            } else if((*j)->getName()=="Voltmeter") {
                Voltmeter* voltmeter = (Voltmeter*)(*j);
                voltmeter->paintComponent(painter);
            } else if((*j)->getName()=="Terminal") {
                Terminal* terminal = (Terminal*)(*j);
                terminal->paintComponent(painter);
            }
        }
    }

    delete colorContainer1;
    delete colorContainer2;
}


void VisualisationManager::startVisualisation(QList<Branch*>* branches, double *x, int numb)
{
    this->potentials = x;
    this->numb = numb;

    //установка значений скорости движения частиц
    QList<Wire*>::iterator i;
    for(i=wires->begin();i!=wires->end();i++) {
        (*i)->setPotential(potentials[(*i)->getNumber()]);
    }

//    for(i=wires->begin();i!=wires->end();i++) {
//        qDebug()<<(*i)->initSpeed();
//    }

    InitEvent* initEvent = new InitEvent();
    initEvent->setX(x);
    initEvent->setBranches(branches);
    //TODO set branches

    foreach (Visualization* vis, *handlers) {
        vis->init(initEvent);
    }

    delete initEvent;
    emit unsetRenderLock();
    emit enableVisualisation();
}

