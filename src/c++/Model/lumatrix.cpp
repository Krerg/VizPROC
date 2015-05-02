#include "lumatrix.h"
#include <QDebug>

LUMatrix::LUMatrix(QObject *parent) :
    QObject(parent)
{
}

double* LUMatrix::compute(int n)
{
    this->x = new double[n];

    //создаем правую и левую матрицы
    double** L = new double*[n];
    double** U = new double*[n];

    for(int i=0;i<n;i++) {
        L[i] = new double[n];
        U[i] = new double[n];
    }

    int i = 0, j = 0, k = 0;
       for (i = 0; i < n; i++)
       {
           for (j = 0; j < n; j++)
           {
               if (j < i)
                   L[j][i] = 0;
               else
               {
                   L[j][i] = a[j][i];
                   for (k = 0; k < i; k++)
                   {
                       L[j][i] = L[j][i] - L[j][k] * U[k][i];
                   }
               }
           }
           for (j = 0; j < n; j++)
           {
               if (j < i)
                   U[i][j] = 0;
               else if (j == i)
                   U[i][j] = 1;
               else
               {
                   U[i][j] = a[i][j] / L[i][i];
                   for (k = 0; k < i; k++)
                   {
                       U[i][j] = U[i][j] - ((L[i][k] * U[k][j]) / L[i][i]);
                   }
               }
           }
       }

    double *y = new double[n];
    double sum;
    for(i=0;i<n;i++) {
        sum=0;
        for(j=0;j<i;j++) {
            sum+=L[i][j]*y[j];
        }
        y[i]=(a[i][n]-sum)/L[i][i];
    }

//    for(i=0;i<n;i++)
//        qDebug()<<y[i];

    for(i=n-1;i>=0;i--) {
        sum=0;
        for(j=i+1;j<n;j++) {
            sum+=x[j]*U[i][j];
        }
        x[i]=(y[i]-sum);
    }

//    for(i=0;i<n;i++)
//        qDebug()<<x[i];

    delete L;
    delete U;
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

void LUMatrix::printMatrix(double **matrix, int n)
{
    for(int i=0;i<n;i++) {
        for(int j=0;j<n;j++) {
            qDebug()<<matrix[i][j];
        }
    }
}
