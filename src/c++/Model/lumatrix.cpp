#include "lumatrix.h"

LUMatrix::LUMatrix(QObject *parent) :
    QObject(parent)
{
}

double* LUMatrix::compute(int n)
{
    this->x = new double[n];

    return x;
}

void LUMatrix::setA(double **a)
{
    this->a = a;
}

void LUMatrix::setB(double *b)
{
    this->b = b;
}
