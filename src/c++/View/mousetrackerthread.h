#ifndef MOUSETRACKERTHREAD_H
#define MOUSETRACKERTHREAD_H

#include <QThread>
#include <QGLWidget>

/**
 * @brief The mouseTrackerThread class класс-поток, который следит за перемещением мыши
 */
class MouseTrackerThread : public QThread
{
    Q_OBJECT
public:
    /**
     * @brief MouseTrackerThread конструктор класса
     * @param parent указатель на родительский элемент
     */
    explicit MouseTrackerThread(QGLWidget* widget, QObject *parent = 0);
private:
    /**
     * @brief widget виджет, у которого будем отслеживать позицию курсора
     */
    QGLWidget *widget;
protected:
    void run();
signals:
    /**
     * @brief mouseMoved сигнал, который вызывается когда курсор переместился
     * @param x координата курсора
     * @param y координата курсора
     */
    void mouseMoved(int x, int y);
public slots:

};

#endif // MOUSETRACKERTHREAD_H
