#ifndef RESISTOR_H
#define RESISTOR_H

#include <QObject>
#include "src/c++/Elements/element.h"

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
    virtual void setPosition(int x, int y); //установка позиции на экране
    virtual void connect(int x,int y); //присоединение другого проводника
    virtual ~Resistor();
private:
    int x; //координаты
    int y;
    int height; //высота резистора
    int width; //ширина
signals:

public slots:

};

#endif // RESISTOR_H
