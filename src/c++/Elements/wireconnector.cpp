#include "wireconnector.h"
#include <QGLWidget>
#include <math.h>

WireConnector::WireConnector(int x, int y,QObject *parent) : QObject(parent)
{
    this->x = x;
    this->y = y-1;
}

WireConnector::~WireConnector()
{

}

void WireConnector::paintComponent()
{
    glColor3d(0.0f,0.0f,0.0f);
    int i;
    int triangleAmount = 20;
    GLfloat twicePi = 2.0f * 3.1415;
    glBegin(GL_TRIANGLE_FAN);
        glVertex2f(x,y);
        for(i=0;i <= triangleAmount; i++) {
            glVertex2f(x+(3*cos(i*twicePi/triangleAmount)),y+(3*sin(i*twicePi/triangleAmount)));
        }
    glEnd();
}

int WireConnector::getX()
{
    return this->x;
}

int WireConnector::getY()
{
    return this->y;
}
