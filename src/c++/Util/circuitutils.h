#ifndef CIRCUITUTILS_H
#define CIRCUITUTILS_H

#include <QObject>

class CircuitUtils : public QObject
{
    Q_OBJECT
public:
    explicit CircuitUtils(QObject *parent = 0);

    /**
     * @brief getAmperage
     * @param potentialNumber
     * @param x
     */
    static double getAmperage(int potentialNumber, double* x);

signals:

public slots:

};

#endif // CIRCUITUTILS_H
