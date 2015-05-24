#ifndef WIRE_H
#define WIRE_H

class Connector;

#include <QObject>
#include <QPoint>
#include <QList>
#include "src/c++/Elements/element.h"
#include <QPainter>
#include "src/c++/View/particle.h"
#include "src/c++/Elements/wireconnector.h"

/**
 * @brief The Wire class провод соединяющий два элемента
 */
class Wire : public QObject
{
    Q_OBJECT
public:
    /**
     * @brief Wire конструктор класса
     * @param parent указатель на рожительский элемент
     */
    explicit Wire(QObject *parent = 0);

    /**
     * @brief addPoint добавление точки отрисовки к проводу
     * @param x координата по оси абсцисс
     * @param y координата по оси ординат
     */
    void addPoint(int x, int y);

    /**
     * @brief addPoint добавление точки отрисовки к проводу
     * @param point сама точка
     */
    void addPoint(QPoint* point);

    /**
     * @brief getPath
     * @return
     */
    QList<QPoint*>* getPath();

    /**
     * @brief setNumber утсановка номера
     * @brief root
     * @param number
     */
    void setNumber(int number, bool root);

    /**
     * @brief getNumber возвращает номер элемента
     * @return
     */
    int getNumber();

    /**
     * @brief paintComponent отрисовка провода на экране
     */
    void paintComponent();

    /**
     * @brief visualisation
     * @param color
     */
    void visualisation(int* color, QPainter* painter);

    /**
     * @brief startConnection начало соединения проводом элементов
     * @param c коннектор, к которому провод должен быть присоединен
     */
    void startConnection(Connector* c);

    /**
     * @brief endConnection заверщенеие соединения проводом
     * @param c коннектор, к которому провод должен быть присоединен
     */
    void endConnection(Connector* c);

    /**
     * @brief isSelected проверет нажал ли пользователь на этот провод
     * @param x координата курсора по оси абсцисс
     * @param y координата курсора по оси ординат
     * @return
     */
    int isSelected(int x, int y);

    /**
     * @brief enablePointing
     */
    void enablePointing();

    /**
     * @brief enableSelection
     */
    void enableSelection();

    /**
     * @brief disablePointing
     */
    void disablePointing();

    /**
     * @brief disableSelection
     */
    void disableSelection();

    /**
     * @brief connectWire присоединение другого провода
     * @param w провод, который хотим присоединить
     */
    void connectWire(Wire* w, int wirePart);

    /**
     * @brief getConnectedWires возвращает список присоединенный проводов
     * @return
     */
    QList<Wire*>* getConnectedWires();

    /**
     * @brief setWireList
     * @param t
     */
    void setWireList(QList<Wire*>* t);

    /**
     * @brief getConnectedElements
     * @return
     */
    QList<Element*>* getConnectedElements();

    /**
     * @brief getAllConnectedElements возвращает все элементы соединенные
     *  с данным потенциалом
     * @return
     */
    QList<Element*>* getAllConnectedElements();

    /**
     * @brief isGround
     * @return
     */
    bool isGround();

    /**
     * @brief setPotential
     * @param potential
     */
    void setPotential(double potential);

    /**
     * @brief getPotential
     * @return
     */
    double getPotential();

    /**
     * @brief initParticles
     */
    void initParticles();

    /**
     * @brief initSpeed вычисляет скорость движения частиц
     * @return сила тока
     */
    int initSpeed();

    /**
     * @brief setSpeed ручная установка скорости движения частиц
     * @param speed
     */
    void setSpeed(int speed);

    /**
     * @brief getConneted1
     * @return
     */
    Connector* getConneted1();

    /**
     * @brief getConneted2
     * @return
     */
    Connector* getConneted2();

private:
    /**
     * @brief path путь, по которому будет рисоваться провод
     */
    QList<QPoint*> *path;

    /**
     * @brief connected1 присоединенный к проводу элемент
     */
    Connector *connected1;

    /**
     * @brief connected2 присоединенный к проводу элемент
     */
    Connector *connected2;

    /**
     * @brief wires присоединенный к проводу другие провода
     */
    QList<Wire*> *wires;

    /**
     * @brief number уникальный номер для потенциала
     */
    int number;

    /**
     * @brief selected выделен ли провод или нет
     */
    bool selected;

    /**
     * @brief pointed наведена ли мышь на провод
     */
    bool pointed;

    /**
     * @brief connectedPointNumber номер точки, которая присоединена к другому проводу
     */
    int connectedPointNumber;

    /**
     * @brief particleList
     */
    QList<Particle*>* particleList;

    /**
     * @brief speed
     */
    int speed;

    /**
     * @brief lastStep
     */
    int lastStep;

    /**
     * @brief potential
     */
    double potential;

    /**
     * @brief wireConnector
     */
    WireConnector* wireConnector;


signals:
    void addWire(Wire* w);
public slots:
    /**
     * @brief changePosition
     * @param oldX
     * @param oldY
     * @param newX
     * @param newY
     */
    void changePosition(int oldX, int oldY, int newX, int newY);
};

#endif // WIRE_H
