#ifndef COMPONENTMANAGER_H
#define COMPONENTMANAGER_H

#include <QObject>
#include <QList>
#include "src/c++/Elements/resistor.h"
#include "src/c++/Elements/element.h"

/**
 * @brief The ComponentManager class менеджер элементов
 */
class ComponentManager : public QObject
{
    Q_OBJECT
public:
    /**
     * @brief ComponentManager конструктор класса
     * @param parentуказатель на родительский элемент
     */
    explicit ComponentManager(QObject *parent = 0);
private:
    /**
     * @brief dx разница координат мыши и элемента по оси абсцисс
     */
    int dx;

    /**
     * @brief dy
     */
    int dy;

    /**
     * @brief leftClick говорит нажата ли левая кнопка мыши
     */
    bool leftClick;

    /**
     * @brief elements стуктура, которая хранит все элементы
     */
    QList<Element*> *elements;

    /**
     * @brief getElementByCoordinates возвращает элемент по координатам курсора
     * @param x координата по оси абсцисс
     * @param y координата по оси ординат
     * @return
     */
    Element* getElementByCoordinates(int x, int y);

    /**
     * @brief selected выделенные элемент
     */
    Element* selected;

    /**
     * @brief pointed элемент, на который наведена мышь
     */
    Element* pointed;

    /**
     * @brief pointedConnector коннектор, на который наведен курссор
     */
    Connector* pointedConnector;
signals:

public slots:
    void leftClickReleased();

    /**
     * @brief paintComponents отрисовка всех элементов на экране
     */
    void paintComponents();

    /**
     * @brief addResistor добавление резистора
     * @param x координата добавления по оси абсцисс
     * @param y координата добавления по оси ординат
     */
    void addResistor(int x, int y);

    /**
     * @brief moveElement перемещениие элемента
     * @param x
     * @param y
     */
    void moveElement(int x, int y);

    /**
     * @brief mouseClick клик левой кнопкой мыши
     * @param x
     * @param y
     */
    void mouseClick(int x, int y);

    /**
     * @brief mouseMoved простое перемещение мыши
     * @param x
     * @param y
     */
    void mouseMoved(int x, int y);

    /**
     * @brief changeOrientation изменение ориентации элмента по координатам курсора
     * @param x
     * @param y
     */
    void changeOrientation(int x, int y);
};

#endif // COMPONENTMANAGER_H
