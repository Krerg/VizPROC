#include "initcontroller.h"

InitController::InitController(QObject *parent) :
    QObject(parent)
{
    //Инициализация менеджера окон
    this->main = new WindowManager(this);
}
void InitController::startProgramm()
{
    //Запуск менеджера окон
    this->main->start();
}
