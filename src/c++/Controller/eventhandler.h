#ifndef EVENTHANDLER_H
#define EVENTHANDLER_H

#include <QObject>
#include <QMouseEvent>
#include "src/c++/View/componentmanager.h"

class EventHandler : public QObject
{
    Q_OBJECT
public:
    explicit EventHandler(QObject *parent = 0);
private:

signals:
    void addResistor(int x, int y); //добавление резистора
public slots:
    void mouseClicked(QMouseEvent* event); //нажатие мыши
    void mouseReleased(QMouseEvent* event); //отпускание клавиши мыши
    void mouseMoved(QMouseEvent* event); //перетаскивание мышью
};

#endif // EVENTHANDLER_H
