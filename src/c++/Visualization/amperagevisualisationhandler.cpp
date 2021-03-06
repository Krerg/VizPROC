#include "amperagevisualisationhandler.h"
#include "src/c++/Util/stringvalues.h"
#include "src/c++/Elements/resistor.h"
#include "src/c++/Elements/emf.h"
#include "src/c++/Util/constvalues.h"
#include "src/c++/Controller/applicationcontext.h"
#include <math.h>
#include "src/c++/Elements/connector.h"
#include "src/c++/Util/circuitutils.h"
#include "src/c++/Util/wirehandler.h"
#include <QScopedPointer>
#include <QVector>
#include <QDebug>

AmperageVisualisationHandler::AmperageVisualisationHandler(QObject *parent) :
    QObject(parent)
{
    amperages = NULL;
}

void AmperageVisualisationHandler::nextStep(NextStepEvent *event)
{
    foreach (Wire* w, *ApplicationContext::getInstance()->getComponentManager()->getWires()) {
        if(w->getSpeed()==ConstValues::POSITIVE_SPEED || w->getSpeed()==ConstValues::NEGATIVE_SPEED) {
            w->setSpeed(w->getSpeed()*getSpeed(maxAmperage,w->getAmperage()));
        }
        w->initParticles();
    }
}

void AmperageVisualisationHandler::destroy(DestroyEvent *event)
{
    //TODO
}

void AmperageVisualisationHandler::init(InitEvent *event)
{
    if(event->getBranches()==NULL) {
        return;
    }
    clearWireAmperages();
    if(amperages!=NULL) {
        delete amperages;
    }
    amperages = new QVector<double>(event->getBranches()->size());


    double tmpAmperage = 0.0;
    bool wasUninit=true;
    while(true) {
        if(!wasUninit) {
            break;
        }
        wasUninit=false;
        foreach (Branch* branch, *event->getBranches()) {
            if(branch->getAmperage()!=ConstValues::BRANCH_AMPERAGE_UNKNOWN) {
                continue;
            }
            if((tmpAmperage=getBranchAmperage(branch,event->getX()))!=ConstValues::BRANCH_AMPERAGE_UNKNOWN) {
                amperages->append(tmpAmperage);
                setAmperageOnWires(branch,tmpAmperage,event->getX());
            } else {
                if(!trySetAmperage(branch,event->getX())) {
                    wasUninit=true;
                }
            }
        }
    }
    checkAllWires();
    initParticlesSpeed();
}

QHash<QString,double>* AmperageVisualisationHandler::getBranchParameters(QList<Element *> *elements)
{
    QHash<QString,double> *parameters = new QHash<QString,double>();
    double resistance=0.0;
    double voltage=0.0;
    foreach (Element* elem, *elements) {
        if(elem->getName()==StringValues::RESISTOR_NAME) {
            resistance+=((Resistor*)elem)->getResistance();
        } else if(elem->getName()==StringValues::EMF_NAME) {
            voltage+=((EMF*)elem)->getVoltage();
        }
    }
    parameters->insert(StringValues::RESISTANCE_MAP_VALUE,resistance);
    parameters->insert(StringValues::VOLTAGE_MAP_VALUE,voltage);
    return parameters;
}

double AmperageVisualisationHandler::getBranchAmperage(Branch *branch, double* x)
{
    foreach (Element* elem , *branch->getBranchElements()) {
        if(elem->getName()==StringValues::RESISTOR_NAME) {
            double potential1 = x[elem->getConnectors()->first()->getConnectedWire()->getNumber()];
            double potential2 = x[elem->getConnectors()->last()->getConnectedWire()->getNumber()];
            double amperage = fabs((potential1-potential2)/((Resistor*)elem)->getResistance());
            return amperage;
        }
    }
    return ConstValues::BRANCH_AMPERAGE_UNKNOWN;
}

void AmperageVisualisationHandler::setAmperageOnWires(QList<Branch *> *connectedBranches, Branch *branch, double* x, int vertexNumber)
{
    double amperage = 0.0;
    int centralVertexNumber = -1;
    int anotherVertexNumber = -1;
    int k=1;
    foreach (Branch* connectedBranch, *connectedBranches) {
        k=1;
        if(connectedBranch == branch ) {
            continue;
        }

        if(branch->isHasEmf() || connectedBranch->isHasEmf()) {
            k=-1;
        }

        if(vertexNumber == 1) {
            if(branch->getVertexNumber1()==connectedBranch->getVertexNumber1()) {
                centralVertexNumber = branch->getVertexNumber1();
                anotherVertexNumber = connectedBranch->getVertexNumber2();
            } else if (branch->getVertexNumber1()==connectedBranch->getVertexNumber2()) {
                anotherVertexNumber = connectedBranch->getVertexNumber1();
                centralVertexNumber = branch->getVertexNumber1();
            }

            double centralAmerage = CircuitUtils::getAmperage(centralVertexNumber,x);
            double anotherAmperage = CircuitUtils::getAmperage(anotherVertexNumber,x);
            if(CircuitUtils::getAmperage(centralVertexNumber,x)<CircuitUtils::getAmperage(anotherVertexNumber,x)) {
                amperage+=connectedBranch->getAmperage()*k;
            } else {
                amperage-=connectedBranch->getAmperage()*k;
            }

        }

        if(vertexNumber == 2) {
            if(branch->getVertexNumber2()==connectedBranch->getVertexNumber1()) {
                centralVertexNumber = branch->getVertexNumber2();
                anotherVertexNumber = connectedBranch->getVertexNumber2();
            } else if(branch->getVertexNumber2()==connectedBranch->getVertexNumber2()) {
                centralVertexNumber = branch->getVertexNumber2();
                anotherVertexNumber = connectedBranch->getVertexNumber1();
            }

            if(CircuitUtils::getAmperage(centralVertexNumber,x)<CircuitUtils::getAmperage(anotherVertexNumber,x)) {
                amperage-=connectedBranch->getAmperage()*k;
            } else {
                amperage+=connectedBranch->getAmperage()*k;
            }
        }
    }
    setAmperageOnWires(branch,amperage,x);
}

void AmperageVisualisationHandler::setAmperageOnWires(Branch *branch, double amperage, double* x)
{
    QList<Element*>::Iterator elementIterator;
    QList<Connector*> *connectors;
    double potential1 = 0.0;
    double potential2 = 0.0;
    branch->setAmperage(amperage);
    amperages->append(fabs(amperage));
    for(elementIterator = branch->getBranchElements()->begin();elementIterator!=branch->getBranchElements()->end();elementIterator++) {
        if((*elementIterator)->getName()!=StringValues::TRANSISTOR_NAME) {
            connectors = (*elementIterator)->getConnectors();

            if(connectors->first()->getConnectedWire()->getNumber()==-1) {
                potential1 = 0.0;
            } else {
                potential1 = x[connectors->first()->getConnectedWire()->getNumber()];
            }

            if(connectors->last()->getConnectedWire()->getNumber()==-1) {
                potential2 = 0.0;
            } else {
                potential2 = x[connectors->last()->getConnectedWire()->getNumber()];
            }

            if(potential1>potential2) {
                setAmperageOnWire(connectors->first()->getConnectedWire(),(*elementIterator),true);
                setAmperageOnWire(connectors->last()->getConnectedWire(),(*elementIterator),false);
            } else {
                setAmperageOnWire(connectors->first()->getConnectedWire(),(*elementIterator),false);
                setAmperageOnWire(connectors->last()->getConnectedWire(),(*elementIterator),true);
            }
        }
    }
}

void AmperageVisualisationHandler::setAmperageOnWire(Wire *w, Element *elem, bool direction)
{
    int k=1;
    if(elem->getName()==StringValues::EMF_NAME) {
        k=-1;
    }
    if(direction) {
        if(w->getConneted1()!=NULL && w->getConneted1()->getParentElement()==elem) {
            w->setSpeed(ConstValues::POSITIVE_SPEED*k);
        } else if(w->getConneted2()!=NULL && w->getConneted2()->getParentElement()==elem) {
            w->setSpeed(ConstValues::NEGATIVE_SPEED*k);
        }
    } else {
        if(w->getConneted1()!=NULL && w->getConneted1()->getParentElement()==elem) {
            w->setSpeed(ConstValues::NEGATIVE_SPEED*k);
        } else if(w->getConneted2()!=NULL && w->getConneted2()->getParentElement()==elem) {
            w->setSpeed(ConstValues::POSITIVE_SPEED*k);
        }
    }
}

bool AmperageVisualisationHandler::trySetAmperage(Branch *branch, double *x)
{
    QList<Branch*> *connectedBranches;
    bool wasUninit = false;
    if(branch->getVertexNumber1()!=0) {
        if(branch->getAmperage()!=ConstValues::BRANCH_AMPERAGE_UNKNOWN) {
            return true;
        }
        connectedBranches = ApplicationContext::getInstance()->getModel()->getConnectedBranches(branch->getVertexNumber1());
        bool wasUninit = false;
        foreach (Branch* connectedBranch, *connectedBranches) {
            if(connectedBranch==branch) {
                continue;
            }
            if(connectedBranch->getAmperage()==ConstValues::BRANCH_AMPERAGE_UNKNOWN) {
                wasUninit = true;
                break;
            }
        }
        if(!wasUninit) {
            setAmperageOnWires(connectedBranches,branch,x,1);
            return true;
        }
        delete connectedBranches;
    }

    if(branch->getVertexNumber2()!=0) {
        connectedBranches = ApplicationContext::getInstance()->getModel()->getConnectedBranches(branch->getVertexNumber2());
        wasUninit = false;
        foreach (Branch* connectedBranch, *connectedBranches) {
            if(connectedBranch==branch) {
                continue;
            }
            if(connectedBranch->getAmperage()==ConstValues::BRANCH_AMPERAGE_UNKNOWN) {
                wasUninit = true;
                break;
            }
        }
        if(!wasUninit) {
            setAmperageOnWires(connectedBranches,branch,x,2);
            return true;
        }
        delete connectedBranches;
    }
    return false;
}

bool AmperageVisualisationHandler::trySeyAmperageOnWire(Wire *wire)
{
    double wireAmperage = 0.0;
    bool success = true;
    QList<QPair<Wire*, int> >* connectedWires = WireHandler::getFirstConnectedWires(wire);
    QList<QPair<Wire*, int> >::Iterator it;
    for(it = connectedWires->begin();it!=connectedWires->end();it++) {
        if((*it).first->getAmperage() == ConstValues::BRANCH_AMPERAGE_UNKNOWN) {
            success = false;
            break;
        }
        switch((*it).second) {
            //ConstValues::FIRST_POINT_EQUAL
            case 1:
                if((*it).first->getSpeed()>0) {
                    wireAmperage+=(*it).first->getAmperage();
                } else {
                    wireAmperage-=(*it).first->getAmperage();
                }
                break;
            //ConstValues::LAST_POINT_EQUAL
            case 2:
                if((*it).first->getSpeed()>0) {
                    wireAmperage-=(*it).first->getAmperage();
                } else {
                    wireAmperage+=(*it).first->getAmperage();
                }
                break;
        }
    }

    if(wireAmperage < 0) {
        wire->setSpeed(ConstValues::POSITIVE_SPEED);
    } else {
        wire->setSpeed(ConstValues::NEGATIVE_SPEED);
    }
    delete connectedWires;
    if(success) {
        wire->setAmperage(wireAmperage);
        amperages->append(fabs(wireAmperage));
        return true;
    }


    connectedWires = WireHandler::getLastConnectedWires(wire);
    success = true;

    for (it = connectedWires->begin();it!=connectedWires->end();it++) {
        if((*it).first->getAmperage() == ConstValues::BRANCH_AMPERAGE_UNKNOWN) {
            success = false;
            break;
        }
        switch((*it).second) {
            //ConstValues::FIRST_POINT_EQUAL
            case 1:
                if((*it).first->getSpeed()>0) {
                    wireAmperage-=(*it).first->getAmperage();
                } else {
                    wireAmperage+=(*it).first->getAmperage();
                }
                break;
            //ConstValues::LAST_POINT_EQUAL
            case 2:
                if((*it).first->getSpeed()>0) {
                    wireAmperage+=(*it).first->getAmperage();
                } else {
                    wireAmperage-=(*it).first->getAmperage();
                }
                break;
        }
    }

    if(wireAmperage < 0) {
        wire->setSpeed(ConstValues::POSITIVE_SPEED);
    } else {
        wire->setSpeed(ConstValues::NEGATIVE_SPEED);
    }
    delete connectedWires;
    if(success) {
        amperages->append(fabs(wireAmperage));
        return true;
    }

    return false;
}

void AmperageVisualisationHandler::initParticlesSpeed()
{
    qSort(*amperages);
    maxAmperage = amperages->last();
    qDebug()<<"Max amperage :"+QString::number(maxAmperage);
}

void AmperageVisualisationHandler::checkAllWires()
{
    QList<Wire*>* allWires = ApplicationContext::getInstance()->getComponentManager()->getWires();
    bool wasUninit = false;
    while(true) {
        wasUninit = false;
        foreach (Wire* wire, *allWires) {
            if(wire->groundConnected()) {
                continue;
            }
            if(wire->getAmperage()==ConstValues::BRANCH_AMPERAGE_UNKNOWN) {
                if(!trySeyAmperageOnWire(wire)) {
                    wasUninit = true;
                }
            }
        }
        if(!wasUninit) {
            break;
        }
    }
}

int AmperageVisualisationHandler::getSpeed(double maxAmperage, double wireAmperage)
{
    int speed = (wireAmperage/maxAmperage)*3;
    if(speed==0) {
        return 1;
    }
    return speed;
}

void AmperageVisualisationHandler::clearWireAmperages()
{
    foreach (Wire* w, *ApplicationContext::getComponentManager()->getWires()) {
        w->setAmperage(ConstValues::BRANCH_AMPERAGE_UNKNOWN);
    }
}


