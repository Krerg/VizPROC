#include "branch.h"
#include "src/c++/Util/stringvalues.h"
#include "src/c++/Util/constvalues.h"
#include "src/c++/Elements/diode.h"
#include <QDebug>
#include "src/c++/Model/model.h"

Branch::Branch(QObject *parent) :
    QObject(parent)
{
    this->isDiode = false;
    this->branchElements = new QList<Element*>();
    this->branchWires = new QList<Wire*>();
    this->opened = true;
    vertexNumber1 = -1;
    vertexNumber2 = -1;
    amperage = ConstValues::BRANCH_AMPERAGE_UNKNOWN;
    hasEmf=false;
    diodeCount=0;
}

void Branch::unionBranch(Branch *anotherBranch)
{
    bool append = false;
    if(this->vertexNumber2==anotherBranch->getVertexNumber1()) {
        append = true;
    }

    foreach (Element* tmpElem, *anotherBranch->branchElements) {
        this->addElement(tmpElem,append, Model::isDiodeBranchCheck());
    }

    foreach (Wire* tmpWire, *anotherBranch->branchWires) {
        this->addWire(tmpWire,append);
    }
}

bool Branch::isDiodeBranch()
{
    return isDiode;
}

void Branch::addElement(Element *elem, bool append, bool check)
{
    if(elem->getName() == StringValues::DIODE_NAME) {
        diodeCount++;
        this->isDiode = true;
        if(check) {
            close();
        }
    }
    if(elem->getName() == StringValues::EMF_NAME) {
        this->hasEmf=true;
    }
    if(append) {
        this->branchElements->append(elem);
    } else {
        this->branchElements->insert(0,elem);
    }
}

void Branch::addWire(Wire *w, bool append)
{
    if(!opened)
        w->close();

    if(append) {
        this->branchWires->append(w);
    } else {
        this->branchWires->insert(0,w);
    }
}

void Branch::setVertexNumber1(int vertexNumber)
{
    this->vertexNumber1 = vertexNumber;
}

void Branch::setVertexNumber2(int vertexNumber)
{
    this->vertexNumber2 = vertexNumber;
}

int Branch::getVertexNumber1()
{
    return vertexNumber1;
}

int Branch::getVertexNumber2()
{
    return vertexNumber2;
}

double Branch::getAmperage()
{
    return amperage;
}

void Branch::setAmperage(double amperage)
{
    this->amperage = amperage;
    foreach (Wire* w, *branchWires) {
        w->setAmperage(amperage);
    }
}

Branch::~Branch()
{
    delete branchElements;
    delete branchWires;
    qDebug()<<"Branch was deleted";
}

bool Branch::isHasEmf()
{
    return hasEmf;
}

void Branch::open()
{
    foreach (Wire* w, *branchWires) {
        w->open();
    }

    foreach (Element* elem, *branchElements) {
        if(elem->getName()==StringValues::DIODE_NAME) {
            ((Diode*)elem)->open();
        }
    }
}

QList<Element *> *Branch::getBranchElements()
{
    return branchElements;
}

QList<Wire *> *Branch::getBranchWires()
{
    return branchWires;
}

int Branch::getDiodeCount()
{
    return diodeCount;
}

void Branch::close()
{
    this->opened=false;
    foreach (Wire* w, *branchWires) {
        w->close();
    }
}
