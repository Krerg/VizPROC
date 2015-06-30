#ifndef AMPEREMETER_H
#define AMPEREMETER_H

#include <QObject>
#include "src/c++/Elements/element.h"
#include <QPainter>

class Amperemeter : public QObject, Element
{
    Q_OBJECT
public:
    explicit Amperemeter(QObject *parent = 0);
    ~Amperemeter();
    virtual void paintComponent();
    void paintComponent(QPainter *painter);
    virtual void setPosition(int x, int y);
    //надо удалить
    virtual void connect(int x, int y);
    virtual bool isSelected(int x, int y);
    virtual void enableSelection();
    virtual void disableSelection();
    virtual QList<Connector *> *getConnectors();
    virtual void enablePointing();
    virtual void disablePointing();
    virtual void changeOrientation();
    virtual void disconnectWire(Wire *w);

    void setEnabled();

    /**
     * @brief setWire
     * @param w
     */
    void setWire(Wire* w);

    /**
     * @brief connectorPointCheck не используется
     * @param x
     * @param y
     * @return
     */
    virtual Connector* connectorPointCheck(int x, int y);
    virtual int getX();
    virtual int getY();
    virtual QString getName();

    /**
     * @brief getType н используется
     * @return
     */
    virtual bool getType();

private:
    /**
     * @brief x
     */
    int x;

    /**
     * @brief y
     */
    int y;

    /**
     * @brief pointed
     */
    bool pointed;

    /**
     * @brief selected
     */
    bool selected;

    /**
     * @brief attachedWire провод, который присоединен к амперметру
     */
    Wire* attachedWire;

    /**
     * @brief width
     */
    int width;

    /**
     * @brief height
     */
    int height;

    bool enabled;
signals:

public slots:
};

#endif // AMPEREMETER_H
