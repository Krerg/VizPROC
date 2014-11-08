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
    virtual ~Element()=0; //деструктор
signals:

public slots:

};

#endif // ELEMENT_H
