#include "applicationcontext.h"

ApplicationContext* ApplicationContext::instance = NULL;
ComponentManager* ApplicationContext::COMPONENT_MANAGER = NULL;
UpdateThread* ApplicationContext::UPDATE_THREAD = NULL;
Model* ApplicationContext::MODEL = NULL;
WindowManager* ApplicationContext::WINDOW_MANAGER = NULL;

ApplicationContext *ApplicationContext::getInstance()
{
    if(instance == NULL) {
        instance = new ApplicationContext();
    }
    return instance;
}

void ApplicationContext::setComponentManager(ComponentManager *cm)
{
    if(ApplicationContext::COMPONENT_MANAGER==NULL) {
        this->COMPONENT_MANAGER = cm;
    } else {
        //TODO throw an custom exception
    }
}

void ApplicationContext::setUpdateThread(UpdateThread *ut)
{
    if(UPDATE_THREAD==NULL) {
        this->UPDATE_THREAD = ut;
    } else {
        //TODO throw an custom exception
    }
}

void ApplicationContext::setModel(Model *model)
{
    if(MODEL==NULL) {
        this->MODEL = model;
    } else {
        //TODO
    }
}

void ApplicationContext::setWindowManager(WindowManager *wm)
{
    if(WINDOW_MANAGER==NULL) {
        this->WINDOW_MANAGER = wm;
    } else {
        //TODO
    }
}

ComponentManager *ApplicationContext::getComponentManager()
{
    return COMPONENT_MANAGER;
}

UpdateThread *ApplicationContext::getUpdateThread()
{
    return UPDATE_THREAD;
}

Model *ApplicationContext::getModel()
{
    return MODEL;
}

WindowManager *ApplicationContext::getWindowManager()
{
    return WINDOW_MANAGER;
}

ApplicationContext::ApplicationContext(QObject *parent) :
    QObject(parent)
{

}
