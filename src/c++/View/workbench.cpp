#include "workbench.h"
#include <QVBoxLayout>
#include <QMovie>
#include <QLabel>


WorkBench::WorkBench::WorkBench(QWidget *parent) :
    QWidget(parent)
{
   this->v1 = new QVBoxLayout(this);
   this->setLayout(v1);
   this->setFixedWidth(400);
   this->setFixedHeight(400);
   this->show();
   this->componentManager = new ComponentManager(this);
   this->eventHandler = new EventHandler(this);
   this->canvas = new OGLRender(); //сюда надо добавить родителя
   QObject::connect(canvas,SIGNAL(mouseClicked(QMouseEvent*)),eventHandler,SLOT(mouseClicked(QMouseEvent*)));
   QObject::connect(canvas,SIGNAL(mouseReleased(QMouseEvent*)),eventHandler,SLOT(mouseReleased(QMouseEvent*)));
   QObject::connect(eventHandler,SIGNAL(addResistor(int,int)),componentManager,SLOT(addResistor(int,int)));
   QObject::connect(canvas,SIGNAL(paintComponents()),componentManager,SLOT(paintComponents()));
   v1->addWidget(canvas);
   canvas->initializeGL();
   refresher = new UpdateThread(this);
   QObject::connect(refresher,SIGNAL(update()),canvas,SLOT(update()));
   refresher->start();
}
