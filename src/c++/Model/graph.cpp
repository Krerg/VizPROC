#include "graph.h"
#include "src/c++/Util/stringvalues.h"
#include "src/c++/Util/constvalues.h"
#include "src/c++/Elements/emf.h"

Graph::Graph(QObject *parent) :
    QObject(parent)
{
    this->matrixSize = 0;
    this->adjacencyMatrix = NULL;
    this->diodeBranches = new QList<Branch*>;
    this->closedDiodeBranches = new QStack<Branch*>;
}

void Graph::addEdge(Branch *branch, int vertexNumber1, int vertexNumber2)
{
    if(branch!=NULL) {
        if(branch->isDiodeBranch()) {
            this->diodeBranches->append(branch);
        }
        branch->setVertexNumber1(vertexNumber1);
        branch->setVertexNumber2(vertexNumber2);
        nullSafeAddDirectEdge(branch,vertexNumber1,vertexNumber2);
    }
}

QList<Branch *> *Graph::getConnectedBranches(int vertexNumber)
{
    QList<Branch*>* connectedBranches = new QList<Branch*>();
    for(int i=0;i<matrixSize;i++) {
        if(adjacencyMatrix[vertexNumber][i]!=NULL && adjacencyMatrix[vertexNumber][i]->size()>1) {
            connectedBranches->append(*adjacencyMatrix[vertexNumber][i]);
        }
    }
    return connectedBranches;
}

QList<Branch *> *Graph::getAllBranches()
{
    QList<Branch*>* branches = new QList<Branch*>();
    for(int i=0;i<matrixSize;i++) {
        for(int j=0;j<i+1;j++) {
            if(adjacencyMatrix[i][j]!=NULL) {
                branches->append(*adjacencyMatrix[i][j]);
            }
        }
    }
    return branches;
}

void Graph::deleteEdge(int firstVertexNumber, int secondVertexNumber)
{
    nullSafeDeleteDirectEdge(firstVertexNumber,secondVertexNumber);
    nullSafeDeleteDirectEdge(secondVertexNumber,firstVertexNumber);
}

void Graph::initGraph(int vertexNumber)
{
    if(adjacencyMatrix!=NULL) {
        deleteAdjencyMatrix();
    }
    this->matrixSize = vertexNumber;
    this->adjacencyMatrix = new QList<Branch*>**[vertexNumber];
    for(int i=0;i<vertexNumber;i++) {
        for(int j=0;j<i+1;j++) {
            this->adjacencyMatrix[i] = new QList<Branch*>*[j+1];
        }
    }

    for(int i=vertexNumber-2;i>=0;i--) {
        for(int j=vertexNumber-1;j>i;j--) {
            this->adjacencyMatrix[i][j] = this->adjacencyMatrix[j][i];
        }
    }

    clearAllocatedArray();
}

bool Graph::openNextBranch(double *calculationResult)
{
    if(this->closedDiodeBranches!=NULL && this->closedDiodeBranches->size()>0) {
        Branch* branch;
        while(true) {
            if(closedDiodeBranches->size()==0) {
                return false;
            }
            branch = this->closedDiodeBranches->pop();
            if(checkDiodeBranchTreshold(calculationResult,branch)) {
                branch->open();
                return true;
            }
        }
    } else {
        return false;
    }
}

QString Graph::isolateDiodeBranches()
{
    if(matrixSize<=0 || diodeBranches->size()<=0) {
        return StringValues::GRAPH_ISOLATION_ERROR;
    } else {
        while(!diodeBranches->isEmpty()) {
            foreach (Branch* diodeBranch, *diodeBranches) {
                if(tryCloseDiodeBranch(diodeBranch)) {
                    closedDiodeBranches->push(diodeBranch);
                    //TODO заменить на итератор для повышения производительности
                    diodeBranches->removeAll(diodeBranch);
                    optimizeGraph();
                } else {
                    addEdge(diodeBranch,diodeBranch->getVertexNumber1(),diodeBranch->getVertexNumber2());
                }
            }
        }
        if(matrixIsEmpty()) {
            return StringValues::GRAPH_ISOLATION_NEED_DIODE_OPEN;
        } else {
            return StringValues::GRAPH_ISOLATION_COMPLETE;
        }
    }
}

bool Graph::matrixIsEmpty()
{
    for(int i=0;i<matrixSize;i++) {
        for(int j=0;j<matrixSize;j++) {
            if(adjacencyMatrix[i][j]!=NULL && adjacencyMatrix[i][j]->size()>0) {
                return false;
            }
        }
    }
    return true;
}

Branch *Graph::checkBranchList(QList<Branch *> *branchList)
{
    if(branchList->size()!=1) {
        //TODO на этом месте можно сказать какую диодную ветку можно спокойно закрыть
        return NULL;
    }
    return branchList->first();
}

void Graph::optimizeGraph()
{
    //список присоединенных вершин для рассматриваемого узла
    QList<int> *connectedVertexes = new QList<int>();
    for(int i=0;i<matrixSize;i++) {
        for(int j=0;j<matrixSize;j++) {
            if(adjacencyMatrix[i][j]!=NULL && adjacencyMatrix[i][j]->size()==1) {
                connectedVertexes->append(j);
            } else if(adjacencyMatrix[i][j]!=NULL && adjacencyMatrix[i][j]->size()==2) {
                //проверка на цикл между двумя вершинами
                if(hasCycle(i,j)) {
                    unionEdges(i,j,j);
                }
            }
        }
        //если кол-во веток равно 2, то оптимизируем граф
        if(connectedVertexes->size()==2) {
            unionEdges(i,connectedVertexes->first(),connectedVertexes->last());
        }
        connectedVertexes->clear();
    }
    delete connectedVertexes;
}

void Graph::nullSafeDeleteDirectEdge(int vertexNumber1, int vertexNumber2)
{
    if(adjacencyMatrix[vertexNumber1][vertexNumber2]) {
        adjacencyMatrix[vertexNumber1][vertexNumber2]->clear();
    }
}

bool Graph::hasEmfCycle(int vertexNumber1, int vertexNumber2)
{
    if(adjacencyMatrix[vertexNumber1][vertexNumber2]!=NULL) {
        QList<Branch*>* br = adjacencyMatrix[vertexNumber1][vertexNumber2];
        if(adjacencyMatrix[vertexNumber1][vertexNumber2]->size()>1) {
            foreach (Branch* br, *adjacencyMatrix[vertexNumber1][vertexNumber2]) {
                if(br->isHasEmf()) {
                    return true;
                }
            }
        }
    }
    return false;
}

bool Graph::onlyEmfLeft(int vertexNumber1, int vertexNumber2)
{
   if(adjacencyMatrix[vertexNumber1][vertexNumber2]!=NULL) {
       if(adjacencyMatrix[vertexNumber1][vertexNumber2]->size()==1) {
           if(adjacencyMatrix[vertexNumber1][vertexNumber2]->at(0)->isHasEmf()) {
               return true;
           }
       }
   }
   return false;
}

bool Graph::hasCycle(int vertexNumber1, int vertexNumber2)
{
    if(adjacencyMatrix[vertexNumber1][vertexNumber2]!=NULL) {
        if(adjacencyMatrix[vertexNumber1][vertexNumber2]->size()==2) {
            for(int i=0;i<matrixSize;i++) {

                if(i==vertexNumber2 || i==vertexNumber1) {
                    continue;
                }

                if(adjacencyMatrix[vertexNumber1][i]!=NULL && adjacencyMatrix[vertexNumber1][i]->size()>0) {
                    return false;
                }

                if(adjacencyMatrix[vertexNumber2][i]!=NULL && adjacencyMatrix[vertexNumber2][i]->size()>0) {
                    return false;
                }
            }
        }
    }
    return true;
}

void Graph::nullSafeAddDirectEdge(Branch *branch, int vertexNumber1, int vertexNumber2)
{
    if(!adjacencyMatrix[vertexNumber1][vertexNumber2]) {
        adjacencyMatrix[vertexNumber1][vertexNumber2] = new QList<Branch*>();
    } else if(adjacencyMatrix[vertexNumber1][vertexNumber2]->size()==1) {
        if(!adjacencyMatrix[vertexNumber1][vertexNumber2]->first()->isDiodeBranch() && !branch->isDiodeBranch()) {
            adjacencyMatrix[vertexNumber1][vertexNumber2]->first()->unionBranch(branch);
            return;
        }
    }

    adjacencyMatrix[vertexNumber1][vertexNumber2]->append(branch);
}

void Graph::clearAllocatedArray()
{
    if(matrixSize<=0) {
        return;
    }

    for(int i=0;i<matrixSize;i++) {
        for(int j=0;j<matrixSize;j++) {
            adjacencyMatrix[i][j] = NULL;
        }
    }
}

void Graph::deleteAdjencyMatrix()
{
    if(matrixSize<=0) {
        return;
    }

    for(int i=0;i<matrixSize;i++) {
        for(int j=0;j<matrixSize;j++) {
            if(adjacencyMatrix[i][j]!=NULL)
                delete adjacencyMatrix[i][j];
        }
        delete[] adjacencyMatrix[i];
    }
    delete[] adjacencyMatrix;

    matrixSize=0;
    adjacencyMatrix = NULL;
}

void Graph::unionEdges(int centralVertexNumber, int firstConnectedVertex, int secondConnectedVertex)
{
    //проверка на то, что не являются ли вершины зациклены
    if(firstConnectedVertex == secondConnectedVertex) {
        unionCycles(centralVertexNumber,firstConnectedVertex);
        return;
    }

    Branch* firstConnectedBranch = checkBranchList(adjacencyMatrix[centralVertexNumber][firstConnectedVertex]);
    if(firstConnectedBranch == NULL) {
        return;
    }

    Branch* secondConnectedBranch = checkBranchList(adjacencyMatrix[centralVertexNumber][secondConnectedVertex]);
    if(secondConnectedBranch == NULL) {
        return;
    }

    Branch* unionBranch;
    if(firstConnectedBranch->isDiodeBranch()) {
        firstConnectedBranch->unionBranch(secondConnectedBranch);
        unionBranch=firstConnectedBranch;
    } else {
        secondConnectedBranch->unionBranch(firstConnectedBranch);
        unionBranch=secondConnectedBranch;
    }

    //TODO добавить условие с объединением 2 диодных ветвей

    //нужно сохранять направленность диодных ветвей
    if(firstConnectedBranch->isDiodeBranch() || firstConnectedBranch->isHasEmf()) {
        if(firstConnectedBranch->getVertexNumber1()==centralVertexNumber) {
            firstConnectedVertex = secondConnectedVertex;
            secondConnectedVertex = firstConnectedBranch->getVertexNumber2();
        } else if(firstConnectedBranch->getVertexNumber1()==firstConnectedVertex) {
            //наверное можно убрать
        }
    } else if(secondConnectedBranch->isDiodeBranch() || firstConnectedBranch->isHasEmf()) {
        if(secondConnectedBranch->getVertexNumber1()==centralVertexNumber) {
            //наверное можно убрать
        } else if(secondConnectedBranch->getVertexNumber1()==secondConnectedVertex) {
            int tmpFirstConnectedVertex = firstConnectedVertex;
            firstConnectedVertex=secondConnectedVertex;
            secondConnectedVertex = tmpFirstConnectedVertex;
        }
    }

    unionBranch->setVertexNumber1(firstConnectedVertex);
    unionBranch->setVertexNumber2(secondConnectedVertex);
    addEdge(unionBranch,firstConnectedVertex,secondConnectedVertex);

    deleteEdge(centralVertexNumber,firstConnectedVertex);
    deleteEdge(centralVertexNumber,secondConnectedVertex);
}

void Graph::unionCycles(int vertexNumber1, int vertexNumber2)
{
    if(adjacencyMatrix[vertexNumber1][vertexNumber2]->size()==2) {
        Branch* firstBranch = adjacencyMatrix[vertexNumber1][vertexNumber2]->first();
        Branch* secondBranch = adjacencyMatrix[vertexNumber1][vertexNumber2]->last();

        if(firstBranch->isDiodeBranch()) {
            diodeBranches->removeAll(firstBranch);
        }

        if(secondBranch->isDiodeBranch()) {
            diodeBranches->removeAll(secondBranch);
        }

        if(firstBranch->isDiodeBranch() || firstBranch->isHasEmf()) {
            if(secondBranch->isDiodeBranch() || secondBranch->isHasEmf()) {
                if(firstBranch->getVertexNumber1()!=secondBranch->getVertexNumber2()) {
                    //TODO throw Exception
                }
            }
        }

        deleteEdge(vertexNumber1,vertexNumber2);
        firstBranch->unionBranch(secondBranch);
        addEdge(firstBranch,vertexNumber1,vertexNumber1);
    } else {
        //TODO throw Exception
    }
    return;
}

bool Graph::checkGraphCohesion(int firstVertexNumber, int secondVertexNumber)
{

    if(hasEmfCycle(firstVertexNumber,secondVertexNumber)) {
        return true;
    }

    if(matrixIsEmpty()) {
        //TODO throw empty matrix exception
        return true;
    }

    int firstUniqueVertexCount=0;
    int secondUniqueVertexCount=0;
    for(int i=0;i<matrixSize;i++) {
        if(adjacencyMatrix[firstVertexNumber][i]!=NULL) {
            if(adjacencyMatrix[firstVertexNumber][i]->length()>0) {
                firstUniqueVertexCount++;
            }
        }

        if(adjacencyMatrix[secondVertexNumber][i]!=NULL) {
            if(adjacencyMatrix[secondVertexNumber][i]->length()>0) {
                secondUniqueVertexCount++;
            }
        }
    }
    if(firstUniqueVertexCount<2 || secondUniqueVertexCount<2) {
        return false;
    } else {
        return true;
    }
}

bool Graph::tryCloseDiodeBranch(Branch *diodeBranch)
{
    deleteBranch(diodeBranch->getVertexNumber1(),diodeBranch->getVertexNumber2(),diodeBranch);
    if(checkGraphCohesion(diodeBranch->getVertexNumber1(),diodeBranch->getVertexNumber2())) {
        return true;
    } else {
        return false;
    }
}

void Graph::deleteBranch(int vertexNumber1, int vertexNumber2, Branch *branch)
{
    nullSafeDeleteDirectBranch(vertexNumber1,vertexNumber2,branch);
    nullSafeDeleteDirectBranch(vertexNumber2,vertexNumber1,branch);
}

void Graph::nullSafeDeleteDirectBranch(int vertexNumber1, int vertexNumber2, Branch *branch)
{
    QList<Branch*>* branches;
    if((branches=adjacencyMatrix[vertexNumber1][vertexNumber2])!=NULL) {
        branches->removeAll(branch);
    }
}

bool Graph::checkDiodeBranchTreshold(double *calcResult, Branch *diodeBranch)
{
    if(!diodeBranch->isDiodeBranch()) {
        return true;
    }

    if(diodeBranch->isHasEmf()) {
        foreach (Element* elem, *diodeBranch->getBranchElements()) {
            if(elem->getName()==StringValues::EMF_NAME) {
                if(((EMF*)elem)->getVoltage()>ConstValues::DIODE_OPEN_TRESHOLD) {
                    return true;
                } else {
                    return false;
                }
            }
        }
    }

    double upPotential=0.0;
    if(!diodeBranch->getVertexNumber1()==0) {
        upPotential=calcResult[diodeBranch->getVertexNumber1()-1];
    }

    double downPotential=0.0;
    if(!diodeBranch->getVertexNumber2()==0) {
        downPotential=calcResult[diodeBranch->getVertexNumber2()-1];
    }

    //TODO несколько диодов в ветви
    if((upPotential-downPotential)>ConstValues::DIODE_OPEN_TRESHOLD) {
        return true;
    } else {
        return false;
    }

}
