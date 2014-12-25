#ifndef RESISTOR_H
#define RESISTOR_H

#include <QObject>
#include "src/c++/Elements/element.h"
#include "src/c++/Elements/connector.h"

class Resistor : public QObject,Element
{
    Q_OBJECT
public:
    explicit Resistor(QObject *parent = 0);
    virtual void paintComponent(); //отрисовка резистора на экране
    void setHeight(int height); //установка высоты
    void setWidth(int width); //установка ширины
    int getWidth();
    int getHeight();
    const QString HORIZONTAL_ORIENTATION = "HORIZONTAL";
    const QString VERTICAL_ORIENTATION = "VERTICAL";
    virtual void setPosition(int x, int y); //установка позиции на экране
    virtual void connect(int x,int y); //присоединение другого проводника
    virtual bool isSelected(int x, int y); //проверка на то, что мышь кликнула по резистору
    virtual void disableSelected(); //снятие выделенеия с элемента
    virtual void enableSelected();
    virtual void changeOrientation();
    virtual int getX();
    virtual int getY();
    virtual ~Resistor();
private:
    bool selected;
    bool pointed;
    int x; //координаты
    int y;
    int height; //высота резистора
    int width; //ширина
    int pinLength; //длина выводов резистора
    QString orientation;
    Connector* c1;
    Connector* c2;
signals:

public slots:

};

#endif // RESISTOR_H
