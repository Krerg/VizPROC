#ifndef OGLRENDER_H
#define OGLRENDER_H

#include <QtOpenGL/QGLWidget>
#include <QMouseEvent>
#include "src/c++/View/updatethread.h"
#include <QObject>
#include <QComboBox>
#include <QPushButton>
#include <src/c++/Elements/wire.h>
#include "src/c++/Elements/resistor.h"
#include "src/c++/Elements/emf.h"
#include <QLabel>
#include <QDoubleSpinBox>
#include <QVBoxLayout>

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

    Wire* w;

    /**
     * @brief openResistorPanel
     * @param res
     */
    void openResistorPanel(Resistor* res);

    /**
     * @brief openEmfPanel
     * @param emf
     */
    void openEmfPanel(EMF* emf);

    ~OGLRender();
private:

    bool resistorPanelVisible=false;

    bool emfPanelVisible=false;


    /**
      * @brief voltagePanel
      */
     QHBoxLayout* voltagePanel;

    /**
     * @brief voltageLabel
     */
    QLabel* voltageLabel;

    /**
     * @brief voltageSpinBox
     */
    QDoubleSpinBox* voltageSpinBox;

    /**
     * @brief resPanel панель для парметров резистора
     */
    QVBoxLayout *elemPanel;

    /**
     * @brief resistanceLabel
     */
    QLabel* resistanceLabel;

    /**
     * @brief powerLabel
     */
    QLabel* powerLabel;

    /**
     * @brief power
     */
    QComboBox* power;

    /**
     * @brief resistanceSpinBox
     */
    QDoubleSpinBox* resistanceSpinBox;

    /**
     * @brief elementList список элементов для работы
     */
    QComboBox *elementList;

    /**
     * @brief startVisualisation кнопка, которая запускает визуализацию схемы
     */
    QPushButton *startButton;


    /**
     * @brief enableVisualisation флаг, отвечающий за режим работы
     */
    bool enableVisualisation;

    /**
     * @brief selectedRes
     */
    Resistor* selectedRes;

    /**
     * @brief selectedEmf
     */
    EMF* selectedEmf;

protected:

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
    void paintEvent(QPaintEvent *event);
    void wheelEvent(QWheelEvent *event);

public slots:
    void startButtonPressed();
    void enableVisualisationSlot();
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

    /**
     * @brief updateVisualisation обновление состояния визуализации
     * @param painter
     */
    void updateVisualisation(QPainter *painter);
};

#endif // OGLRENDER_H
