#ifndef COMPONENTMANAGER_H
#define COMPONENTMANAGER_H

#include <QObject>
#include <QList>
#include "src/c++/Elements/resistor.h"
#include "src/c++/Elements/emf.h"
#include "src/c++/Elements/element.h"
#include "src/c++/Elements/wire.h"
#include "src/c++/Elements/ground.h"
#include "src/c++/Elements/diode.h"
#include <QPainter>

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

    /**
     * @brief setPainter
     * @param painter
     */
    void setPainter(QPainter *painter);

    /**
     * @brief addResistor
     * @param res
     */
    void addResistor(Resistor* res);

    /**
     * @brief addEMF
     * @param emf
     */
    void addEMF(EMF* emf);

    /**
     * @brief addGrounf
     * @param ground
     */
    void addGround(Ground* ground);

    /**
     * @brief addDiode добавление диода
     */
    void addDiode(Diode* d);

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
     * @brief addDiode добавление диода
     * @param x координата курсора по оси абсцисс
     * @param y координата курсора по оси ординат
     */
    void addDiode(int x, int y);

    /**
     * @brief addGround добавление заземления
     * @param x координата курсора по оси абсцисс
     * @param y координата курсора по оси ординат
     */
    void addGround(int x, int y);

    /**
     * @brief addAmperemeter добавление амперметра
     * @param x координата курсора по оси абсцисс
     * @param y координата курсора по оси ординат
     */
    void addAmperemeter(int x, int y);

    /**
     * @brief addVoltmeter
     * @param x
     * @param y
     */
    void addVoltmeter(int x, int y);

    /**
     * @brief dx разница координат мыши и элемента по оси абсцисс
     */
    int dx;

    /**
     * @brief dy разница координат мыши и элемента по оси ординат
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
     * @brief meters список измерительных приборов
     */
    QList<Element*> *meters;

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
     * @brief deleteMutex
     */
    bool deleteMutex=false;

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

    /**
     * @brief painter отрисовщик на OpenGL виджете
     */
    QPainter *painter;

protected:

signals:

    /**
     * @brief elementDeleted
     */
    void elementDeleted();

    /**
     * @brief WireAdded сигнал, который вызывается когда добавляется
     * новый элемент (сигнал подается на логиику для построения графа
     * потенциалов)
     *
     * @param w добавляемый провод
     */
    void wireAdded(Wire* w);

    /**
     * @brief deleteWire сигнял, который вызывается при удалении провода.
     * @param w удаляемый провод.
     */
    void deleteWire(Wire* w);

    /**
     * @brief onElementClick
     * @param elem
     */
    void onElementClick(Element* elem);

    /**
     * @brief onWireClick
     * @param w
     */
    void onWireClick(Wire* w);

    /**
     * @brief addDiode
     * @param d
     */
    void addedDiode(Diode* d);
public slots:
    /**
     * @brief deleteItem слот удаления элемента
     */
    void deleteItem();

    /**
     * @brief leftClickReleased
     */
    void leftClickReleased();

    /**
     * @brief addWire добавление провода (при делении на 2)
     * @param w
     */
    void addWire(Wire* w);

    /**
     * @brief paintComponents отрисовка всех элементов на экране
     */
    void paintComponents();

    /**
     * @brief paintMeters отрисовка измерительных приборов
     * @param painter
     */
    void paintMeters(QPainter *painter);

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
     * @param elemType название элемента
     * @param x координата курсора по оси абсцисс
     * @param y координата курсора по оси ординат
     */
    void addElement(int elemType, int x, int y);

    /**
     * @brief connect вызывается при соединении элементов проводом
     * @param x координата курсора по оси абсции
     * @param y координата курсора по оси ординат
     */
    void connect(int x, int y);

    /**
     * @brief getElements
     * @return
     */
    QList<Element*>* getElements();

    /**
     * @brief getElements
     * @return
     */
    QList<Element*>* getMeters();



    /**
     * @brief getWires
     * @return
     */
    QList<Wire*>* getWires();
};

#endif // COMPONENTMANAGER_H
