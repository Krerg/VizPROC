#ifndef GRAPH_H
#define GRAPH_H

#include <QObject>
#include "src/c++/Model/branch.h"
#include <QList>
#include <QStack>
#include <QVector>

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
     * @brief getConnectedBranches
     * @param vertexNumber
     * @return
     */
    QList<Branch *> *getConnectedBranches(int vertexNumber);

    /**
     * @brief getAllBranches возвращает список всех ветвей в графе
     * @return
     */
    QList<Branch *> *getAllBranches();

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

    /**
     * @brief openNextBranch открывает следующую диодную ветвь если возмонжно
     */
    bool openNextBranch(double *calculationResult);

    /**
     * @brief isolateDiodeBranches стартует процесс выделения диодных ветвей и помещение их в стек по порядку их закрытия
     * @return StringValues::GRAPH_ISOLATION_...
     */
    QString isolateDiodeBranches();

    /**
     * @brief optimizeGraph
     */
    void optimizeGraph();

    /**
     * @brief clearAllocatedArray заполнение массива значениями NULL
     */
    void clearAllocatedArray();

private:

    /**
     * @brief matrixIsEmpty проверяет текущее состояние графа на пустоту
     * @return true если граф пустой, в противном случае false
     */
    bool matrixIsEmpty();

    /**
     * @brief closedDiodeBranches стек с закрытыми диодными ветвями
     */
    QStack<Branch*>* closedDiodeBranches;

    /**
     * @brief diodeBranches список диодных ветвей
     */
    QList<Branch*> *diodeBranches;

    /**
     * @brief checkBranchList
     * @return
     */
    Branch *checkBranchList(QList<Branch*>*);

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
     * @brief hasEmfCycle проверка на цикл с ЭДС между двумя вершинами
     * @param vertexNumber1 номер первой вершины
     * @param vertexNumber2 номер второй вершины
     * @return true если есть цикл с ЭДС, в противном случае false
     */
    bool hasEmfCycle(int vertexNumber1, int vertexNumber2);

    /**
     * @brief onlyEmfLeft проверяет, что в графе осталось только ЭДС и ничего более
     * @return true если осталось только ЭДС, в остальных случаях false
     */
    bool onlyEmfLeft(int vertexNumber1, int vertexNumber2);

    /**
     * @brief hasCycle
     * @param vertexNumber1
     * @param vertexNumber2
     * @return
     */
    bool hasCycle(int vertexNumber1, int vertexNumber2);

    /**
     * @brief nullSafeAddDirectEdge
     * @param vertexNumber1
     * @param vertexNumber2
     */
    void nullSafeAddDirectEdge(Branch* branch, int vertexNumber1, int vertexNumber2);

    /**
     * @brief deleteAdjencyMatrix
     */
    void deleteAdjencyMatrix();

    /**
     * @brief unionEdge
     * @param centralVertexNumber
     * @param firstConnectedVertex
     * @param secondConnectedVertex
     */
    void unionEdges(int centralVertexNumber, int firstConnectedVertex, int secondConnectedVertex);

    /**
     * @brief unionCycles
     * @param vertexNumber1
     * @param vertexNumber2
     */
    void unionCycles(int vertexNumber1, int vertexNumber2);

    /**
     * @brief checkGraphCohesion проверяет связность графа, после удаления ветви
     * @param firstVertexNumber номер крайнего потенциала удаленной ветви
     * @param secondVertexNumber номер крайнего потенциала удаленной ветви
     * @return false если связости нету, в противном случае true
     */
    bool checkGraphCohesion(int firstVertexNumber, int secondVertexNumber);

    /**
     * @brief tryCloseDiodeBranch закрытие диодной ветви если это возможно
     * @param diodeBranch диодная ветвь которую нужно закрыть
     * @return true если возможно, в противном случае false
     */
    bool tryCloseDiodeBranch(Branch* diodeBranch);

    /**
     * @brief deleteBranch удаление ветви из графа
     * @param vertexNumber1 номер присоединенного узла
     * @param vertexNumber2 номер присоединенного узла
     * @param branch ветвь, которую нужно удалить
     */
    void deleteBranch(int vertexNumber1, int vertexNumber2, Branch* branch);

    /**
     * @brief nullSafeDeleteDirectEdge
     * @param vertexNumber1
     * @param vertexNumber2
     */
    void nullSafeDeleteDirectBranch(int vertexNumber1, int vertexNumber2, Branch* branch);

    /**
     * @brief checkDiodeBranchTreshold проверяет возможность открытия диодной ветви
     * @param calcResult результаты предвычисления схемы
     * @param diodeBranch диодная ветвь
     * @return true если можно открыть ветвь, в противном случае false
     */
    bool checkDiodeBranchTreshold(double* calcResult, Branch* diodeBranch);

signals:

public slots:

};

#endif // GRAPH_H
