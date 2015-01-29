#include "graph.h"
#include "src/c++/Elements/resistor.h"
#include <QDebug>

Graph::Graph(QObject *parent) :
    QObject(parent)
{
    this->lastFreeNumber = 0;
    this->graph = new QList<Wire*>();
}

void Graph::addVertex(Wire *w)
{
    if(w->getConnectedWires()->size()==0)
    {
        /*
         * Добавлем в граф только те провода, который не присоединены к дургим,
         * то есть который образуют новый потенциал
         *
         */
        this->graph->append(w);
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
        QList<Wire*>::iterator i;
        int numb=0;
        //пронумеровываем все потенциалы
        int tmp;
        for(i=graph->begin();i!=graph->end();i++)
        {
            tmp=(*i)->isGround();
            if(tmp==1)
            {
                continue;
            }
            else if (tmp==2)
            {
                (*i)->setNumber(-2,true);
            }
            else
            {
                (*i)->setNumber(numb++,true);
            }
     }
        //выделяем память по массив
        this->array = new float*[--numb];
        numb++;
        for(int count=0;count<numb;count++)
        {
            array[count] = new float [numb];
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
            if((*i)->getNumber()<0)
            {
                continue;
            }
            temp = (*i)->getAllConnectedElements();
            for(j=temp->begin();j!=temp->end();j++)
            {
                if((*j)->getName()=="Res")
                {
                    Resistor* y = (Resistor*)(*j);
                    tmp = y->getAnotherWire((*i)->getNumber())->getNumber();
                    array[(*i)->getNumber()][(*i)->getNumber()] += y->getValue();
                    if(tmp==-2)
                    {
                        //заменить двойку блеа
                      array[(*i)->getNumber()][numb-1]=2;
                    }
                    else
                    {
                        array[(*i)->getNumber()][tmp] -= y->getValue();
                    }
                }
                else
                {

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
        for(int j=0;j<n;j++)
        {
            qDebug()<<array[i][j];
        }
    }
}
