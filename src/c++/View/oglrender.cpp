#include "oglrender.h"
#include "src/c++/Elements/resistor.h"

OGLRender::OGLRender() :
    QGLWidget()
{
    this->refreshThread = new UpdateThread();
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
void OGLRender::update()
{
    this->paintGL();
    this->updateGL();
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
void OGLRender::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
   // Resistor *r = new Resistor();
   // r->paintComponent();
    emit paintComponents();
}
//Ивент который вызывается при нажатии на кнопку мыши
void OGLRender::mousePressEvent(QMouseEvent *event)
{
    emit mouseClicked(event);
}
//Ивент который вызывается при передвижении мыши и нажатии кнопки, удобно кстати оч
void OGLRender::mouseMoveEvent(QMouseEvent *event)
{
    int dx = event->x();
    int dy = event->y();
}
//Ивент который вызывается при отпускании клавиши мыши
void OGLRender::mouseReleaseEvent(QMouseEvent *event)
{
    emit mouseReleased(event);
}
