#ifndef CONNECTOR_H
#define CONNECTOR_H

#include <QObject>
#include "src/c++/Elements/element.h"

/**
 * @brief The Connector class
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
     * @brief setConnection связывание коннектора с элементом
     * @param elem элемент с которым связываем
     */
    void setConnection(Element* elem);

    /**
     * @brief setPosition утсановка позиции коннектора
     * @param x
     * @param y
     */
    void setPosition(int x, int y);

    int getX();

    int getY();

    Element* getConnectedElement();

    /**
     * @brief drawComponent отрисовка на экране
     */
    void drawComponent();
private:
    /**
     * @brief connectedWith указатель на элемент с которым соединен
     */
    Element* connectedWith;

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
signals:

public slots:

};

#endif // CONNECTOR_H
