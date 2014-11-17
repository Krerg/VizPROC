#ifndef ELEMENT_H
#define ELEMENT_H

#include <QObject>

class Element
{
//Pure virtual
public:
    virtual void setPosition(int x, int y)=0; //установка позиции на экране элемента
    virtual void connect(int x, int y)=0; //присоединение к элементу провода
    virtual void paintComponent()=0; //отрисовка элемента на экране
    virtual bool isSelected(int x,int y)=0; //проверка на то, что кликнули по этому элементу
    virtual void disableSelected()=0; //убираем выделение с элемента
    virtual void enableSelected()=0; //делаем элемент выбранным
    virtual void changeOrientation()=0; //изменение ориентации элемента
    virtual int getX()=0;
    virtual int getY()=0;
    virtual ~Element()=0; //деструктор
signals:

public slots:

};

#endif // ELEMENT_H
