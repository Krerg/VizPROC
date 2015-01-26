#ifndef CONNECTOR_H
#define CONNECTOR_H

class Element;
class Wire;

#include <QObject>
#include "src/c++/Elements/element.h"
#include "src/c++/Elements/wire.h"



/**
 * @brief The Connector class коннектор, который соединяет провод и элемент
 */
class Connector : public QObject
{
    Q_OBJECT
public:
    /**
     * @brief Connector конструктор класса
     * @param parent указатель на родительский элемент
     */
    explicit Connector(QObject *parent = 0);

    /**
     * @brief setConnection связывание коннектора с проводом
     * @param
     */
    void setConnection(Wire* w);

    /**
     * @brief setPosition утсановка позиции коннектора
     * @param x
     * @param y
     */
    void setPosition(int x, int y);

    /**
     * @brief getX возвращает координатц позиции коннектора по оси абсцисс
     * @return
     */
    int getX();

    /**
     * @brief getY возвращает координату позиции коннектора по оси ординат
     * @return
     */
    int getY();

    /**
     * @brief getConnectedElement возвращает присоединенный провод к коннектору
     * @return
     */
    void getConnectedElement();

    /**
     * @brief getConnectedWire
     * @return
     */
    Wire* getConnectedWire();

    /**
     * @brief drawComponent отрисовка на экране
     */
    void drawComponent();

    /**
     * @brief enablePointing делает коннектор наведенным
     */
    void enablePointing();

    /**
     * @brief disablePointing снимает наведение с коннектора
     */
    void disablePointing();

    /**
     * @brief setParentElement устанавливает элемент, с которым
     * связан конннектор
     * @param parent
     */
    void setParentElement(Element* parent);

    /**
     * @brief getParentElement
     * @return элемент, с которым связан коннектор
     */
    Element* getParentElement();

    /**
     * @brief checkPointing проверяет на то, что курсора наведен на коннектор
     * @param x координата курсора по оси обсцисс
     * @param y координата курсора по оси ординат
     * @return
     */
    bool checkPointing(int x, int y);

    /**
     * @brief changePosition оповещает подключенные провода о том, что позиция
     * элемента изменилась
     * @param x координата курсора по оси абсцисс
     * @param y координата курсора по оси ординат
     */
    void changePosition(int x, int y);
private:    
    /**
     * @brief x координата на экране
     */
    int x;

    /**
     * @brief y координата на экране
     */
    int y;

    /**
     * @brief width ширина коннектора
     */
    int width;

    /**
     * @brief height высота коннектора
     */
    int height;

    /**
     * @brief pointed наведен ли курсор на коннектор
     */
    bool pointed;

    /**
     * @brief parent элемент, с которым соединен коннектор
     */
    Element* parent;

    /**
     * @brief connectedWire присоединенный к коннектору провод
     */
    Wire* connectedWire;

signals:
    /**
     * @brief changePosition
     * @param oldX
     * @param oldY
     * @param newX
     * @param newY
     */
    void changePosition(int oldX, int oldY, int newX, int newY);
public slots:

};
\
#endif // CONNECTOR_H
