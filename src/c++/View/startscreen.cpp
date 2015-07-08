#include "startscreen.h"
#include <QVBoxLayout>
#include "windowmanager.h"
StartScreen::StartScreen(QWidget *parent) :
    QWidget(parent)
{
    QString styleSheet = "QPushButton {display: inline-block;color: white;font-weight: 700;text-decoration: none;user-select: none;padding: .5em 2em;outline: none;border: 2px solid;border-radius: 1px;-webkit-transition: 0.2s; background: rgb(45,45,45)}  QPushButton:hover {background: rgba(225,225,225,.2);}";
    this->setWindowTitle("VIZProc");
    //Инициализация кнопок стартового экрана
    this->newProject = new QPushButton("Новый проект",this);
    this->loadProject = new QPushButton("Загрузить проект",this);
    this->Exit = new QPushButton("Выход",this);
    newProject->setStyleSheet(styleSheet);
    loadProject->setStyleSheet(styleSheet);
    Exit->setStyleSheet(styleSheet);


    //Добавление кнопок в лэйаут окн
    QHBoxLayout *h = new QHBoxLayout(this);

    QVBoxLayout *v = new QVBoxLayout();
    h->addLayout(v);
    v->addWidget(newProject);
    v->addSpacing(15);
    v->addWidget(loadProject);
    v->addSpacing(15);
    v->addWidget(Exit);
    this->setStyleSheet("QWidget {background: rgb(230,230,230);}");
    this->setLayout(v);
}
void StartScreen::setSignals(QObject *l)
{
    //Связывание сигналов кнопок стартового экрана с сигналами windowManager
    WindowManager *m = qobject_cast<WindowManager*>(l);
    QObject::connect(this->Exit,SIGNAL(clicked()),this,SLOT(close()));
    QObject::connect(this->newProject,SIGNAL(clicked()),m,SLOT(openWorkBench()));
    QObject::connect(this->loadProject,SIGNAL(clicked()),m,SLOT(openProject()));
    
}

StartScreen::~StartScreen()
{

}
