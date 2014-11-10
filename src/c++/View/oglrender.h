#ifndef OGLRENDER_H
#define OGLRENDER_H

#include <QtOpenGL/QGLWidget>
#include <QMouseEvent>
#include "src/c++/View/updatethread.h"
#include <QObject>

class OGLRender : public QGLWidget
{

    Q_OBJECT

public:
    OGLRender();
    void initializeGL();
    ~OGLRender();
private:
    UpdateThread* refreshThread;
protected:
    void paintGL(); //рисование на эране
    void resizeGL(int width,int height); //обновить весь виджет
    void mousePressEvent(QMouseEvent* event);
    void mouseMoveEvent(QMouseEvent* event);
    void mouseReleaseEvent(QMouseEvent* event);
public slots:
    void update();
signals:
    void paintComponents(); //нарисовать все элементы
    void mouseClicked(QMouseEvent *event); //нажатие мыши
    void mouseReleased(QMouseEvent *event); //отпускание нажатой мыши
    void mouseMoved(QMouseEvent *event); //перетскивание мышью
};

#endif // OGLRENDER_H
