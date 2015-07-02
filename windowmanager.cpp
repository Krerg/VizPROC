#include "windowmanager.h"
#include "src/c++/View/workbench.h"
#include "src/c++/Util/filehandler.h"

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
    return workBench;
    //wb = new WorkBench(this);
}

void WindowManager::openProject()
{
    WorkBench* wb = openWorkBench();
    wb->hide();
    FileHandler::openFile(wb->getComponentManager());
    wb->show();
}
