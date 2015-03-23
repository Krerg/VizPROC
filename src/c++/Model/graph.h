#ifndef GRAPH_H
#define GRAPH_H

#include <QObject>
#include <QVector>
#include <QList>
#include <QMap>
#include "src/c++/Elements/wire.h"
#include "src/c++/Elements/element.h"

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
    float **array;

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
signals:

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
};

#endif // GRAPH_H
