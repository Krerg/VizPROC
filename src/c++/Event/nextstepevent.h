#ifndef NEXTSTEPEVENT_H
#define NEXTSTEPEVENT_H

#include <QObject>
#include "src/c++/Elements/element.h"

class NextStepEvent : public QObject
{
    Q_OBJECT
public:
    explicit NextStepEvent(QObject *parent = 0);

    QList<Wire *> *getWires() const;

    void setWires(QList<Wire *> *value);

    QList<Element *> *getElements() const;

    void setElements(QList<Element *> *value);

private:

    QList<Element*>* elements;

    QList<Wire*>* wires;

signals:

public slots:

};

#endif // NEXTSTEPEVENT_H
