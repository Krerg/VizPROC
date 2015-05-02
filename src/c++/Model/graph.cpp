#include "graph.h"
#include "src/c++/Elements/resistor.h"
#include "src/c++/Elements/emf.h"
#include "src/c++/Elements/diode.h"
#include <QDebug>

Graph::Graph(QObject *parent) :
    QObject(parent)
{
    this->lastFreeNumber = 0;
    this->graph = new QMap<Wire*,int*>();
    this->matrixResolver = new LUMatrix(this);
}

void Graph::addVertex(Wire *w)
{
    int *i = new int[3]; //первый бит номер ветки, второй бит диодная ветка или нет и третий нужно ли при рпсчетах прибавлять
    i[0]=-1;
    i[1]=0;
    this->graph->insert(w,i);

    if(w->getConnectedWires()->size()!=1)
    {
       i[2]=1;
     } else {
       i[2]=0;
    }
}

void Graph::deleteVertex(Wire *w)
{

}

int Graph::getNewNumber()
{
    return lastFreeNumber++;
}

void Graph::start()
{
    //processGraph(graph->firstKey(),getNewNumber());
    //если мы имемм 2 потенциала и больше
    if(this->graph->size()>1)
    {
        QMap<Wire*,int*>::iterator i;
        int numb=0;
        //пронумеровываем все потенциалы
        int tmp;
        for(i=graph->begin();i!=graph->end();i++)
        {
            if(i.value()[2]==1) {
                continue;
            }
            if(i.key()->isGround()) {
                i.key()->setNumber(-1,true);
                continue;
            }
            i.key()->setNumber(numb++,true);
        }
        //выделяем память по массив
        this->array = new double*[numb];

        for(int count=0;count<numb;count++)
        {
            array[count] = new double[numb+1];
        }
        //заполняем массив нулями
        for(int i=0;i<numb;i++)
        {
            for(int j=0;j<numb+1;j++)
            {
                array[i][j] = 0.0;
            }
        }
        //ну а теперь заполняем ссответсвенно
        QList<Element*> *temp;
        QList<Element*>::iterator j;
        for(i=graph->begin();i!=graph->end();i++)
        {
            //пропускаем если это земля
            if(i.key()->getNumber()<0)
            {
                continue;
            }
            //берем все присоединенные элементы и заносим в матрицу
            temp = i.key()->getAllConnectedElements();
            for(j=temp->begin();j!=temp->end();j++)
            {
                if((*j)->getName()=="Res") {
                    Resistor* y = (Resistor*)(*j);
                    //берем потенциал с другого конца ихик
                    tmp = y->getAnotherWire(i.key()->getNumber())->getNumber();
                    //прибавляем проводимость резистора к диагональному элементу
                    array[i.key()->getNumber()][i.key()->getNumber()] += y->getValue();
                    if(tmp>=0) {
                    array[i.key()->getNumber()][tmp] -= y->getValue();
                    }
                } else if((*j)->getName()=="Emf") {
                    EMF* emfTemp = (EMF*)(*j);
                    tmp = emfTemp->getAnotherWire(i.key()->getNumber())->getNumber();
                    //прибавляем к правой части помноженная на проводимость (большое число будет)
                    //не забываем про направление
                    qDebug()<<"Direction"<<emfTemp->getEmfDirection(i.key()->getNumber());
                    qDebug()<<"Value"<<emfTemp->getConductivity()*emfTemp->getVoltage();

                    array[i.key()->getNumber()][numb]=emfTemp->getEmfDirection(i.key()->getNumber())*emfTemp->getConductivity()*emfTemp->getVoltage();

                    //прибавляем к диагональному элементу
                    array[i.key()->getNumber()][i.key()->getNumber()] += emfTemp->getConductivity();


                    //и соответсвенно к тому элементу через который он присоединен
                    if(tmp>=0) {
                    array[i.key()->getNumber()][tmp] -= emfTemp->getConductivity();
                    }
                }
            }
        }

        this->showMatrix(numb);
        matrixResolver->setA(*(&array));
        double *x = matrixResolver->compute(numb);

        for(int i=0;i<numb;i++) {
            qDebug()<<x[i];
        }

        emit startVisualisation(graph,x,numb);



    }
}

void Graph::showMatrix(int n)
{
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<n+1;j++)
        {
            qDebug()<<array[i][j];
        }
        qDebug()<<endl;
    }
}

void Graph::processGraph(Wire* first,int number)
{
    if(this->graph->value(first)[0]>=0) {
        return;
    }
    this->graph->value(first)[0]=number;
    QList<Element*>* connectedElems = first->getConnectedElements();
    QList<Element*>::iterator i;
    for(i=connectedElems->begin();i!=connectedElems->end();i++) {
        if((*i)->getName()=="Diode") {
            qDebug()<<"diode";
           Diode* y = (Diode*)(*i);
           //требует реализации
        } else if((*i)->getName()=="Emf") {
            EMF* emfTemp = (EMF*)(*i);
            processGraph(emfTemp->getAnotherWire(first),number);
        } else if((*i)->getName()=="Res") {
            Resistor* resTemp = (Resistor*)(*i);
            processGraph(resTemp->getAnotherWire(first),number);
        }

    }
    if(first->getConnectedWires()->size()>=2) {
        QList<Wire*>::iterator i;
        for(i=first->getConnectedWires()->begin();i!=first->getConnectedWires()->end();i++) {
            processGraph((*i),this->getNewNumber());
        }
    }
}
