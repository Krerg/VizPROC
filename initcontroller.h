#pragma once
#ifndef INITCONTROLLER_H
#define INITCONTROLLER_H

#include <QObject>
#include "windowmanager.h"
class InitController : public QObject
{
    Q_OBJECT
public:
    explicit InitController(QObject *parent = 0);
    void startProgramm();
private:
    WindowManager *main;
signals:

public slots:

};

#endif // INITCONTROLLER_H
