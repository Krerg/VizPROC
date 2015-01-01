#ifndef OGLRENDER_H
#define OGLRENDER_H

#include <QtOpenGL/QGLWidget>
#include <QMouseEvent>
#include "src/c++/View/updatethread.h"
#include <QObject>
#include <QComboBox>

/**
 * @brief The OGLRender class
 */
class OGLRender : public QGLWidget
{

    Q_OBJECT

public:
    OGLRender();
    void initializeGL();
    ~OGLRender();
private:
    QComboBox *elementList;
protected:
    /**
     * @brief paintGL отрисовка фигур на экране
     */
    void paintGL();

    /**
     * @brief resizeGL обновление всего виджета (в том числе включает paintGL)
     * @param width
     * @param height
     */
    void resizeGL(int width,int height);
    void mousePressEvent(QMouseEvent* event);
    void mouseMoveEvent(QMouseEvent* event);
    void mouseReleaseEvent(QMouseEvent* event);
    void mouseDoubleClickEvent(QMouseEvent *event);
public slots:
    void update();
signals:
    /**
     * @brief paintComponents
     */
    void paintComponents();

    /**
     * @brief mouseClicked нажатие мыши
     * @param event
     */
    void mouseClicked(QMouseEvent *event);

    /**
     * @brief mouseReleased отпускание кнопки мыши
     * @param event
     */
    void mouseReleased(QMouseEvent *event);

    /**
     * @brief mouseMoved перетаскивание мыши
     * @param event
     */
    void mouseMoved(QMouseEvent *event);

    /**
     * @brief mouseDoubleClicked двойное надатие кнопки мыши
     * @param event
     */
    void mouseDoubleClicked(QMouseEvent *event);
};

#endif // OGLRENDER_H
