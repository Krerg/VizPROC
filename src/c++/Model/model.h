#ifndef MODEL_H
#define MODEL_H

#include <QObject>
#include <QVector>
#include <QList>
#include <QMap>
#include "src/c++/Elements/wire.h"
#include "src/c++/Elements/element.h"
#include "src/c++/Model/lumatrix.h"
#include "src/c++/Elements/diode.h"
#include "src/c++/Model/diodebranch.h"
#include "src/c++/Model/graph.h"

/**
 * @brief The Graph class класс, который представляет схему в виде графа
 */
class Model : public QObject
{
    Q_OBJECT
public:

    /**
     * @brief isDiodeBranchCheck
     * @return
     */
    static bool isDiodeBranchCheck();

    /**
     * @brief Graph конструктор класса
     * @param parent указатель на родительский элемент
     */
    explicit Model(QObject *parent = 0);

    /**
     * @brief getConnectedBranches
     * @param branch
     * @return
     */
    QList<Branch *> *getConnectedBranches(int vertexNumber);

private:

    /**
     * @brief DIODE_BRANCH_CHECK
     */
    static bool DIODE_BRANCH_CHECK;

    /**
     * @brief potentialsNumber кол-ао потенциалов в текущей схеме
     */
    int potentialsNumber;

    /**
     * @brief calculate @brief calculate производит расчет текущего графа
     * @return
     */
    double* calculate();

    /**
     * @brief deleteCircuitArray
     */
    void deleteCircuitArray();

    /**
     * @brief getEmptyResult возвращает пустой результат схемы, где все потенциалы равны 0
     * @return
     */
    double* getEmptyResult();

    /**
     * @brief array массив, который представляет собой решение схемы
     */
    double **array;

    /**
     * @brief leftpart
     */
    float **leftpart;

    /**
     * @brief graph пре-граф схемы,
     * который содержит потенциалы и информацию о них
     */
    QMap<Wire*,int*> *preGraph;

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
     * @brief matrixResolver реализация LU разложения и последующего нахождения решения системы уравнений
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
     * @brief checkCohesion
     * @return
     */
    bool checkCohesion();

    /**
     * @brief initCurciutArray инициализирует массив
     */
    void initCurciutArray();

    /**
     * @brief clearCurcuitArray очищает массив
     */
    void clearCurcuitArray();

    /**
     * @brief allocateBranches
     */
    void allocateBranches(bool wireCheck);

    Graph* graph;

    ~Model();

signals:

    /**
     * @brief startVisualisation сигн
     * @param x
     * @param numb
     */
    void startVisualisation(QList<Branch*>*, double* x, int numb);

    /**
     * @brief hideStartButton сигнал о том, что нжно скрыть кнопку рассчитать
     */
    void hideStartButton();

    /**
     * @brief setRenderLock установка блокировки на рендер схемы
     */
    void setRenderLock();

    /**
     * @brief setLock
     */
    void setLock();

    /**
     * @brief curcuitError сигнал об ошибке в схеме
     * @param errorMessage
     */
    void circuitError(QString errorMessage);

public slots:
    /**
     * @brief addVertex добавление вершины(потенциала в граф)
     * @param w провод, потенциал которого хотим добавить
     */
    void addVertex(Wire* w);

    /**
     * @brief deleteVertex удаление вершины из графа
     * @param w провод, чей потенциал мы хотим удалить
     */
    void deleteVertex(Wire* w);

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

#endif // MODEL_H
