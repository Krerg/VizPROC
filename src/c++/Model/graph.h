#ifndef GRAPH_H
#define GRAPH_H

#include <QObject>
#include <QVector>
#include <QList>
#include <QMap>
#include "src/c++/Elements/wire.h"
#include "src/c++/Elements/element.h"
#include "src/c++/Model/lumatrix.h"
#include "src/c++/Elements/diode.h"
#include "src/c++/Model/diodebranch.h"

/**
 * @brief The Graph class класс, который представляет схему в виде графа
 */
class Graph : public QObject
{
    Q_OBJECT
public:
    /**
     * @brief Graph конструктор класса
     * @param parent указатель на родительский элемент
     */
    explicit Graph(QObject *parent = 0);

    /**
     * @brief deleteVertex удаление вершины из графа
     * @param w провод, чей потенциал мы хотим удалить
     */
    void deleteVertex(Wire* w);
private:
    /**
     * @brief getNewNumber
     * @return уникальный номер для вершины
     */
    int getNewNumber();

    /**
     * @brief lastFreeNumber последний свободный номер для добавления потенциала
     */
    int lastFreeNumber;

    /**
     * @brief array массив, который представляет собой решение схемы
     */
    double **array;

    /**
     * @brief leftpart
     */
    float **leftpart;

    /**
     * @brief graph граф схемы,
     * который содержит потенциалы
     */
    QMap<Wire*,int*> *graph;

    /**
     * @brief showMatrix вывод матрицы на экран (для отладки)
     * @param n размерность
     */
    void showMatrix(int n);

    /**
     * @brief processGraph обработка графа для нумерации веток и нахождения диодных веток
     * @param first провод для обработки (обход в ширину)
     * @param number номер, с которого начинается нумерация
     */
    void processGraph(Wire* first, int number);

    /**
     * @brief matrixResolver
     */
    LUMatrix* matrixResolver;

    /**
     * @brief numberOfIterations кол-во итерация равное кол-ву диодов в схеме
     */
    int numberOfIterations;

    /**
     * @brief diodes список диодов в схеме
     */
    QList<Diode*>* diodes;

    /**
     * @brief diodesBranches список диодных ветвей
     */
    QList<DiodeBranch*>* diodesBranches;
signals:
    void startVisualisation(QMap<Wire*,int*> *graph, double* x, int numb);
public slots:
    /**
     * @brief addVertex добавление вершины(потенциала в граф)
     * @param w провод, потенциал которого хотим добавить
     */
    void addVertex(Wire* w);

    /**
     * @brief start сигнал запускающий расчет схемы
     */
    void start();

    /**
     * @brief addDiode добавление диода в структуру
     * @param d сам диод
     */
    void addDiode(Diode* d);
};

#endif // GRAPH_H
