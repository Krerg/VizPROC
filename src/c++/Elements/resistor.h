#ifndef RESISTOR_H
#define RESISTOR_H

#include <QObject>
#include "src/c++/Elements/element.h"

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
    virtual ~Resistor();
private:
    const QString name = "res";
    int x;
    int y;
    int height;
    int width;
signals:

public slots:

};

#endif // RESISTOR_H
