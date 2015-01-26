#ifndef ELEMENT_H
#define ELEMENT_H

class Connector;

#include <QObject>
#include "src/c++/Elements/connector.h"

/**
 * @brief The Element class абстрактный класс элемента схемы
 */
class Element
{
//Pure virtual
public:
    /**
     * @brief setPosition утсановка позиции на экране
     * @param x
     * @param y
     */
    virtual void setPosition(int x, int y)=0;

    /**
     * @brief connect присоединение к элементу провода
     * @param x
     * @param y
     */
    virtual void connect(int x, int y)=0;

    /**
     * @brief paintComponent отрисовка элемента на экране
     */
    virtual void paintComponent()=0;

    /**
    * @brief isSelected проверка на то, что указатель находится на элементу
     * @param x координата указателя
     * @param y
     * @return
     */
    virtual bool isSelected(int x,int y)=0;

    /**
     * @brief disableSelected удаление выделения с элемента
     */
    virtual void disableSelected()=0;

    /**
     * @brief enableSelected делает элемент выделенным
     */
    virtual void enableSelected()=0;

    /**
     * @brief enablePointing делает элемент наведенным
     */
    virtual void enablePointing()=0;

    /**
     * @brief disablePointing снимает с элемента наведение
     */
    virtual void disablePointing()=0;

    /**
     * @brief changeOrientation изменяет ориентацию элемента
     */
    virtual void changeOrientation()=0;

    /**
     * @brief connectorPointCheck проверка на то, что крусор находится на коннекторе
     * @param x координата курсора по оси абсцисс
     * @param y координата курсора по оси ординат
     * @return коннектор, на который наведен курсор если таковой есть
     */
    virtual Connector* connectorPointCheck(int x, int y)=0;

    /**
     * @brief getX возвращает x координату элемента
     * @return
     */
    virtual int getX()=0;

    /**
     * @brief getY возвращает y координату элемента
     * @return
     */
    virtual int getY()=0;

    /**
     * @brief getType
     * @return
     */
    virtual bool getType()=0;

    virtual QString getName()=0;

    /**
     * @brief ~Element деструктор
     */
    virtual ~Element()=0;
signals:

public slots:

};

#endif // ELEMENT_H
