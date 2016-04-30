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
#include <QMenuBar>

/**
 * @brief The OGLRender class OpenGL окно для отрисовки
 */
class OGLRender : public QGLWidget
{

    Q_OBJECT

public:
    /**
     * @brief OGLRender конструктор класса
     */
    OGLRender();

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

    /**
     * @brief drawGrid отрисовка сетки
     */
    void drawGrid();

    /**
     * @brief hideAllPanesl скрывает все панели на экране
     */
    void hideAllPanesl();

    /**
     * @brief error выводить ли ошибку
     */
    bool error;

    /**
     * @brief renderLock
     */
    bool renderLock;

    /**
     * @brief errorText текст ошибки
     */
    QString errorText;

    /**
     * @brief componentIndex номер элемента в списке
     */
    int componentIndex;

    /**
     * @brief resistorPanelVisible флаг видимости настроек парметров резистора
     */
    bool resistorPanelVisible=false;

    /**
     * @brief emfPanelVisible флаг видимости панели настроек ЭДС
     */
    bool emfPanelVisible=false;

    /**
      * @brief voltagePanel менеджер компановки элементов для напряжения на ЭДС
      */
     QHBoxLayout* voltagePanel;

    /**
     * @brief voltageLabel лэйбл напряжения
     */
    QLabel* voltageLabel;

    /**
     * @brief voltageSpinBox спин бокс для вытавления напряженя на ЭДС
     */
    QDoubleSpinBox* voltageSpinBox;

    /**
     * @brief resPanel панель для парметров резистора
     */
    QVBoxLayout *elemPanel;

    /**
     * @brief resistanceLabel лэйбл сопротивления резистора
     */
    QLabel* resistanceLabel;

    /**
     * @brief powerLabel лэйбл мощности резистора
     */
    QLabel* powerLabel;

    /**
     * @brief power комбобокс для выставления мощности
     */
    QComboBox* power;

    /**
     * @brief resistanceSpinBox спин бокс для настройки сопротивления на резисторе
     */
    QDoubleSpinBox* resistanceSpinBox;

    /**
       //TODO удалить
     * @brief elementList список элементов для работы
     */
    QComboBox *elementList;

    /**
     * @brief startVisualisation кнопка, которая запускает визуализацию схемы
     */
    QPushButton *startButton;

    /**
     * @brief stopButton кнопка, которая останавливает визуализацию
     */
    QPushButton* stopButton;


    /**
     * @brief enableVisualisation флаг, отвечающий за режим работы
     */
    bool enableVisualisation;

    /**
     * @brief selectedRes выбранный на UI резистор
     */
    Resistor* selectedRes;

    /**
     * @brief selectedEmf выбранный на UI ЭДС
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
    void keyPressEvent(QKeyEvent *event);
public slots:

    void setRenderLock();

    void unsetRenderLock();

    void editingElementFinished();

    /**
     * @brief valueChanged
     */
    void valueChanged();

    void startButtonPressed();

    void enableVisualisationSlot();

    /**
     * @brief stopVisualisation остановка визуализации
     */
    void stopVisualisationSlot();

    /**
     * @brief setError установка флага ошибки и ее текста
     * @param errorText текст ошибки
     */
    void setError(QString errorText);

    void elementDeleted();

signals:

    /**
     * @brief recalculate перерасчет схемы
     */
    void recalculate();

    /**
     * @brief paintComponents отрисовка элементов
     */
    void paintComponents();

    /**
     * @brief paintMeters визуализация измерительных приборов
     * @param painter
     */
    void paintMeters(QPainter *painter);

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

    /**
     * @brief keyPressed сигнал нажатия кнопки
     * @param event
     */
    void keyPressed(QKeyEvent* event);

    /**
     * @brief releaseLock
     */
    void releaseLock();


};

#endif // OGLRENDER_H
