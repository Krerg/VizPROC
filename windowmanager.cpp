#include "windowmanager.h"
#include "src/c++/View/workbench.h"
#include "src/c++/Util/filehandler.h"
#include "src/c++/View/componentmanager.h"

WindowManager::WindowManager(QObject *parent) :
    QObject(parent)
{
}

void WindowManager::start()
{
    //Инициализация стартового экрана
    sc = new StartScreen();
    //Установка сигналов
    sc->setSignals(this);
    sc->show();
}

WorkBench* WindowManager::openWorkBench()
{
    if(sc!=NULL)
        delete sc;
    sc = NULL;
    WorkBench* workBench = new WorkBench(this);
    workBench->connectComponents();
    return workBench;
}

WorkBench *WindowManager::openWorkBench(ComponentManager *cm)
{
    if(sc!=NULL)
        delete sc;
    sc = NULL;
    WorkBench* workBench = new WorkBench(this,cm);
    workBench->connectComponents();
    return workBench;
}

void WindowManager::openProject()
{
    ComponentManager* cm = new ComponentManager();
    FileHandler::openFile(cm);
    WorkBench* workBench = openWorkBench(cm);
}
