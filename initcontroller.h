#pragma once
#ifndef INITCONTROLLER_H
#define INITCONTROLLER_H

#include <QObject>
#include "windowmanager.h"

/**
 * @brief The InitController class
 */
class InitController : public QObject
{
    Q_OBJECT
public:
    explicit InitController(QObject *parent = 0);

    /**
     * @brief startProgramm
     */
    void startProgramm();
private:
    WindowManager *main;
signals:

public slots:

};

#endif // INITCONTROLLER_H
