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
    ComponentManager* componentManger;
signals:
    void addResistor(int x, int y);
public slots:
    void mouseClicked(QMouseEvent* event);
    void mouseReleased(QMouseEvent* event);
};

#endif // EVENTHANDLER_H
