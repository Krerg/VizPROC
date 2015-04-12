#ifndef DIODE_H
#define DIODE_H

#include <QObject>
#include <src/c++/Elements/element.h>
#include <src/c++/Elements/connector.h>
#include <QPainter>

/**
 * @brief The Diode class класс диода
 */
class Diode : public QObject, Element
{
    Q_OBJECT
public:
    explicit Diode(QObject *parent = 0);
    virtual void paintComponent();
    virtual void setPosition(int x, int y);
    //надо удалить
    virtual void connect(int x, int y);
    virtual bool isSelected(int x, int y);
    virtual void enableSelection();
    virtual void disableSelection();
    virtual void enablePointing();
    virtual void disablePointing();
    virtual void changeOrientation();
    virtual Connector* connectorPointCheck(int x, int y);
    virtual int getX();
    virtual int getY();
    int getWidth();
    int getHeight();
    virtual QString getName();
    virtual bool getType();
    int getOpeningThreshold();
    void setOpeningThreshold();
    ~Diode();
private:

    /**
     * @brief HORIZONTAL_ORIENTATION
     */
    const QString HORIZONTAL_ORIENTATION = "HORIZONTAL";

    /**
     * @brief VERTICAL_ORIENTATION
     */
    const QString VERTICAL_ORIENTATION = "VERTICAL";

    /**
     * @brief openingThreshold порог открытия диода в вольтах
     */
    int openingThreshold;

    int x;
    int y;
    bool pointed;
    bool selected;
    int height;
    QPainter* render;
    int width;
    int pinLength;
    QString orientation;
    Connector* c1;
    Connector* c2;

    void setConnectorPosition();

signals:

public slots:
};

#endif // DIODE_H
