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
    this->numberOfIterations = 0;
    this->diodesBranches = new QList<DiodeBranch*>();
    this->diodes = new QList<Diode*>();
}

void Graph::addVertex(Wire *w)
{
    //первый бит номер ветки, второй бит диодная ветка или нет (0 - не диодная, 1,2,3 - диодная) и третий нужно ли при расчетах прибавлять
    int *i = new int[3];
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
    delete this->graph->value(w);
    this->graph->remove(w);
}

int Graph::getNewNumber()
{
    return lastFreeNumber++;
}

void Graph::start()
{
    if(diodes->size()>0) {
        processGraph(graph->firstKey(),getNewNumber());
    }
    double *x;
    int numb;
    QList<DiodeBranch*>::Iterator diodeBranchIterator;
    diodeBranchIterator = this->diodesBranches->begin();
    do{
    if(this->graph->size()>1)
    {

        QMap<Wire*,int*>::iterator i;
        numb=0;
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
            if(array[i.key()->getNumber()][i.key()->getNumber()]!=0) {
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
                } else if((*j)->getName()=="Diode") {
                    Diode* diodeTemp = (Diode*)(*j);
                    if(!diodeTemp->isOpened()) {
                        continue;
                    }
                    tmp = diodeTemp->getAnotherWire(i.key()->getNumber())->getNumber();

                    array[i.key()->getNumber()][numb]=diodeTemp->getEmfDirection(i.key()->getNumber())*diodeTemp->getConductivity()*diodeTemp->getVoltage();

                    //прибавляем к диагональному элементу
                    array[i.key()->getNumber()][i.key()->getNumber()] += diodeTemp->getConductivity();

                    //и соответсвенно к тому элементу через который он присоединен
                    if(tmp>=0) {
                    array[i.key()->getNumber()][tmp] -= diodeTemp->getConductivity();
                    }
                }
            }
        }

        this->showMatrix(numb);
        matrixResolver->setA(*(&array));
        x = matrixResolver->compute(numb);

        for(int i=0;i<numb;i++) {
            qDebug()<<x[i];
        }
    }
    if(diodeBranchIterator==diodesBranches->end())
        break;

        if(diodesBranches->size()!=0) {
            //вот и весь алгоритм
            if((*diodeBranchIterator)->checkBranch(x)) {
                (*diodeBranchIterator)->open();
            }
            diodeBranchIterator++;
        }

    } while (true);
        emit startVisualisation(graph,x,numb);
    }

void Graph::addDiode(Diode *d)
{
    this->diodes->append(d);
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
    int i=0;
    foreach (Diode* d, *diodes) {
        /**
         * Для каждого диода берем коннектор и провод, и утснавливам флаги на
         * проводах, что это диодная ветка
         */
        Connector* tmpConnector = d->getConnector1();
        Wire* tmpWire = tmpConnector->getConnectedWire();
        Element* tmpElem = (Element*)d;
        Element* tmpElem2;
        QList<Element*>* tmpList;
        DiodeBranch* currentBranch = new DiodeBranch(this);
        currentBranch->setGraph(graph);
        currentBranch->addDiode(d);
        diodesBranches->append(currentBranch);
        i++;
        while(true) {
            currentBranch->addWire(tmpWire);
            graph->value(tmpWire)[1]=i;
            if(tmpWire->getConnectedWires()->size()>1) {
                currentBranch->setUpWire(tmpWire);
                break;
            } else {
                tmpList = tmpWire->getConnectedElements();
                //смотрим в какую сторону надо идти
                if(tmpList->at(0)==tmpElem) {
                    tmpElem2 = tmpList->at(1);
                    if(tmpElem2->getName() == "Res") {
                        tmpWire = ((Resistor*)tmpElem2)->getAnotherWire(tmpWire);
                        tmpElem = tmpElem2;
                    } else if(tmpElem2->getName() == "Emf") {
                        tmpWire = ((EMF*)tmpElem2)->getAnotherWire(tmpWire);
                        tmpElem = tmpElem2;
                    }
                } else {
                    tmpElem2 = tmpList->at(0);
                    if(tmpElem2->getName() == "Res") {
                        tmpWire = ((Resistor*)tmpElem2)->getAnotherWire(tmpWire);
                        tmpElem = tmpElem2;
                    } else if(tmpElem2->getName() == "Emf") {
                        tmpWire = ((EMF*)tmpElem2)->getAnotherWire(tmpWire);
                        tmpElem = tmpElem2;
                    }
                }
            }
        }

        //идем в другую сторону
        tmpConnector = d->getConnector2();
        tmpWire = tmpConnector->getConnectedWire();
        tmpElem = (Element*)d;
        while(true) {
            currentBranch->addWire(tmpWire);
            graph->value(tmpWire)[1]=i;
            if(tmpWire->getConnectedWires()->size()>1) {
                currentBranch->setDownWire(tmpWire);
                break;
            } else {
                tmpList = tmpWire->getConnectedElements();
                //смотрим в какую сторону надо идти
                if(tmpList->at(0)==tmpElem) {
                    tmpElem2 = tmpList->at(1);
                    if(tmpElem2->getName() == "Res") {
                        tmpWire = ((Resistor*)tmpElem2)->getAnotherWire(tmpWire);
                        tmpElem = tmpElem2;
                    } else if(tmpElem2->getName() == "Emf") {
                        tmpWire = ((EMF*)tmpElem2)->getAnotherWire(tmpWire);
                        tmpElem = tmpElem2;
                    }
                } else {
                    tmpElem2 = tmpList->at(0);
                    if(tmpElem2->getName() == "Res") {
                        tmpWire = ((Resistor*)tmpElem2)->getAnotherWire(tmpWire);
                        tmpElem = tmpElem2;
                    } else if(tmpElem2->getName() == "Emf") {
                        tmpWire = ((EMF*)tmpElem2)->getAnotherWire(tmpWire);
                        tmpElem = tmpElem2;
                    }
                }
            }
        }

    }
}
