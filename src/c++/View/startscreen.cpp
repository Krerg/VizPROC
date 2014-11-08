#include "startscreen.h"
#include <QVBoxLayout>
#include "windowmanager.h"
StartScreen::StartScreen(QWidget *parent) :
    QWidget(parent)
{
    this->setWindowTitle("VIZProc");
    //Инициализация кнопок стартового экрана
    this->newProject = new QPushButton("Новый проект",this);
    this->loadProject = new QPushButton("Загрузить проект",this);
    this->Exit = new QPushButton("Выход",this);

    //Добавление кнопок в лэйаут окн
    QVBoxLayout *v = new QVBoxLayout(this);
    v->addWidget(newProject);
    v->addWidget(loadProject);
    v->addWidget(Exit);

    this->setLayout(v);
}
void StartScreen::setSignals(QObject *l)
{
    //Связывание сигналов кнопок стартового экрана с сигналами windowManager
    WindowManager *m = qobject_cast<WindowManager*>(l);
    QObject::connect(this->Exit,SIGNAL(clicked()),this,SLOT(close()));
    QObject::connect(this->newProject,SIGNAL(clicked()),m,SLOT(openWorkBench()));
    
}

StartScreen::~StartScreen()
{

}
