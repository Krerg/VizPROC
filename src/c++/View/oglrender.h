#ifndef OGLRENDER_H
#define OGLRENDER_H

#include <QtOpenGL/QGLWidget>
#include <QMouseEvent>
#include "src/c++/View/updatethread.h"
#include <QObject>
#include <QComboBox>
#include <QPushButton>

/**
 * @brief The OGLRender class
 */
class OGLRender : public QGLWidget
{

    Q_OBJECT

public:
    /**
     * @brief OGLRender конструктор класса
     */
    OGLRender();

    /**
     * @brief getComboBox
     * @return
     */
    QComboBox* getComboBox();

    void initializeGL();

    ~OGLRender();
private:
    /**
     * @brief elementList список элементов для работы
     */
    QComboBox *elementList;

    /**
     * @brief startVisualisation кнопка, которая запускает визуализацию схемы
     */
    QPushButton *startButton;
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
    void startButtonPressed();
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

    /**
     * @brief startVisualisation
     */
    void startVisualisation();
};

#endif // OGLRENDER_H
