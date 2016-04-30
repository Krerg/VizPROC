#ifndef DESTROYEVENT_H
#define DESTROYEVENT_H

#include <QObject>

class DestroyEvent : public QObject
{
    Q_OBJECT
public:
    explicit DestroyEvent(QObject *parent = 0);

signals:

public slots:

};

#endif // DESTROYEVENT_H
