#ifndef GRAPH_H
#define GRAPH_H

#include <QObject>
#include "src/c++/Model/branch.h"
#include <QList>

/**
 * @brief The Graph class класс, реализующий граф схемы
 */
class Graph : public QObject
{
    Q_OBJECT
public:

    /**
     * @brief Graph публичный конструктор
     * @param parent родительский элемент
     */
    explicit Graph(QObject *parent = 0);

    /**
     * @brief addEdge
     * @param branch
     */
    void addEdge(Branch* branch, int vertexNumber1, int vertexNumber2);

    /**
     * @brief deleteEdge
     * @param firstVertexNumber
     */
    void deleteEdge(int firstVertexNumber, int secondVertexNumber);

    /**
     * @brief initGraph инициализация матрицы смежности
     * @param vertexNumber кол-во вершин
     */
    void initGraph(int vertexNumber);

private:

    /**
     * @brief checkBranchList
     * @return
     */
    Branch *checkBranchList(QList<Branch*>*);

    /**
     * @brief optimizeGraph
     */
    void optimizeGraph();

    /**
     * @brief adjacencyMatrix матрица смежности графа
     */
    QList<Branch*>*** adjacencyMatrix;

    /**
     * @brief matrixSize размер матрицы смежности
     */
    int matrixSize;

    /**
     * @brief nullSafeDeleteDirectEdge
     * @param vertexNumber1
     * @param vertexNumber2
     */
    void nullSafeDeleteDirectEdge(int vertexNumber1, int vertexNumber2);

    /**
     * @brief nullSafeAddDirectEdge
     * @param vertexNumber1
     * @param vertexNumber2
     */
    void nullSafeAddDirectEdge(Branch* branch, int vertexNumber1, int vertexNumber2);

    /**
     * @brief unionEdge
     * @param centralVertexNumber
     * @param firstConnectedVertex
     * @param secondConnectedVertex
     */
    void unionEdges(int centralVertexNumber, int firstConnectedVertex, int secondConnectedVertex);

signals:

public slots:

};

#endif // GRAPH_H
