#include "branch.h"
#include "src/c++/Util/stringvalues.h"

Branch::Branch(QObject *parent) :
    QObject(parent)
{
    this->isDiode = false;
    this->branchElements = new QList<Element*>();
    this->branchWires = new QList<Wire*>();
}

void Branch::unionBranch(Branch *anotherBranch)
{
    foreach (Element* tmpElem, *anotherBranch->branchElements) {
        this->addElement(tmpElem);
    }

    foreach (Wire* tmpWire, *anotherBranch->branchWires) {
        this->addWire(tmpWire);
    }
}

bool Branch::isDiodeBranch()
{
    return isDiode;
}

void Branch::addElement(Element *elem)
{
    if(elem->getName() == StringValues::DIODE_NAME) {
        this->isDiode = true;
    }
    this->branchElements->append(elem);
}

void Branch::addWire(Wire *w)
{
    this->branchWires->append(w);
}

Branch::~Branch()
{
    delete branchElements;
    delete branchWires;
}
