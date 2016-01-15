#ifndef VISUALISATIONMANAGER_H
#define VISUALISATIONMANAGER_H

#include <QObject>
#include <QPainter>
#include "src/c++/Elements/wire.h"
#include "src/c++/Elements/wire.h"

/**
 * @brief The VisualisationManager class класс, отвечающий за визуализацию схемы
 */
class VisualisationManager : public QObject
{
    Q_OBJECT
public:
    explicit VisualisationManager(QObject *parent = 0);
    ~VisualisationManager();
    void setPotentials(double* potentials);
    void setGraph(QMap<Wire*,int*> *graph);
    void setWires(QList<Wire*>* wires);
    void setElements(QList<Element*>* elements);
    void setMeters(QList<Element*> *meters);
private:
    /**
     * @brief potentials потенциалы
     */
    double* potentials;

    /**
     * @brief elements список элементов для визуализации
     */
    QList<Element*> *elements;

    /**
     * @brief meters список измеряющих элементов
     */
    QList<Element*> *meters;

    /**
     * @brief wires срисок проводов для визуализации
     */
    QList<Wire*> *wires;

    /**
     * @brief graph граф схемы,
     * который содержит потенциалы
     */
    QMap<Wire*,int*> *graph;

    /**
     * @brief numb кол-во потенциалов
     */
    int numb;

    /**
     * @brief getColor методя для получения цвета в зависимости от значения напряжения
     * @param potential значение напряжение
     * @param maxPotential мак значение напряжения на схеме
     * @param container контейнер куда цвет положится
     * @return входной контейнер
     */
    int* getColor(double potential,double maxPotential, int* container);

    /**
     * @brief getRadius
     * @param maxPower
     * @param power
     * @return
     */
    int getRadius(double maxPower, double power);
signals:
    void enableVisualisation();
public slots:
    /**
     * @brief updateVusualisation обновление состояния проводов
     * @param painter
     */
    void updateVusualisation(QPainter *painter);

    /**
     * @brief startVisualisation первоначальная установка входных данных для визуализации
     * @param graph граф
     * @param x потенциалы точек
     */
    void startVisualisation(QMap<Wire*,int*> *graph, double* x,int numb);
};

#endif // VISUALISATIONMANAGER_H
