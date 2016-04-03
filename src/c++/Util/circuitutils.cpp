#include "circuitutils.h"

CircuitUtils::CircuitUtils(QObject *parent) :
    QObject(parent)
{
}

double CircuitUtils::getAmperage(int potentialNumber, double *x)
{
    if(potentialNumber==0) {
        return 0.0;
    }
    return x[potentialNumber-1];
}
