#include <QApplication>
#include "main.h"
#include "src/c++/Model/lumatrix.h"
#include <QDebug>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    int m = 5;
    int b = *(&m);
    m = 8;
    qDebug()<< b;
//    LUMatrix* luTest = new LUMatrix();
//    double **aMatrix = new double*[3];
//    double *bMatrix = new double[3];
//    for(int i=0;i<3;i++) {
//        aMatrix[i] = new double[3];
//    }
//    aMatrix[0][0]=3;
//    aMatrix[0][1]=-1;
//    aMatrix[0][2]=0;
//    aMatrix[1][0]=-2;
//    aMatrix[1][1]=1;
//    aMatrix[1][2]=1;
//    aMatrix[2][0]=2;
//    aMatrix[2][1]=-1;
//    aMatrix[2][2]=4;
//    bMatrix[0]=5;
//    bMatrix[1]=0;
//    bMatrix[2]=15;
//    luTest->setA(aMatrix);
//    luTest->setB(bMatrix);
//    luTest->compute(3);

    //Запуск контроллера инициализации приложения
    InitController *i = new InitController();
    i->startProgramm();
    return a.exec();
}

