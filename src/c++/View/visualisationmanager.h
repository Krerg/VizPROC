#ifndef VISUALISATIONMANAGER_H
#define VISUALISATIONMANAGER_H

#include <QObject>
#include <QPainter>
#include "src/c++/Elements/wire.h"
#include "src/c++/Elements/wire.h"
#include "src/c++/Visualization/visualization.h"

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

    /**
     * @brief subscribe подписка обработчика визуализации на события изменений в схеме
     * @param handler обработчик визуализаций
     */
    void subscribe(Visualization* handler);

    /**
     * @brief unsubscribe отписка обработчика от обновлений
     * @param handler обработчик визуализации
     */
    void unsubscribe(Visualization* handler);

private:

    /**
     * @brief handlers список обработчиков визуализации
     */
    QList<Visualization*> *handlers;

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
     * @brief stop остановка всех обработчиков визулизациии
     */
    void stop();

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
    void startVisualisation(QList<Branch*> *branches, double* x,int numb);
};

#endif // VISUALISATIONMANAGER_H
