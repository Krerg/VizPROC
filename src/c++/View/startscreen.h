#pragma once
#ifndef STARTSCREEN_H
#define STARTSCREEN_H

#include <QMainWindow>
#include <QPushButton>

class StartScreen : public QWidget
{
    Q_OBJECT

public:
    explicit StartScreen(QWidget *parent = 0);
    ~StartScreen();
    void setSignals(QObject *l);
private:
    QPushButton* newProject;
    QPushButton* loadProject;
    QPushButton* Exit;

};

#endif // STARTSCREEN_H
