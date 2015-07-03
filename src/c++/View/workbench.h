#pragma once
#ifndef WORKBENCH_H
#define WORKBENCH_H

class WindowManager;

#include <QWidget>
#include <QVBoxLayout>
#include "oglrender.h"
#include "src/c++/View/updatethread.h"
#include "src/c++/Controller/eventhandler.h"
#include "src/c++/View/componentmanager.h"
#include "src/c++/View/mousetrackerthread.h"
#include "src/c++/Model/graph.h"
#include "src/c++/View/visualisationmanager.h"
#include "src/c++/Controller/graphhandler.h"
#include <QMenuBar>
#include <QAction>
#include "windowmanager.h"

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
    explicit WorkBench(WindowManager* wm, QWidget *parent = 0);

    /**
     * @brief connectComponents метод для соединения сигнало и слотов компонент программы
     */
    void connectComponents();

    /**
     * @brief getComponentManager
     * @return
     */
    ComponentManager* getComponentManager();

    /**
     * @brief setWindowManger установка менеджера окон
     * @param wm
     */
    void setWindowManger(WindowManager* wm);

private:
    /**
     * @brief menuBar
     */
    QMenuBar *menuBar;

    /**
     * @brief fileMenu
     */
    QMenu* fileMenu;

    /**
     * @brief aboutMenu
     */
    QMenu* aboutMenu;

    /**
     * @brief saveProject
     */
    QAction* saveProject;

    /**
     * @brief loadProject
     */
    QAction* loadProject;

    /**
     * @brief information
     */
    QAction* information;

    /**
     * @brief v1 вертикальный лэйоут размещения
     */
    QVBoxLayout *v1;

    /**
     * @brief hLayout
     */
    QHBoxLayout *hLayout;

    /**
     * @brief leftPanelLayout лэйаут для левой панели(панель инструментов)
     */
    QVBoxLayout* leftPanelLayout;

    /**
     * @brief rightPanelLayout
     */
    QVBoxLayout* rightPanelLayout;

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

    /**
     * @brief GraphHandler
     */
    GraphHandler* graphHandler;

    /**
     * @brief wm
     */
    WindowManager* wm;

    /**
     * @brief panel
     */
    QWidget *panel;

    QLabel* lbl;
protected:

    /**
     * @brief keyPressed сигнал нажатия кнопки
     * @param event
     */
    void keyPressEvent(QKeyEvent *event);

signals:

public slots:

    /**
     * @brief openInformationWindow
     */
    void openInformationWindow();

    /**
     * @brief onElementClick
     * @param elem
     */
    void onElementClick(Element* elem);

    /**
     * @brief onWireClick
     * @param w
     */
    void onWireClick(Wire* w);

    /**
     * @brief saveFile слот дл сохранения в файл
     */
    void saveFile();

    /**
     * @brief openFile слот дл открытия файла
     */
    void openFile();
};

#endif // WORKBENCH_H
