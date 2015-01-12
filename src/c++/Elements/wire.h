#ifndef WIRE_H
#define WIRE_H

#include <QObject>
#include <QPoint>
#include <QList>
#include "src/c++/Elements/element.h"

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
     * @brief setNumber утсановка номера
     * @param number
     */
    void setNumber(int number);

    /**
     * @brief paintComponent отрисовка провода на экране
     */
    void paintComponent();

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
    bool isSelected(int x, int y);
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
signals:

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
