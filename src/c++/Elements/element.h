#ifndef ELEMENT_H
#define ELEMENT_H

#include <QObject>

class Element
{

public:
    virtual void setPosition(int x, int y)=0;
    virtual void connect(int x, int y)=0;
    virtual void paintComponent()=0;
    virtual ~Element()=0;
signals:

public slots:

};

#endif // ELEMENT_H
