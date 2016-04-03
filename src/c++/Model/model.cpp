#include "model.h"
#include "src/c++/Elements/resistor.h"
#include "src/c++/Elements/emf.h"
#include "src/c++/Elements/diode.h"
#include "src/c++/Util/stringvalues.h"
#include <QDebug>
#include "src/c++/Controller/applicationcontext.h"
#include "src/c++/Model/branch.h"

bool Model::DIODE_BRANCH_CHECK = true;

Model::Model(QObject *parent) :
    QObject(parent)
{
    this->preGraph = new QMap<Wire*,int*>();
    this->matrixResolver = new LUMatrix(parent);
    this->potentialsNumber = 0;
    this->diodes = new QList<Diode*>();
    this->graph = new Graph(parent);
    this->array = NULL;
}

bool Model::isDiodeBranchCheck()
{
    return Model::DIODE_BRANCH_CHECK;
}

void Model::addVertex(Wire *w)
{
    /*
     *  первый бит номер ветки, второй бит диодная ветка или нет (0 - не диодная, 1,2,3 - диодная)
     * и третий нужно ли при расчетах прибавлять (потенциал состоит из нескольких проводов, незачем каждый провод считать)
     *
    */
    int *i = new int[3];
    i[0]=-1;
    i[1]=0;
    this->preGraph->insert(w,i);

    if(w->getConnectedWires()->size()!=1)
    {
       i[2]=1;
    } else {
       i[2]=0;
    }
}

void Model::deleteVertex(Wire *w)
{
    delete this->preGraph->value(w);
    this->preGraph->remove(w);
}

double* Model::calculate()
{
    double *x;
    if(this->preGraph->size()>1) {
            QMap<Wire*,int*>::iterator i;
            //пронумеровываем все потенциалы
            int tmp;
            clearCurcuitArray();
            //ну а теперь заполняем ссответсвенно
            QList<Element*> *temp;
            QList<Element*>::iterator j;
            for(i=preGraph->begin();i!=preGraph->end();i++)
            {
                //пропускаем если это земля
                if(i.key()->getNumber()<0)
                {
                    continue;
                }
                //пропускаем если уже для этого потенциала все расчитано
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
                        //и вычитаем из соответствующего потенциала
                        if(tmp>=0) {
                            array[i.key()->getNumber()][tmp] -= y->getValue();
                        }
                    } else if((*j)->getName()=="Emf") {
                        EMF* emfTemp = (EMF*)(*j);
                        tmp = emfTemp->getAnotherWire(i.key()->getNumber())->getNumber();
                        //прибавляем к правой части помноженная на проводимость (большое число будет)
                        //не забываем про направление
                        array[i.key()->getNumber()][potentialsNumber]+=emfTemp->getEmfDirection(i.key()->getNumber())*emfTemp->getConductivity()*emfTemp->getVoltage();

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

                        array[i.key()->getNumber()][potentialsNumber]+=diodeTemp->getEmfDirection(i.key()->getNumber())*diodeTemp->getConductivity()*diodeTemp->getVoltage();

                        //прибавляем к диагональному элементу
                        array[i.key()->getNumber()][i.key()->getNumber()] += diodeTemp->getConductivity();

                        //и соответсвенно к тому элементу через который он присоединен
                        if(tmp>=0) {
                            array[i.key()->getNumber()][tmp] -= diodeTemp->getConductivity();
                        }
                    }
                }
                //очищаем список эдементов
                delete temp;
            }

            //решаем получившуюся матрицу
            this->showMatrix(potentialsNumber);
            matrixResolver->setA(*(&array));
            x = matrixResolver->compute(potentialsNumber);
            for(int i=0;i<potentialsNumber;i++) {
                qDebug()<<x[i];
            }
            return x;
    }
}

void Model::deleteCircuitArray()
{
    for(int i=0;i<potentialsNumber;i++) {
        delete array[i];
    }
    delete array;
}

double *Model::getEmptyResult()
{
    double* emptyResult = new double[potentialsNumber];
    for(int i=0;i<potentialsNumber;i++) {
        emptyResult[i]=0;
    }
    return emptyResult;
}

void Model::start()
{
    DIODE_BRANCH_CHECK = true;
    initCurciutArray();
    double *calculationResult = NULL;
    if(diodes->size()<=0) {
        calculationResult = calculate();
    } else {
        graph->initGraph(potentialsNumber+1);
        allocateBranches(false);
        graph->optimizeGraph();
        QString initStatus = graph->isolateDiodeBranches();
        if(initStatus == StringValues::GRAPH_ISOLATION_NEED_DIODE_OPEN) {
            if(!graph->openNextBranch(calculationResult)) {
                emit circuitError(StringValues::NO_SUCH_COLTAGE_FOR_OPEN_DIODE_MESSAGE);
                emit setLock();
                emit hideStartButton();
                emit startVisualisation(NULL,getEmptyResult(),potentialsNumber);
                return;
            }
        } else if(initStatus == StringValues::GRAPH_ISOLATION_ERROR) {
            // TODO emit error(errorMessage);
            return;
        }

        while(true) {
            if(calculationResult!=NULL) {
                delete calculationResult;
            }
            calculationResult = calculate();
            if(!graph->openNextBranch(calculationResult)) {
                break;
            }
        }
    }
    emit setLock();
    emit hideStartButton();

    this->DIODE_BRANCH_CHECK = false;
    graph->clearAllocatedArray();
    allocateBranches(true);
    graph->optimizeGraph();
    emit startVisualisation(graph->getAllBranches(),calculationResult,potentialsNumber);
}

void Model::addDiode(Diode *d)
{
    this->diodes->append(d);
}

void Model::showMatrix(int n)
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

void Model::initCurciutArray()
{
    potentialsNumber=0;
    QMap<Wire*,int*>::Iterator i;
    for(i=preGraph->begin();i!=preGraph->end();i++)
    {
        if(preGraph->value(i.key())[2]==1) {
            continue;
        }
        if(i.key()->isGround()) {
            i.key()->setNumber(-1,true);
            continue;
        }
        i.key()->setNumber(potentialsNumber++,true);
    }

    if(this->array!=NULL) {
        deleteCircuitArray();
    }

    this->array = new double*[potentialsNumber];

    for(int count=0;count<potentialsNumber;count++)
    {
        array[count] = new double[potentialsNumber+1];
    }
}

void Model::clearCurcuitArray()
{
    for(int i=0;i<potentialsNumber;i++)
    {
        for(int j=0;j<potentialsNumber+1;j++)
        {
            array[i][j] = 0.0;
        }
    }
}

void Model::allocateBranches(bool wireCheck)
{
    int firstConnectedVertex;
    int secondConnectedVertex;
    foreach (Element* elem, *ApplicationContext::getComponentManager()->getElements()) {
        if(elem->getName() == StringValues::GROUND_NAME) {
            continue;
        }
        Branch* branch = new Branch();
        foreach (Connector* c, *elem->getConnectors()) {
            if(c->getConnectedWire()!=NULL) {
                if(wireCheck && !c->getConnectedWire()->isOpened()) {
                    delete branch;
                    branch=NULL;
                    break;
                }
                branch->addWire(c->getConnectedWire(),false);
            } else {
                //TODO throw exception
            }
        }
        if(branch==NULL) {
            continue;
        }
        branch->addElement((Element*)elem,false,DIODE_BRANCH_CHECK);
        if(elem->getName() != StringValues::TRANSISTOR_NAME) {
            firstConnectedVertex = elem->getConnectors()->first()->getConnectedWire()->getNumber();
            secondConnectedVertex = elem->getConnectors()->last()->getConnectedWire()->getNumber();
            graph->addEdge(branch,firstConnectedVertex+1,secondConnectedVertex+1);
        } else {
            //TODO next release 2.0 transistor logic
        }
    }
}

QList<Branch *> *Model::getConnectedBranches(int vertexNumber)
{
    graph->getConnectedBranches(vertexNumber);
}

Model::~Model()
{
    delete diodes;
    delete preGraph;
}
