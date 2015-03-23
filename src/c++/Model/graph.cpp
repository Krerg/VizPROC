#include "graph.h"
#include "src/c++/Elements/resistor.h"
#include "src/c++/Elements/emf.h"
#include <QDebug>

Graph::Graph(QObject *parent) :
    QObject(parent)
{
    this->lastFreeNumber = 0;
    this->graph = new QMap<Wire*,int*>();
}

void Graph::addVertex(Wire *w)
{
    if(w->getConnectedWires()->size()==1)
    {
        /*
         * Добавлем в граф только те провода, который не присоединены к дургим,
         * то есть который образуют новый потенциал
         *
         */
        int *i = new int[2];
        i[0]=0;
        i[1]=0;
        this->graph->insert(w,i);
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
    //если мы имемм 2 потенциала и больше
    if(this->graph->size()>1)
    {
        QMap<Wire*,int*>::iterator i;
        int numb=0;
        //пронумеровываем все потенциалы
        int tmp;
        for(i=graph->begin();i!=graph->end();i++)
        {
            if(i.key()->isGround()) {
                i.key()->setNumber(-1,true);
                continue;
            }
            i.key()->setNumber(numb++,true);
        }
        //выделяем память по массив
        this->array = new float*[numb];

        for(int count=0;count<numb;count++)
        {
            array[count] = new float[numb+1];
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
                    if(tmp>0) {
                    array[(*i)->getNumber()][tmp] -= y->getValue();
                    }
                } else if((*j)->getName()=="Emf") {
                    EMF* emfTemp = (EMF*)(*j);
                    //прибавляем к правой части помноженная на проводимость (большое число будет)
                    //не забываем про направление

                    //прибавляем к диагональному элементу

                    //и соответсвенно к тому элементу через который он присоединен

                }
            }
        }
        this->showMatrix(numb);
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
