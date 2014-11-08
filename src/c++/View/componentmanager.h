#ifndef COMPONENTMANAGER_H
#define COMPONENTMANAGER_H

#include <QObject>
#include <QList>
#include "src/c++/Elements/listelement.h"
#include "src/c++/Elements/resistor.h"

class ComponentManager : public QObject
{
    Q_OBJECT
public:
    explicit ComponentManager(QObject *parent = 0);
private:
    QList<Element*> *elements;
signals:

public slots:
    void paintComponents(); //отрисовка всех элементов на экран
    void addResistor(int x, int y); //добавление резистора
};

#endif // COMPONENTMANAGER_H
