#include <QApplication>
#include "main.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //Запуск контроллера инициализации приложения
    InitController *i = new InitController();
    i->startProgramm();
    return a.exec();
}

