#include "workbench.h"
#include <QVBoxLayout>
#include <QMovie>
#include <QLabel>
#include <QPainter>

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
    //создаем потоки для обновления изображения
   this->refresher = new UpdateThread(this);
   this->mouseTrackerThread = new MouseTrackerThread(canvas,this);

   this->g = new Graph(this);

   //инициализация обработчика визуализации
   this->visualisationManager = new VisualisationManager(this);
   this->visualisationManager->setWires(componentManager->getWires());
   this->visualisationManager->setElements(componentManager->getElements());


   //соединяем сигналы и слоты
   this->connectComponents();

   //добавляем OpenGL виджет и инициализируем его
   v1->addWidget(canvas);
   //canvas->initializeGL();



   //запуск потоков
   refresher->start();
   mouseTrackerThread->start();

//   QPainter *painter = new QPainter(canvas);
//   componentManager->setPainter(painter);
}
void WorkBench::connectComponents()
{
    //соединение гуи и обработчика событий
    this->eventHandler->setQComboBox(canvas->getComboBox());

    //соединение сигналов и слотов
    QObject::connect(canvas,SIGNAL(mouseClicked(QMouseEvent*)),eventHandler,SLOT(mouseClicked(QMouseEvent*)));
    QObject::connect(canvas,SIGNAL(mouseReleased(QMouseEvent*)),eventHandler,SLOT(mouseReleased(QMouseEvent*)));
    QObject::connect(canvas,SIGNAL(mouseMoved(QMouseEvent*)),eventHandler,SLOT(mouseMoved(QMouseEvent*)));
    QObject::connect(canvas,SIGNAL(mouseDoubleClicked(QMouseEvent*)),eventHandler,SLOT(mouseDoubleClicked(QMouseEvent*)));
    QObject::connect(eventHandler,SIGNAL(addElement(QString,int,int)),componentManager,SLOT(addElement(QString,int,int)));
    QObject::connect(eventHandler,SIGNAL(click(int,int)),componentManager,SLOT(mouseClick(int,int)));
    QObject::connect(mouseTrackerThread,SIGNAL(mouseMoved(int,int)),componentManager,SLOT(mouseMoved(int,int)));
    QObject::connect(eventHandler,SIGNAL(leftClickReleased()),componentManager,SLOT(leftClickReleased()));
    QObject::connect(eventHandler,SIGNAL(changeOrientation(int,int)),componentManager,SLOT(changeOrientation(int,int)));
    QObject::connect(eventHandler,SIGNAL(moveElement(int,int)),componentManager,SLOT(moveElement(int,int)));
    QObject::connect(canvas,SIGNAL(paintComponents()),componentManager,SLOT(paintComponents()));
    QObject::connect(refresher,SIGNAL(update()),canvas,SLOT(update()));
    QObject::connect(componentManager,SIGNAL(wireAdded(Wire*)),g,SLOT(addVertex(Wire*)));
    QObject::connect(canvas,SIGNAL(startVisualisation()),g,SLOT(start()));

    //подготовка обработчика визуализации
    QObject::connect(g,SIGNAL(startVisualisation(QMap<Wire*,int*>*,double*,int)),visualisationManager,SLOT(startVisualisation(QMap<Wire*,int*>*,double*,int)));

    //установка флага визуализации
    QObject::connect(visualisationManager,SIGNAL(enableVisualisation()),canvas,SLOT(enableVisualisationSlot()));

    //обновление визуализации
    QObject::connect(canvas,SIGNAL(updateVisualisation(QPainter*)),visualisationManager,SLOT(updateVusualisation(QPainter*)));
}
