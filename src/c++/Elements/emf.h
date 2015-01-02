#ifndef EMF_H
#define EMF_H

#include <QObject>
#include "src/c++/Elements/element.h"
#include "src/c++/Elements/connector.h"

/**
 * @brief The EMF класс ЭДС
 */
class EMF : public QObject, Element
{
    Q_OBJECT
public:
    explicit EMF(QObject *parent = 0);
    virtual void paintComponent();
    void setHeight(int height);
    void setWidth(int width);
    int getWidth();
    int getHeight();
    const QString HORIZONTAL_ORIENTATION = "HORIZONTAL";
    const QString VERTICAL_ORIENTATION = "VERTICAL";
    virtual void setPosition(int x, int y);
    virtual void connect(int x,int y);
    virtual bool isSelected(int x, int y);
    virtual void enablePointing();
    virtual void disablePointing();
    virtual void disableSelected();
    virtual void enableSelected();
    virtual void changeOrientation();
    virtual Connector* connectorPointCheck(int x, int y);
    virtual int getX();
    virtual int getY();
    virtual ~EMF();
private:
    Connector *c1;
    Connector *c2;
    bool pointed;
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

    /**
     * @brief setConnectorPosition устанавливает позицию коннекторов
     */
    void setConnectorPosition();

signals:


public slots:

};

#endif // EMF_H
