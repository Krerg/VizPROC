#include "wirehandler.h"
#include "src/c++/Util/constvalues.h"
#include <QScopedPointer>

WireHandler::WireHandler(QObject *parent) :
    QObject(parent)
{
}

QList<QPair<Wire*,int> >* WireHandler::getFirstConnectedWires(Wire *w)
{
    return getConnectedWires(w->getPath()->first(),w);
}

QList<QPair<Wire*,int> >* WireHandler::getLastConnectedWires(Wire *w)
{
    return getConnectedWires(w->getPath()->last(),w);
}

int WireHandler::hasPoint(Wire *w, QPoint *p)
{
    QPoint* first = w->getPath()->first();
    if(first->x()==p->x() && first->y()==p->y()) {
        return ConstValues::FIRST_POINT_EQUAL;
    }

    QPoint* last = w->getPath()->last();
    if(last->x()==p->x() && last->y()==p->y()) {
        return ConstValues::LAST_POINT_EQUAL;
    }

    return ConstValues::NONE_POINT_EQUAL;
}

QList<QPair<Wire*,int> >* WireHandler::getConnectedWires(QPoint *p, Wire *w)
{

    QList<QPair<Wire*,int> >* connectedWires = new QList<QPair<Wire*,int> >();
    foreach (Wire* wire, *w->getConnectedWires()) {
        if(w==wire) {
            continue;
        }
        int equality = hasPoint(wire,p);
        if(equality!=0) {
            QPair<Wire*,int> pair;
            pair.first=wire;
            pair.second=equality;
            connectedWires->append(pair);
        }
    }
    return connectedWires;
}
