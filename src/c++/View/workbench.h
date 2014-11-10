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
    void connectComponents();
private:
    QVBoxLayout *v1; //размещение
    OGLRender *canvas; //кнавас где все и рисуется
    UpdateThread *refresher; //поток обновления экрана
    EventHandler *eventHandler; //обработчик событий на экране
    ComponentManager *componentManager; //менеджер элементов
signals:

public slots:

};

#endif // WORKBENCH_H
