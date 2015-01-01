#pragma once
#ifndef STARTSCREEN_H
#define STARTSCREEN_H

#include <QMainWindow>
#include <QPushButton>

/**
 * @brief The StartScreen class стартоевое окно приложения
 */
class StartScreen : public QWidget
{
    Q_OBJECT

public:
    explicit StartScreen(QWidget *parent = 0);
    ~StartScreen();
    void setSignals(QObject *l);
private:
    /**
     * @brief newProject кнопка создания нового проекта
     */
    QPushButton* newProject;

    /**
     * @brief loadProject кнопка загрузки проекта
     */
    QPushButton* loadProject;

    /**
     * @brief Exit кнопка выхода
     */
    QPushButton* Exit;

};

#endif // STARTSCREEN_H
