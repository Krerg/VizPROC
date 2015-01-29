#ifndef RESISTOR_H
#define RESISTOR_H

#include <QObject>
#include "src/c++/Elements/element.h"
#include "src/c++/Elements/connector.h"


/**
 * @brief The Resistor class класс резистора
 */
class Resistor : public QObject,Element
{
    Q_OBJECT
public:
    explicit Resistor(QObject *parent = 0);
    virtual void paintComponent();
    void setHeight(int height);
    void setWidth(int width);
    int getWidth();
    int getHeight();
    virtual void setPosition(int x, int y);
    virtual void connect(int x,int y);
    virtual bool isSelected(int x, int y);
    virtual void disableSelected();
    virtual void enableSelected();
    virtual void enablePointing();
    virtual void disablePointing();
    virtual void changeOrientation();
    virtual Connector* connectorPointCheck(int x, int y);
    virtual int getX();
    virtual int getY();
    virtual QString getName();

    /**
     * @brief getAnotherConnector
     * @param c
     * @return
     */
    Connector* getAnotherConnector(Connector *c);

    /**
     * @brief getAnotherWire
     * @param number
     * @return
     */
    Wire* getAnotherWire(int number);

    /**
     * @brief getValue метод получения проводимости резистора
     * @return проводимость элемента
     */
    int getValue();

    /**
     * @brief getType текущая ориентация на экране
     * @return
     */
    virtual bool getType();
    virtual ~Resistor();

    /**
     * @brief HORIZONTAL_ORIENTATION
     */
    const QString HORIZONTAL_ORIENTATION = "HORIZONTAL";

    /**
     * @brief VERTICAL_ORIENTATION
     */
    const QString VERTICAL_ORIENTATION = "VERTICAL";

private:

    /**
     * @brief name
     */
    const QString name = "Res";

    /**
     * @brief pointed состоягие наведения на элемент
     */
    bool pointed;

    /**
     * @brief selected хранит состояние выделения элемента
     */
    bool selected;

    /**
     * @brief x координата по оси асцисс
     */
    int x;

    /**
     * @brief y координата по оси ординат
     */
    int y;

    /**
     * @brief height высота резистора
     */
    int height;

    /**
     * @brief width ширина резистора
     */
    int width;

    /**
     * @brief pinLength длина выводов резистора
     */
    int pinLength;

    /**
     * @brief orientation ориентация резистора на экране
     */
    QString orientation;

    /**
     * @brief c1 коннектор для присоединения проводов
     */
    Connector* c1;

    /**
     * @brief c2 коннектор для присоединения проводов
     */
    Connector* c2;

    /**
     * @brief setConnectorPosition устанавливает позицию коннекторов
     */
    void setConnectorPosition();
signals:

public slots:

};

#endif // RESISTOR_H
