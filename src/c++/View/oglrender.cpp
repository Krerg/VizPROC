#include "oglrender.h"
#include "src/c++/Elements/resistor.h"
#include <QDebug>
#include <QVBoxLayout>
#include <QPainter>
#include <QLabel>
#include <QGraphicsDropShadowEffect>

OGLRender::OGLRender() :
    QGLWidget()
{
    //setFormat(QGLFormat(QGL::SampleBuffers));
    startButton = new QPushButton("Поехали",this);
    QObject::connect(startButton,SIGNAL(clicked()),this,SLOT(startButtonPressed()));
    elementList = new QComboBox(this);
    elementList->addItem("Резистор");
    elementList->addItem("Диод");
    elementList->addItem("ЭДС");
    elementList->addItem("Провод");
    elementList->addItem("Заземление");
    QVBoxLayout *g = new QVBoxLayout(this);
    g->setAlignment(Qt::AlignBottom);
    g->addWidget(elementList);
    g->addWidget(startButton);

    //test
    w = new Wire();
    w->addPoint(10,10);
    w->addPoint(10,40);
    w->addPoint(80,40);
    w->addPoint(80,90);
    w->setSpeed(-2);



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
    int *color = new int[3];
    color[0]=255;
    color[1]=20;
    color[2]=20;

//    w->visualisation(color,&painter);
//    Resistor* r = new Resistor();
//    r->setPosition(60,60);
//    //r->paintComponent();
//    int* colorContainer1 = new int[3];
//    int* colorContainer2 = new int[3];
//    colorContainer1[0]=255;
//    colorContainer1[1]=0;
//    colorContainer1[2]=0;


//    colorContainer2[0]=0;
//    colorContainer2[1]=0;
//    colorContainer2[2]=255;


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



    if(!enableVisualisation) {
    painter.beginNativePainting();
    emit paintComponents();
    } else {
      emit updateVisualisation(&painter);
    }
    painter.endNativePainting();
    painter.end();
    //qDebug()<<"Paiint";
    //swapBuffers();
    delete color;

    //qDebug()<<"Paiint";
    //swapBuffers();
}

void OGLRender::wheelEvent(QWheelEvent *event)
{

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
