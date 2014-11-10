#ifndef COMPONENTMANAGER_H
#define COMPONENTMANAGER_H

#include <QObject>
#include <QList>
#include "src/c++/Elements/resistor.h"

class ComponentManager : public QObject
{
    Q_OBJECT
public:
    explicit ComponentManager(QObject *parent = 0);
private:
    QList<Element*> *elements; //список всех элементов
    Element getElementByCoordinates(int x, int y); //взятие элемента с экрана по координатам
signals:

public slots:
    void paintComponents(); //отрисовка всех элементов на экран
    void addResistor(int x, int y); //добавление резистора
    void moveElement(int x, int y); //перетаскивание компонента
    void mouseClick(int x, int y); //клик левой кнопкой мыши
};

#endif // COMPONENTMANAGER_H
