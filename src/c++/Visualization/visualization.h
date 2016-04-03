#ifndef VISUALIZATION_H
#define VISUALIZATION_H

#include <QObject>
#include "src/c++/Event/initevent.h"
#include "src/c++/Event/nextstepevent.h"
#include "src/c++/Event/destroyevent.h"

/**
 * @brief The Visualization class интерфейс, описывающий жизненный цикл абстрактного обработчика визуализации
 */
class Visualization
{

public:
    explicit Visualization();

    /**
     * @brief init событие инициализации обработчика визуализации
     * @param event объект события
     */
    virtual void init(InitEvent* event)=0;

    /**
     * @brief nextStep событие следующего шага обработчика визуализации
     * @param event объект события
     */
    virtual void nextStep(NextStepEvent* event)=0;

    /**
     * @brief destroy событие отключения обработчика визуализации
     * @param event объект события
     */
    virtual void destroy(DestroyEvent* event)=0;

signals:

public slots:

};

#endif // VISUALIZATION_H
