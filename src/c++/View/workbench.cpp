#include "workbench.h"
#include <QVBoxLayout>
#include <QMovie>
#include <QLabel>
#include <QPainter>
#include <QDebug>
#include <QApplication>
#include "src/c++/Util/programminformationwindow.h"
#include "src/c++/Util/filehandler.h"
#include "src/c++/Util/stylesheetvalues.h"
#include "src/c++/Controller/applicationcontext.h"

WorkBench::WorkBench::WorkBench(WindowManager* wm,ComponentManager* cm,QWidget *parent) :
    componentManager(cm),QWidget(parent)
{
    this->activatedButton = NULL;
   this->wm = wm;
   this->leftPanelLayout = new QVBoxLayout();
   this->rightPanelLayout = new QVBoxLayout();
   this->hLayout = new QHBoxLayout(this);
   this->v1 = new QVBoxLayout();
   hLayout->addLayout(leftPanelLayout);
   hLayout->addLayout(v1);
   hLayout->addLayout(rightPanelLayout);
   this->setMouseTracking(true);
   QString styleSheet = "QPushButton {width:18px;height:18px;color: white;font-weight: 700;text-decoration: none;padding: .5em 2em;outline: none;border: 2px solid;border-radius: 1px; background: rgb(45,45,45)}  QPushButton:hover {background: rgb(85,85,85);}";
   QString styleSheet2 = "QPushButton {width:1200px;height:40px;color: white;font-weight: 700;text-decoration: none;padding: .5em 2em;outline: none;border: 2px solid;border-radius: 1px; background: rgb(45,45,45)}  QPushButton:hover { border-color: rgb(255,255,255)}";

   stopButton = new QPushButton();
   stopButton->setIcon(QIcon("C:/Users/amylniko/Documents/env/er/VizPROC-master/resource/stop_button.png"));
   stopButton->setStyleSheet(styleSheet2);
   stopButton->setFixedWidth(30);
   stopButton->setFixedHeight(30);
    stopButton->setVisible(false);
   //
   playButton = new QPushButton();
   playButton->setIcon(QIcon("C:/Users/amylniko/Documents/env/er/VizPROC-master/resource/play_button.png"));
   playButton->setStyleSheet(styleSheet2);
   playButton->setFixedWidth(30);
   playButton->setFixedHeight(30);

   resistorButton = new QPushButton();
   resistorButton->setIcon(QIcon("C:/Users/amylniko/Documents/env/er/VizPROC-master/resource/resistor_button.png"));
   resistorButton->setStyleSheet(styleSheet2);
   resistorButton->setFixedSize(30,30);
   resistorButton->setIconSize(QSize(25,25));

   emfButton = new QPushButton();
   emfButton->setIcon(QIcon("C:/Users/amylniko/Documents/env/er/VizPROC-master/resource/emf_button.png"));
   emfButton->setStyleSheet(styleSheet2);
   emfButton->setFixedSize(30,30);
   emfButton->setIconSize(QSize(23,23));

   diodeButton = new QPushButton();
   diodeButton->setIcon(QIcon("C:/Users/amylniko/Documents/env/er/VizPROC-master/resource/diode_button.png"));
   diodeButton->setStyleSheet(styleSheet2);
   diodeButton->setFixedSize(30,30);
   diodeButton->setIconSize(QSize(23,23));

   groundButton = new QPushButton();
   groundButton->setIcon(QIcon("C:/Users/amylniko/Documents/env/er/VizPROC-master/resource/ground_button.png"));
   groundButton->setStyleSheet(styleSheet2);
   groundButton->setFixedSize(30,30);
   groundButton->setIconSize(QSize(17,17));

   wireButton = new QPushButton();
   wireButton->setIcon(QIcon("C:/Users/amylniko/Documents/env/er/VizPROC-master/resource/wire_button.png"));
   wireButton->setStyleSheet(styleSheet2);
   wireButton->setFixedSize(30,30);
   wireButton->setIconSize(QSize(23,23));

   amperemeterButton = new QPushButton();
   amperemeterButton->setIcon(QIcon("C:/Users/amylniko/Documents/env/er/VizPROC-master/resource/amperemeter_button.png"));
   amperemeterButton->setStyleSheet(styleSheet2);
   amperemeterButton->setFixedSize(30,30);
   amperemeterButton->setIconSize(QSize(23,23));

   voltmeterButton = new QPushButton();
   voltmeterButton->setIcon(QIcon("C:/Users/amylniko/Documents/env/er/VizPROC-master/resource/voltmeter_button.png"));
   voltmeterButton->setStyleSheet(styleSheet2);
   voltmeterButton->setFixedSize(30,30);
   voltmeterButton->setIconSize(QSize(23,23));

   rightPanelLayout->setSpacing(2);
   rightPanelLayout->addSpacing(12);
   rightPanelLayout->addWidget(playButton);
   rightPanelLayout->addWidget(stopButton);
   rightPanelLayout->addWidget(resistorButton);
   rightPanelLayout->addWidget(emfButton);
   rightPanelLayout->addWidget(diodeButton);
   rightPanelLayout->addWidget(groundButton);
   rightPanelLayout->addWidget(wireButton);
   rightPanelLayout->addWidget(amperemeterButton);
   rightPanelLayout->addWidget(voltmeterButton);

   //this->setLayout(v1);
   this->setFixedWidth(600);
   this->setFixedHeight(400);
   this->show();
   if(componentManager==NULL) {
    this->componentManager = new ComponentManager(this);
   }
   this->eventHandler = new EventHandler(this);
   this->canvas = new OGLRender(); //сюда надо добавить родителя
    //создаем потоки для обновления изображения
   this->refresher = new UpdateThread(this);
   this->mouseTrackerThread = new MouseTrackerThread(canvas,this);

   this->graphHandler = new GraphHandler(this);
   graphHandler->setElements(componentManager->getElements());
   this->model = new Model(this);

   //инициализация обработчика визуализации
   this->visualisationManager = new VisualisationManager(this);
   this->visualisationManager->setWires(componentManager->getWires());
   this->visualisationManager->setElements(componentManager->getElements());
   this->visualisationManager->setMeters(componentManager->getMeters());

   //добавляем OpenGL виджет и инициализируем его
   v1->addSpacing(17);
   v1->addWidget(canvas);
   canvas->initializeGL();

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

   QString styleSheet3 = "QMenuBar { background-color: rgb(45,45,45)} QMenuBar:item { color: white;font-weight: 700;text-decoration: none;outline: none; background: rgb(45,45,45);} QMenu {color: white;font-weight: 700;text-decoration: none;padding: .5em 2em;outline: none;border: 2px solid;border-radius: 1px; background: rgb(45,45,45);} QMenu::item:selected {background: rgb(85,85,85);}";

   menuBar->setStyleSheet(styleSheet3);
   menuBar->setStyleSheet(styleSheet3);
   menuBar->setAutoFillBackground(true);
   fileMenu->setStyleSheet(styleSheet3);
   aboutMenu->setStyleSheet(styleSheet3);
   aboutMenu->setAutoFillBackground(true);

   QObject::connect(information,SIGNAL(triggered()),this,SLOT(openInformationWindow()));

   menuBar->setFixedSize(600,21);

   //запуск потоков
   refresher->start();
   mouseTrackerThread->start();

   this->setStyleSheet("QWidget {color:white;background-color: rgb(120,120,120)} QComboBox {color: white;font-weight: 700;text-decoration: none;outline: none;border: 2px solid;border-radius: 1px; background: rgb(45,45,45);}  QListView::item { color: white;font-weight: 700;text-decoration: none;outline: none; background: rgb(45,45,45); QListView::item:selected {coloe:white;background: rgb(85,85,85);} ");

   guiButtons = new QList<QPushButton*>();
   guiButtons->append(resistorButton);
   guiButtons->append(emfButton);
   guiButtons->append(diodeButton);
   guiButtons->append(groundButton);

   initApplicationContext();

}
void WorkBench::connectComponents()
{

    //сигналы с переферии
    QObject::connect(canvas,SIGNAL(mouseClicked(QMouseEvent*)),eventHandler,SLOT(mouseClicked(QMouseEvent*)));
    QObject::connect(canvas,SIGNAL(mouseReleased(QMouseEvent*)),eventHandler,SLOT(mouseReleased(QMouseEvent*)));
    QObject::connect(canvas,SIGNAL(mouseMoved(QMouseEvent*)),eventHandler,SLOT(mouseMoved(QMouseEvent*)));
    QObject::connect(canvas,SIGNAL(mouseDoubleClicked(QMouseEvent*)),eventHandler,SLOT(mouseDoubleClicked(QMouseEvent*)));
    QObject::connect(canvas,SIGNAL(keyPressed(QKeyEvent*)),eventHandler,SLOT(keyPressed(QKeyEvent*)));

    //обработанные сигналы с переферии
    QObject::connect(eventHandler,SIGNAL(addElement(int,int,int)),componentManager,SLOT(addElement(int,int,int)));
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
    QObject::connect(componentManager,SIGNAL(wireAdded(Wire*)),model,SLOT(addVertex(Wire*)));
    QObject::connect(componentManager,SIGNAL(addedDiode(Diode*)),model,SLOT(addDiode(Diode*)));
    QObject::connect(componentManager,SIGNAL(deleteWire(Wire*)),model,SLOT(deleteVertex(Wire*)));

    //визуализация
    //QObject::connect(canvas,SIGNAL(startVisualisation()),g,SLOT(start()));
    QObject::connect(playButton,SIGNAL(clicked()),graphHandler,SLOT(handle()));
    QObject::connect(stopButton,SIGNAL(clicked()),this,SLOT(stopButtonHide()));
    QObject::connect(this,SIGNAL(stopVisualisation()),canvas,SLOT(stopVisualisationSlot()));
    QObject::connect(model,SIGNAL(hideStartButton()),this,SLOT(playButtonHide()));
    QObject::connect(graphHandler,SIGNAL(error(QString)),canvas,SLOT(setError(QString)));
    QObject::connect(graphHandler,SIGNAL(start()),model,SLOT(start()));
    QObject::connect(model,SIGNAL(setLock()),eventHandler,SLOT(setLock()));
    QObject::connect(canvas,SIGNAL(releaseLock()),eventHandler,SLOT(releaseLock()));

    //пересчет схемы
    QObject::connect(canvas,SIGNAL(recalculate()),model,SLOT(start()));

    //подготовка обработчика визуализации
    QObject::connect(model,SIGNAL(startVisualisation(QMap<Wire*,int*>*,double*,int)),visualisationManager,SLOT(startVisualisation(QMap<Wire*,int*>*,double*,int)));

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

    //кнопки с GUI
    QObject::connect(resistorButton,SIGNAL(clicked()),this,SLOT(buttonPressed()));
    QObject::connect(emfButton,SIGNAL(clicked()),this,SLOT(buttonPressed()));
    QObject::connect(diodeButton,SIGNAL(clicked()),this,SLOT(buttonPressed()));
    QObject::connect(groundButton,SIGNAL(clicked()),this,SLOT(buttonPressed()));
    QObject::connect(wireButton,SIGNAL(clicked()),this,SLOT(buttonPressed()));
    QObject::connect(amperemeterButton,SIGNAL(clicked()),this,SLOT(buttonPressed()));
    QObject::connect(voltmeterButton,SIGNAL(clicked()),this,SLOT(buttonPressed()));


    QObject::connect(resistorButton,SIGNAL(clicked()),eventHandler,SLOT(resistorActivate()));
    QObject::connect(emfButton,SIGNAL(clicked()),eventHandler,SLOT(emfActivate()));
    QObject::connect(diodeButton,SIGNAL(clicked()),eventHandler,SLOT(diodeActivate()));
    QObject::connect(groundButton,SIGNAL(clicked()),eventHandler,SLOT(groundActivate()));
    QObject::connect(wireButton,SIGNAL(clicked()),eventHandler,SLOT(wireActivate()));
    QObject::connect(amperemeterButton,SIGNAL(clicked()),eventHandler,SLOT(amperemeterActivate()));
    QObject::connect(voltmeterButton,SIGNAL(clicked()),eventHandler,SLOT(voltmeterActivate()));

    QObject::connect(componentManager,SIGNAL(elementDeleted()),canvas,SLOT(elementDeleted()));

}

ComponentManager *WorkBench::getComponentManager()
{
    return componentManager;
}

void WorkBench::setWindowManger(WindowManager *wm)
{
    this->wm = wm;
}

bool WorkBench::eventFilter(QObject *obj, QEvent *event)
{

}

void WorkBench::keyPressEvent(QKeyEvent *event)
{
    qDebug()<<"Key workbench";
}

void WorkBench::showWindow()
{
    QWidget::show();
    canvas->paintComponents();
    qDebug()<<"1110";
}

void WorkBench::initApplicationContext()
{
    ApplicationContext::getInstance()->setComponentManager(componentManager);
    ApplicationContext::getInstance()->setModel(model);
    ApplicationContext::getInstance()->setUpdateThread(refresher);
    ApplicationContext::getInstance()->setWindowManager(wm);
}

void WorkBench::buttonPressed()
{
    if(activatedButton!=NULL) {
        activatedButton->setStyleSheet(StyleSheetValues::BUTTON_STYLE);
    }
    QPushButton* senderButton = dynamic_cast<QPushButton*>(sender());
    senderButton->setStyleSheet(StyleSheetValues::BUTTON_ACTIVATED_STYLE);
    activatedButton=senderButton;
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

void WorkBench::playButtonHide()
{
    playButton->setVisible(false);
    stopButton->setVisible(true);
}

void WorkBench::stopButtonHide()
{
    playButton->setVisible(true);
    stopButton->setVisible(false);
    emit stopVisualisation();
}
