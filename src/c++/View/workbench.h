#pragma once
#ifndef WORKBENCH_H
#define WORKBENCH_H

#include <QWidget>
#include <QVBoxLayout>
#include "oglrender.h"
#include "src/c++/View/updatethread.h"
#include "src/c++/Controller/eventhandler.h"
#include "src/c++/View/componentmanager.h"

class WorkBench : public QWidget
{
    Q_OBJECT
public:
    explicit WorkBench(QWidget *parent = 0);
private:
    QVBoxLayout *v1;
    OGLRender *canvas;
    UpdateThread *refresher;
    EventHandler *eventHandler;
    ComponentManager *componentManager;
signals:

public slots:

};

#endif // WORKBENCH_H
