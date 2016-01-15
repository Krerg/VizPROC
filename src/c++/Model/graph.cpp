#include "graph.h"

Graph::Graph(QObject *parent) :
    QObject(parent)
{
}

void Graph::addEdge(Branch *branch, int vertexNumber1, int vertexNumber2)
{
    nullSafeAddDirectEdge(branch,vertexNumber1,vertexNumber2);
    nullSafeAddDirectEdge(branch,vertexNumber2,vertexNumber1);
}

void Graph::deleteEdge(int firstVertexNumber, int secondVertexNumber)
{
    nullSafeDeleteDirectEdge(firstVertexNumber,secondVertexNumber);
    nullSafeDeleteDirectEdge(secondVertexNumber,firstVertexNumber);
}

void Graph::initGraph(int vertexNumber)
{
    this->matrixSize = vertexNumber;
    for(int i=0;i<vertexNumber;i++) {
        for(int j=0;j<vertexNumber;j++) {

        }
    }
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
    QList<int> connectedVertexes;
    for(int i=0;i<matrixSize;i++) {
        for(int j=0;j<matrixSize;j++) {
            if(adjacencyMatrix[i][j] || adjacencyMatrix[i][j]->size()>0) {
                connectedVertexes.append(j);
            }
        }
        //если кол-во веток равно 2, то оптимизируем граф
        if(connectedVertexes.size()==2) {
            unionEdges(i,connectedVertexes.first(),connectedVertexes.last());
        }
        connectedVertexes.clear();
    }
}

void Graph::nullSafeDeleteDirectEdge(int vertexNumber1, int vertexNumber2)
{
    if(adjacencyMatrix[vertexNumber1][vertexNumber2]) {
        adjacencyMatrix[vertexNumber1][vertexNumber2]->clear();
    }
}

void Graph::nullSafeAddDirectEdge(Branch *branch, int vertexNumber1, int vertexNumber2)
{
    if(!adjacencyMatrix[vertexNumber1][vertexNumber2]) {
        adjacencyMatrix[vertexNumber1][vertexNumber2] = new QList<Branch*>();
    }
    adjacencyMatrix[vertexNumber1][vertexNumber2]->append(branch);
}

void Graph::unionEdges(int centralVertexNumber, int firstConnectedVertex, int secondConnectedVertex)
{
    Branch* firstConnectedBranch = checkBranchList(adjacencyMatrix[centralVertexNumber][firstConnectedVertex]);
    if(firstConnectedBranch == NULL) {
        return;
    }

    Branch* secondConnectedBranch = checkBranchList(adjacencyMatrix[centralVertexNumber][secondConnectedVertex]);
    if(secondConnectedBranch == NULL) {
        return;
    }

    firstConnectedBranch->unionBranch(secondConnectedBranch);
    Branch* unionBranch = firstConnectedBranch;
    addEdge(unionBranch,firstConnectedVertex,secondConnectedVertex);

    deleteEdge(centralVertexNumber,firstConnectedVertex);
    deleteEdge(centralVertexNumber,secondConnectedVertex);
}
