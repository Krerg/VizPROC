#ifndef EVENTHANDLER_H
#define EVENTHANDLER_H

#include <QObject>
#include <QMouseEvent>
#include "src/c++/View/componentmanager.h"
#include <QComboBox>

/**
 * @brief The EventHandler class обрабатывает события мыши и передает данные менеджеру компоненты
 */
class EventHandler : public QObject
{
    Q_OBJECT
public:
    explicit EventHandler(QObject *parent = 0);

    /**
     * @brief setQComboBox
     * @param c
     */
    void setQComboBox(QComboBox *c);
private:
    QComboBox *selectedElem;
signals:
    /**
     * @brief addElement добавление элемента
     * @param elem название элемента
     * @param x координата курсора по оси абсцисс
     * @param y координата курсора по оси ординат
     */
    void addElement(QString elem,int x, int y);

    /**
     * @brief click нажатие левой кнопки мыши
     * @param x координата курсора по оси абсцисс
     * @param y координата курсора по оси ординат
     */
    void click(int x, int y);

    /**
     * @brief moveElement перемещение элемента
     * @param x координата курсора по оси асцисс
     * @param y координата курсора по оси ординат
     */
    void moveElement(int x, int y);

    /**
     * @brief leftClickReleased событие отпуска левой кнопки мыши
     */
    void leftClickReleased();

    /**
     * @brief changeOrientation изменение ориентациии положения элемента
     */
    void changeOrientation(int,int);
public slots:
    /**
     * @brief mouseClicked слот который вызываетя при нажатии любой кнопки мыши
     * @param event событие нажатия кнопки
     */
    void mouseClicked(QMouseEvent* event);

    /**
     * @brief mouseReleased слот который вызывается при отпускании любой кнопки мыши
     * @param event событие мыши
     */
    void mouseReleased(QMouseEvent* event);

    /**
     * @brief mouseMoved слот который вызывается при нажатии кнопки мыши и ее перемещении (перетаскивание)
     * @param event событие мыши
     */
    void mouseMoved(QMouseEvent* event);

    /**
     * @brief mouseDoubleClicked слот который вызывается при двойном нажатии любой кнопки мыши
     * @param event событие мыши
     */
    void mouseDoubleClicked(QMouseEvent *event);
};

#endif // EVENTHANDLER_H
