
#pragma once
#ifndef WINDOWMANAGER_H
#define WINDOWMANAGER_H

#include "src/c++/View/startscreen.h"
#include "src/c++/View/workbench.h"
#include <QObject>

class WindowManager : public QObject
{
    Q_OBJECT
public:
    explicit WindowManager(QObject *parent = 0);
    void start();
private:
    /**
     * @brief wb главнй экране приложения где происходит основная работа
     */
    WorkBench *wb;

    /**
     * @brief sc стартовый экране приложения
     */
    StartScreen *sc;
signals:

public slots:
    void openWorkBench();
};

#endif // WINDOWMANAGER_H
