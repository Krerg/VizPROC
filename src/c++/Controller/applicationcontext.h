#ifndef APPLICATIONCONTEXT_H
#define APPLICATIONCONTEXT_H

#include <QObject>
#include "src/c++/Model/model.h"
#include "windowmanager.h"
#include "src/c++/View/updatethread.h"
#include "src/c++/View/componentmanager.h"

/**
 * @brief The ApplicationContext class класс контекста всего приложения дл доступа к основным компонентам
 */
class ApplicationContext : public QObject
{
    Q_OBJECT
public:

    /**
     * @brief getInstance
     * @return
     */
    static ApplicationContext *getInstance();

    /**
     * @brief setComponentManager
     * @param cm
     */
    void setComponentManager(ComponentManager* cm);

    /**
     * @brief setUpdateThread
     * @param ut
     */
    void setUpdateThread(UpdateThread* ut);

    /**
     * @brief setModel
     * @param model
     */
    void setModel(Model* model);

    /**
     * @brief setWindowManager
     * @param wm
     */
    void setWindowManager(WindowManager* wm);

    /**
     * @brief getComponentManager
     * @return
     */
    ComponentManager* getComponentManager();

    /**
     * @brief getUpdateThread
     * @return
     */
    UpdateThread* getUpdateThread();

    /**
     * @brief getModel
     * @return
     */
    Model* getModel();

    /**
     * @brief getWindowManager
     * @return
     */
    WindowManager *getWindowManager();

private:

    explicit ApplicationContext(QObject *parent = 0);

    static ApplicationContext* instance;

    /**
     * @brief MODEL модель приложения, отвечающая за логику
     */
    static Model* MODEL;

    /**
     * @brief WINDOW_MANAGER менеджер окон
     */
    static WindowManager* WINDOW_MANAGER;

    /**
     * @brief UPDATE_THREAD обновляющий изображение поток.
     */
    static UpdateThread* UPDATE_THREAD;

    /**
     * @brief COMPONENT_MANAGER менеджер графическийх компонент
     */
    static ComponentManager* COMPONENT_MANAGER;

signals:

public slots:

};

    //Инициализация статических переменных


#endif // APPLICATIONCONTEXT_H
