#include "windowmanager.h"
#include "src/c++/View/workbench.h"

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
void WindowManager::openWorkBench()
{
  delete sc;
  wb = new WorkBench();
}
