#ifndef AMPERAGEVISUALISATIONHANDLER_H
#define AMPERAGEVISUALISATIONHANDLER_H

#include <QObject>
#include "src/c++/Event/initevent.h"
#include "src/c++/Elements/element.h"
#include "src/c++/Visualization/visualization.h"
#include <QHash>

class AmperageVisualisationHandler : public QObject,Visualization
{
    Q_OBJECT
public:
    explicit AmperageVisualisationHandler(QObject *parent = 0);

    virtual void init(InitEvent* event);

    virtual void nextStep(NextStepEvent* event);

    virtual void destroy(DestroyEvent* event);

private:

    /**
     * @brief getResistance вычисляет сумму сопротивлений элементов
     * @param elements списко элементов
     * @return сопротивление
     */
    QHash<QString,double>* getBranchParameters(QList<Element*>* elements);

    /**
     * @brief getBranchAmperage расчет силы тока на ветви (если это возможно)
     * @param branch ветвь
     * @param x значения потенциалов
     * @return значения чилы тока (-1 если не удалось)
     */
    double getBranchAmperage(Branch* branch, double* x);

    /**
     * @brief setAmperageOnWires
     * @param connectedBranches
     * @param branch
     */
    void setAmperageOnWires(QList<Branch*> *connectedBranches, Branch* branch, double *x);

    /**
     * @brief setAmperageOnWires
     * @param branch
     * @param amperage
     */
    void setAmperageOnWires(Branch* branch, double amperage, double *x);

    /**
     * @brief trySetAmperage
     * @param branch
     * @return
     */
    bool trySetAmperage(Branch* branch, double*);

    /**
     * @brief trySeyAmperageOnWire
     * @param wire
     * @return
     */
    bool trySeyAmperageOnWire(Wire* wire);

    /**
     * @brief checkAllWires
     */
    void checkAllWires();

    /**
     * @brief setAmperageOnWire
     * @param w
     * @param elem
     * @param direction
     */
    void setAmperageOnWire(Wire* w, Element* elem, bool direction);

signals:

public slots:

};

#endif // AMPERAGEVISUALISATIONHANDLER_H
