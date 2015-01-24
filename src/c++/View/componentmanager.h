#ifndef COMPONENTMANAGER_H
#define COMPONENTMANAGER_H

#include <QObject>
#include <QList>
#include "src/c++/Elements/resistor.h"
#include "src/c++/Elements/element.h"
#include "src/c++/Elements/wire.h"
#include "src/c++/Elements/ground.h"

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
     * @brief addGround добавление заземления
     * @param x координата курсора по оси абсцисс
     * @param y координата курсора по оси ординат
     */
    void addGround(int x, int y);

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
     * @brief ground заземление (пока что одно)
     */
    Ground *ground;

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
     * @brief selectedWire выделенный провод если есть
     */
    Wire* selectedWire;

    /**
     * @brief pointed элемент, на который наведена мышь
     */
    Element* pointed;

    /**
     * @brief pointed провод, на который наведена мышь
     */
    Wire* pointedWire;

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

    /**
     * @brief wirePart указывает на номер отрезка,
     *  к которому присоединяется другой провод
     */
    int wirePart;
signals:
    /**
     * @brief WireAdded сигнал, который вызывается когда добавляется
     * новый элемент (сигнал подается на логиику для построения графа
     * потенциалов)
     *
     * @param w добавляемый провод
     */
    void wireAdded(Wire* w);
public slots:
    void leftClickReleased();

    /**
     * @brief paintComponents отрисовка всех элементов на экране
     */
    void paintComponents();

    /**
     * @brief moveElement перемещениие элемента
     * @param x координата курсора по оси абсцисс
     * @param y координата курсора по оси ординат
     */
    void moveElement(int x, int y);

    /**
     * @brief mouseClick клик левой кнопкой мыши
     * @param x координата курсора по оси абсцисс
     * @param y координата курсора по оси ординат
     */
    void mouseClick(int x, int y);

    /**
     * @brief mouseMoved простое перемещение мыши
     * @param x координата курсора по оси абсцисс
     * @param y координата курсора по оси ординат ы
     */
    void mouseMoved(int x, int y);

    /**
     * @brief changeOrientation изменение ориентации элмента по координатам курсора
     * @param x координата курсора по оси абсцисс
     * @param y координата курсора по оси ординат
     */
    void changeOrientation(int x, int y);


    /**
     * @brief addElement слот для добавления элемента по названию
     * @param elem название элемента
     * @param x координата курсора по оси абсцисс
     * @param y координата курсора по оси ординат
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
