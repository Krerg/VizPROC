#ifndef COMPONENTMANAGER_H
#define COMPONENTMANAGER_H

#include <QObject>
#include <QList>
#include "src/c++/Elements/resistor.h"
#include "src/c++/Elements/element.h"
#include "src/c++/Elements/wire.h"

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
     * @brief addResistor добавление резистора
     * @param x координата добавления по оси абсцисс
     * @param y координата добавления по оси ординат
     */
    void addResistor(int x, int y);

    /**
     * @brief addEMF добавление ЭДС
     * @param x координата курсора по оси абсцисс
     * @param y координата курсора по оси ординат
     */
    void addEMF(int x, int y);

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
     * @brief drawingWire режим соединения элементов проводом
     */
    bool drawingWire;

    /**
     * @brief elements стуктура, которая хранит все элементы
     */
    QList<Element*> *elements;

    /**
     * @brief wires структура, которая хранит все провода
     */
    QList<Wire*> *wires;

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

    /**
     * @brief wireEnd1 точка для предпросмотра поведения провода при присоединении
     */
    QPoint* wireEnd1;

    /**
     * @brief wireEnd2 точка для предпросмотра поведения провода при присоедтинении
     */
    QPoint* wireEnd2;

    /**
     * @brief drawWire провод, который чертит пользователь в данный момент
     */
    Wire *drawWire;

    /**
     * @brief type говорит какого будет поведение провода при препросмотре
     */
    bool drawType;
signals:

public slots:
    void leftClickReleased();

    /**
     * @brief paintComponents отрисовка всех элементов на экране
     */
    void paintComponents();

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


    /**
     * @brief addElement
     * @param elem
     * @param x
     * @param y
     */
    void addElement(QString elem, int x, int y);

    /**
     * @brief connect вызывается при соединении элементов проводом
     * @param x координата курсора по оси абсции
     * @param y координата курсора по оси ординат
     */
    void connect(int x, int y);
};

#endif // COMPONENTMANAGER_H
