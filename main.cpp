#include <QApplication>
#include "main.h"
#include "src/c++/Model/lumatrix.h"
#include <QDebug>
#include "src/c++/Util/stylesheetvalues.h"


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //Запуск контроллера инициализации приложения
    InitController *i = new InitController();
    i->startProgramm();
    return a.exec();
}

