
#pragma once
#ifndef WINDOWMANAGER_H
#define WINDOWMANAGER_H

class WorkBench;

#include "src/c++/View/startscreen.h"
#include "src/c++/View/workbench.h"
#include <QObject>

/**
 * @brief The WindowManager class
 */
class WindowManager : public QObject
{
    Q_OBJECT
public:
    explicit WindowManager(QObject *parent = 0);

    /**
     * @brief start запускает менеджер окон
     */
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
    /**
     * @brief openWorkBench
     */
    WorkBench* openWorkBench();

    /**
     * @brief openProject
     */
    void openProject();
};

#endif // WINDOWMANAGER_H
