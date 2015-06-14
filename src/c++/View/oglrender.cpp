#include "oglrender.h"
#include "src/c++/Elements/resistor.h"
#include <QDebug>
#include <QVBoxLayout>
#include <QPainter>
#include <QLabel>
#include <QGraphicsDropShadowEffect>
#include <QApplication>
#include <math.h>

OGLRender::OGLRender() :
    QGLWidget()
{
    setFocusPolicy(Qt::ClickFocus);
    //setFormat(QGLFormat(QGL::SampleBuffers));
    startButton = new QPushButton("Включить визуализацию",this);
    QObject::connect(startButton,SIGNAL(clicked()),this,SLOT(startButtonPressed()));
    elementList = new QComboBox(this);
    elementList->addItem("Резистор");
    elementList->addItem("Диод");
    elementList->addItem("ЭДС");
    elementList->addItem("Провод");
    elementList->addItem("Заземление");
    elementList->addItem("Амперметр");
    elementList->addItem("Вольтметр");

    QVBoxLayout *g = new QVBoxLayout(this);

    elemPanel = new QVBoxLayout();
    elemPanel->setAlignment(Qt::AlignRight|Qt::AlignTop);
    QHBoxLayout *resistancePanel = new QHBoxLayout();
    QHBoxLayout *powerPanel = new QHBoxLayout();
    resistanceLabel = new QLabel("Сопротивление");
    resistanceSpinBox = new QDoubleSpinBox();

    powerLabel = new QLabel("Мощность");
    power = new QComboBox();
    power->addItem("0,125Вт");
    power->addItem("0,25Вт");

    voltagePanel = new QHBoxLayout();
    voltageLabel = new QLabel("Напряжение");
    voltageSpinBox = new QDoubleSpinBox();
    voltagePanel->addWidget(voltageLabel);
    voltagePanel->addWidget(voltageSpinBox);
    elemPanel->addLayout(voltagePanel);

    this->selectedEmf = NULL;
    this->selectedRes = NULL;

    resistancePanel->addWidget(resistanceLabel);
    resistancePanel->addWidget(resistanceSpinBox);

    powerPanel->addWidget(powerLabel);
    powerPanel->addWidget(power);

    //power->setVisible(false);
    //powerLabel->setVisible(false);

    elemPanel->addLayout(resistancePanel);
    elemPanel->addLayout(powerPanel);

    g->addLayout(elemPanel);
    //g->addWidget(resistanceLabel);
    //g->setAlignment(resistanceLabel,Qt::AlignRight|Qt::AlignTop);
    //g->addSpacing(this->height()-30);


    g->addWidget(elementList);
    g->addWidget(startButton);
    g->setAlignment(elementList,Qt::AlignBottom);
    //g->setAlignment(startButton,Qt::AlignBottom);


    voltageLabel->setVisible(false);
    voltageSpinBox->setVisible(false);

    resistanceLabel->setVisible(false);
    resistanceSpinBox->setVisible(false);

    powerLabel->setVisible(false);
    power->setVisible(false);


    enableVisualisation = false;
    this->setLayout(g);
    setMouseTracking(true);
    setAutoFillBackground(false);




}
OGLRender::~OGLRender()
{

}

void OGLRender::initializeGL()
{
    //Установка белого фона
    qglClearColor(Qt::white);
    //Установка размера виджета
    this->resizeGL(400,400);
}

void OGLRender::openResistorPanel(Resistor *res)
{
    if(selectedEmf!=NULL) {
        QObject::disconnect(voltageSpinBox,SIGNAL(valueChanged(double)),selectedEmf,SLOT(setVoltage(double)));
    }

    this->selectedEmf = NULL;
    this->selectedRes = res;

    resistorPanelVisible = true;
    emfPanelVisible = false;

    voltageSpinBox->hide();

    //resistanceLabel->show();
    resistanceSpinBox->show();

    //powerLabel->show();
    power->show();

    resistanceSpinBox->setValue(res->getResistance());
    QObject::connect(resistanceSpinBox,SIGNAL(valueChanged(double)),res,SLOT(setResistance(double)));

}

void OGLRender::openEmfPanel(EMF *emf)
{

    if(selectedRes!=NULL) {
        QObject::disconnect(resistanceSpinBox,SIGNAL(valueChanged(double)),selectedRes,SLOT(setResistance(double)));
    }

    resistorPanelVisible=false;
    emfPanelVisible=true;

    resistanceLabel->hide();
    resistanceSpinBox->hide();

    powerLabel->hide();
    power->hide();

//    voltageLabel->show();
    voltageSpinBox->show();

    voltageSpinBox->setValue(emf->getVoltage());

    QObject::connect(voltageSpinBox,SIGNAL(valueChanged(double)),emf,SLOT(setVoltage(double)));

}

void OGLRender::resizeGL(int width, int height)
{
    //Не менять!!!!! Я не до конца понимаю что и как здесь
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glViewport(0,0,width,height); //размер порта на котором будем рисовать вроде
    glOrtho(0,width,height,0,-1,1);
}
//paintGL вызывается каждый раз когда требуется перерисовать окно
//void OGLRender::paintGL()
//{
//    //glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//    //emit paintComponents();
//}
//Ивент который вызывается при нажатии на кнопку мыши
void OGLRender::mousePressEvent(QMouseEvent *event)
{
    emit mouseClicked(event);
}
//Ивент который вызывается при передвижении мыши и нажатии кнопки, удобно кстати оч
void OGLRender::mouseMoveEvent(QMouseEvent *event)
{
    emit mouseMoved(event);
}
//Ивент который вызывается при отпускании клавиши мыши
void OGLRender::mouseReleaseEvent(QMouseEvent *event)
{
    emit mouseReleased(event);
}
//Ивент который вызывается при двойном клике мышью
void OGLRender::mouseDoubleClickEvent(QMouseEvent *event)
{
    emit mouseDoubleClicked(event);
}

void OGLRender::paintEvent(QPaintEvent *event)
{

//    w->initParticles();
    QPainter painter;
    painter.begin(this);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

//    r->visualisation(colorContainer1,colorContainer2,&painter,100);
//gradient
//    QLinearGradient lg = QLinearGradient(QPointF(0,200),QPointF(200,300));
//    lg.setCoordinateMode(QGradient::ObjectBoundingMode );
//    lg.setSpread(QGradient::PadSpread);
//    lg.setColorAt(0.0,QColor(255,0,0));
//    lg.setColorAt(1,QColor(0,0,255));

//    QBrush brush = QBrush(lg);
//    painter.setBrush(brush);
//    QPen p;
//    p.setBrush(brush);
//    p.setWidth(2);
//    painter.setPen(p);
//    painter.drawLine(QPointF(0,200),QPointF(200,200)); // @1
//    painter.drawLine(QPointF(0,300),QPointF(200,300));
//    painter.drawLine(QPointF(0,200),QPointF(0,300)); // @1
//    painter.drawLine(QPointF(200,200),QPointF(200,300));


    //glow effect
//    QRadialGradient gradient;
//    gradient.setCoordinateMode(QGradient::ObjectBoundingMode);
//    gradient.setCenter(0.5, 0.5);
//    gradient.setFocalPoint(0.5, 0.5);
//    gradient.setColorAt(0.0, QColor(255, 255, 0));
//    gradient.setColorAt(0.5, QColor(255, 255, 255));
//    painter.setPen(Qt::NoPen);
//    painter.setBrush(gradient);
//    painter.drawEllipse(60,60,100,100);
//    painter.setPen(QColor(0,0,0));

    if(resistorPanelVisible) {
        painter.drawText(resistanceSpinBox->x()-84,resistanceSpinBox->y()+14,"Сопротивление");
        painter.drawText(power->x()-57,power->y()+14,"Мощность");
    } else if (emfPanelVisible) {
        painter.drawText(voltageSpinBox->x()-65,voltageSpinBox->y()+14,"Напряжение");
    }

    if(!enableVisualisation) {
    painter.beginNativePainting();
    emit paintComponents();
    emit paintMeters(&painter);
    } else {
      emit updateVisualisation(&painter);
    }
    painter.endNativePainting();
    painter.end();
}

void OGLRender::wheelEvent(QWheelEvent *event)
{

}

void OGLRender::keyPressEvent(QKeyEvent *event)
{
    emit keyPressed(event);
}

QComboBox* OGLRender::getComboBox()
{
    return elementList;
}

void OGLRender::startButtonPressed()
{
    emit startVisualisation();
}

void OGLRender::enableVisualisationSlot()
{
    this->enableVisualisation = true;
}
