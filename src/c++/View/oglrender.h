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
    void paintGL();
    void resizeGL(int width,int height);
    void mousePressEvent(QMouseEvent* event);
    void mouseMoveEvent(QMouseEvent* event);
    void mouseReleaseEvent(QMouseEvent* event);
public slots:
    void update();
signals:
    void paintComponents();
    void mouseClicked(QMouseEvent *event);
    void mouseReleased(QMouseEvent *event);
};

#endif // OGLRENDER_H
