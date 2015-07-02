#include "workbench.h"
#include <QVBoxLayout>
#include <QMovie>
#include <QLabel>
#include <QPainter>
#include <QDebug>
#include <QApplication>
#include "src/c++/Util/programminformationwindow.h"
#include "src/c++/Util/filehandler.h"

WorkBench::WorkBench::WorkBench(WindowManager* wm,QWidget *parent) :
    QWidget(parent)
{
   this->wm = wm;
   this->leftPanelLayout = new QVBoxLayout();
   this->rightPanelLayout = new QVBoxLayout();
   this->hLayout = new QHBoxLayout(this);
   this->v1 = new QVBoxLayout();
   hLayout->addLayout(leftPanelLayout);
   hLayout->addLayout(v1);
   hLayout->addLayout(rightPanelLayout);

   //leftPanelLayout->addWidget(new QLabel("Левая панель"));

   //rightPanelLayout->addWidget(new QLabel("Правая панель"));



   //this->setLayout(v1);
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

   //добавляем OpenGL виджет и инициализируем его
   v1->addSpacing(17);
   v1->addWidget(canvas);
   //canvas->initializeGL();

   //запуск потоков
   refresher->start();
   mouseTrackerThread->start();


   this->menuBar = new QMenuBar(this);
   menuBar->show();
   this->fileMenu = new QMenu("Файл",menuBar);
   this->aboutMenu = new QMenu("О программе",menuBar);
   this->saveProject = new QAction("Сохранить проект",fileMenu);
   this->loadProject = new QAction("Загрузить проект",fileMenu);
   this->information = new QAction("Информация",fileMenu);


   menuBar->addMenu(fileMenu);
   menuBar->addMenu(aboutMenu);
   fileMenu->addAction(saveProject);
   fileMenu->addAction(loadProject);
   aboutMenu->addAction(information);

   QObject::connect(information,SIGNAL(triggered()),this,SLOT(openInformationWindow()));

   menuBar->setFixedSize(400,21);

   //соединяем сигналы и слоты
   this->connectComponents();

}
void WorkBench::connectComponents()
{
    //соединение гуи и обработчика событий
    this->eventHandler->setQComboBox(canvas->getComboBox());

    //сигналы с переферии
    QObject::connect(canvas,SIGNAL(mouseClicked(QMouseEvent*)),eventHandler,SLOT(mouseClicked(QMouseEvent*)));
    QObject::connect(canvas,SIGNAL(mouseReleased(QMouseEvent*)),eventHandler,SLOT(mouseReleased(QMouseEvent*)));
    QObject::connect(canvas,SIGNAL(mouseMoved(QMouseEvent*)),eventHandler,SLOT(mouseMoved(QMouseEvent*)));
    QObject::connect(canvas,SIGNAL(mouseDoubleClicked(QMouseEvent*)),eventHandler,SLOT(mouseDoubleClicked(QMouseEvent*)));
    QObject::connect(canvas,SIGNAL(keyPressed(QKeyEvent*)),eventHandler,SLOT(keyPressed(QKeyEvent*)));

    //обработанные сигналы с переферии
    QObject::connect(eventHandler,SIGNAL(addElement(QString,int,int)),componentManager,SLOT(addElement(QString,int,int)));
    QObject::connect(eventHandler,SIGNAL(click(int,int)),componentManager,SLOT(mouseClick(int,int)));
    QObject::connect(mouseTrackerThread,SIGNAL(mouseMoved(int,int)),componentManager,SLOT(mouseMoved(int,int)));
    QObject::connect(eventHandler,SIGNAL(leftClickReleased()),componentManager,SLOT(leftClickReleased()));
    QObject::connect(eventHandler,SIGNAL(changeOrientation(int,int)),componentManager,SLOT(changeOrientation(int,int)));
    QObject::connect(eventHandler,SIGNAL(moveElement(int,int)),componentManager,SLOT(moveElement(int,int)));
    QObject::connect(eventHandler,SIGNAL(deleteItem()),componentManager,SLOT(deleteItem()));

    //отрисовка
    QObject::connect(canvas,SIGNAL(paintComponents()),componentManager,SLOT(paintComponents()));
    QObject::connect(refresher,SIGNAL(update()),canvas,SLOT(update()));

    //соединения с логиков
    QObject::connect(componentManager,SIGNAL(wireAdded(Wire*)),g,SLOT(addVertex(Wire*)));
    QObject::connect(componentManager,SIGNAL(addDiode(Diode*)),g,SLOT(addDiode(Diode*)));
    QObject::connect(componentManager,SIGNAL(deleteWire(Wire*)),g,SLOT(deleteVertex(Wire*)));

    //начало визуализации
    QObject::connect(canvas,SIGNAL(startVisualisation()),g,SLOT(start()));

    //подготовка обработчика визуализации
    QObject::connect(g,SIGNAL(startVisualisation(QMap<Wire*,int*>*,double*,int)),visualisationManager,SLOT(startVisualisation(QMap<Wire*,int*>*,double*,int)));

    //установка флага визуализации
    QObject::connect(visualisationManager,SIGNAL(enableVisualisation()),canvas,SLOT(enableVisualisationSlot()));

    //обновление визуализации
    QObject::connect(canvas,SIGNAL(updateVisualisation(QPainter*)),visualisationManager,SLOT(updateVusualisation(QPainter*)));

    //обновление визуализации
    QObject::connect(canvas,SIGNAL(paintMeters(QPainter*)),componentManager,SLOT(paintMeters(QPainter*)));

    //открытие окошка для настройки параметров элементов
    QObject::connect(componentManager,SIGNAL(onElementClick(Element*)),this,SLOT(onElementClick(Element*)));

    //для провода
    QObject::connect(componentManager,SIGNAL(onWireClick(Wire*)),this,SLOT(onWireClick(Wire*)));

    //обработка файлов
    QObject::connect(saveProject,SIGNAL(triggered()),this,SLOT(saveFile()));
    QObject::connect(loadProject,SIGNAL(triggered()),wm,SLOT(openProject()));

}

ComponentManager *WorkBench::getComponentManager()
{
    return componentManager;
}

void WorkBench::setWindowManger(WindowManager *wm)
{
    this->wm = wm;
}

void WorkBench::keyPressEvent(QKeyEvent *event)
{
    qDebug()<<"Key workbench";
}

void WorkBench::openInformationWindow()
{
    ProgrammInformationWindow* w = new ProgrammInformationWindow();
    w->show();
}

void WorkBench::onElementClick(Element *elem)
{
    if(elem->getName()=="Res") {
        canvas->openResistorPanel((Resistor*)elem);
    } else if(elem->getName()=="Emf") {
        canvas->openEmfPanel((EMF*)elem);
    }
}

void WorkBench::onWireClick(Wire *w)
{
    qDebug()<<"On wire click";
}

void WorkBench::saveFile()
{
    FileHandler::saveFile(componentManager);
}

void WorkBench::openFile()
{

}
