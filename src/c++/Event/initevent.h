#ifndef AMPERAGEVISUALIZATIONEVENT_H
#define AMPERAGEVISUALIZATIONEVENT_H

#include <QObject>
#include <QList>
#include "src/c++/Model/branch.h"

class InitEvent : public QObject
{
    Q_OBJECT
public:
    explicit InitEvent(QObject *parent = 0);

    QList<Branch *> *getBranches() const;

    void setBranches(QList<Branch *> *value);

    double *getX() const;

    void setX(double *value);

private:

    /**
     * @brief branch
     */
    QList<Branch*>* branches;

    /**
     * @brief x
     */
    double *x;

signals:

public slots:

};

#endif // AMPERAGEVISUALIZATIONEVENT_H
