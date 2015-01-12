#include "ground.h"
#include <QtOpenGL/QGLWidget>

Ground::Ground(QObject *parent) :
    QObject(parent)
{
    this->selected = false;
    this->pointed = false;
    this->c1 = NULL;
}

void Ground::setPosition(int x, int y)
{
    this->x = x;
    this->y = y;
}

void Ground::paintComponent()
{

}

bool Ground::isSelected(int x, int y)
{
    return false;
}

