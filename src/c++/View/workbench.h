#pragma once
#ifndef WORKBENCH_H
#define WORKBENCH_H

#include <QWidget>
#include <QVBoxLayout>
#include "oglrender.h"
#include "src/c++/View/updatethread.h"
#include "src/c++/Controller/eventhandler.h"
#include "src/c++/View/componentmanager.h"
#include "src/c++/View/mousetrackerthread.h"
#include "src/c++/Model/graph.h"
#include "src/c++/View/visualisationmanager.h"

/**
 * @brief The WorkBench class окно где происходит вся ралота с программой
 */
class WorkBench : public QWidget
{
    Q_OBJECT
public:
    /**
     * @brief WorkBench конструктор класса
     * @param parent указатель на родительский элемент
     */
    explicit WorkBench(QWidget *parent = 0);

    /**
     * @brief connectComponents метод для соединения сигнало и слотов компонент программы
     */
    void connectComponents();
private:
    /**
     * @brief v1 вертикальный лэйоут размещения
     */
    QVBoxLayout *v1;

    /**
     * @brief canvas поле где рисуетс весь интерфейс
     */
    OGLRender *canvas;

    /**
     * @brief refresher поток для обновления экрана
     */
    UpdateThread *refresher;

    /**
     * @brief eventHandler обработчик событий на экране
     */
    EventHandler *eventHandler;

    /**
     * @brief componentManager менеджер элементов
     */
    ComponentManager *componentManager;

    /**
     * @brief mouseTrackerThread поток наблюдения перемещени курсора
     */
    MouseTrackerThread *mouseTrackerThread;

    /**
     * @brief g граф для расчета значений потенциалов схемы
     */
    Graph *g;

    /**
     * @brief visualisationManager обработчик визуализации
     */
    VisualisationManager* visualisationManager;
signals:

public slots:

};

#endif // WORKBENCH_H
