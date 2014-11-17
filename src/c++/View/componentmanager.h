#ifndef COMPONENTMANAGER_H
#define COMPONENTMANAGER_H

#include <QObject>
#include <QList>
#include "src/c++/Elements/resistor.h"
#include "src/c++/Elements/element.h"

class ComponentManager : public QObject
{
    Q_OBJECT
public:
    explicit ComponentManager(QObject *parent = 0);
private:
    int dx; //разниица ккординат мыши и элемента для передвижения элементов
    int dy;
    bool leftClick;
    QList<Element*> *elements; //список всех элементов
    Element* getElementByCoordinates(int x, int y); //взятие элемента с экрана по координатам
    Element* selected;
signals:

public slots:
    void leftClickReleased();
    void paintComponents(); //отрисовка всех элементов на экран
    void addResistor(int x, int y); //добавление резистора
    void moveElement(int x, int y); //перетаскивание компонента
    void mouseClick(int x, int y); //клик левой кнопкой мыши
    void changeOrientation(int x, int y); //изменение ориентации элемента
};

#endif // COMPONENTMANAGER_H
