#ifndef EMF_H
#define EMF_H

#include <QObject>
#include "src/c++/Elements/element.h"
/**
 * @brief The EMF класс ЭДС
 */
class EMF : public QObject, Element
{
    Q_OBJECT
public:
    explicit EMF(QObject *parent = 0);
    /**
     * @brief paintComponent отрисовка ЭДС на экране
     */
    virtual void paintComponent();
    /**
     * @brief setHeight установка высоты
     * @param height высота ЭДС
     */
    void setHeight(int height);
    /**
     * @brief setWidth установка ширины
     * @param width ширина ЭДС
     */
    void setWidth(int width);
    int getWidth();
    int getHeight();
    const QString HORIZONTAL_ORIENTATION = "HORIZONTAL";
    const QString VERTICAL_ORIENTATION = "VERTICAL";
    /**
     * @brief setPosition установка позиции
     * @param x
     * @param y
     */
    virtual void setPosition(int x, int y);
    /**
     * @brief connect присоединение другого проводника
     * @param x
     * @param y
     */
    virtual void connect(int x,int y);
    /**
     * @brief isSelected проверка на то, что курсор кликнул по ЭДС
     * @param x координата курсора
     * @param y координата курсора
     * @return
     */
    virtual bool isSelected(int x, int y);
    /**
     * @brief disableSelected снятие выделения с элемента
     */
    virtual void disableSelected();
    /**
     * @brief enableSelected сделать элемент выделенным
     */
    virtual void enableSelected();
    /**
     * @brief changeOrientation изменение ориентации элемента
     */
    virtual void changeOrientation();
    virtual int getX();
    virtual int getY();
    virtual ~EMF();
private:
    bool selected;
    int x;
    int y;
    int height;
    int width;
    /**
     * @brief pinLength длина выводов ЭДС
     */
    int pinLength;
    QString orientation;
signals:

public slots:

};

#endif // EMF_H
