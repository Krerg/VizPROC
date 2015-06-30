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
    virtual QList<Connector *> *getConnectors();
    int getWidth();
    int getHeight();
    virtual QString getName();
    virtual bool getType();
    virtual void disconnectWire(Wire *w);
    int getOpeningThreshold();
    void setOpeningThreshold();
    void setPainter(QPainter* painter);


    void open();



    void close();

    /**
     * @brief getConnector1
     * @return
     */
    Connector* getConnector1();

    /**
     * @brief getConnector2
     * @return
     */
    Connector* getConnector2();

    /**
     * @brief getAnotherWire
     * @param number
     * @return
     */
    Wire* getAnotherWire(int number);

    /**
     * @brief getEmfDirection возвращает направление ЭДС по отношению к потенциалу
     * @param wireNumber номер потенциала
     * @return 1 если входит в провод и -1 если наоборот
     */
    int getEmfDirection(int wireNumber);

    /**
     * @brief getConductivity
     * @return возвращает значение проводимсти ЭДС
     */
    int getConductivity();

    /**
     * @brief getVoltage
     * @return напряжение на ЭДС
     */
    double getVoltage();

    /**
     * @brief isOpened
     * @return
     */
    bool isOpened();

    /**
     * @brief visualisation
     * @param painter
     */
    void visualisation(int *container1, int *container2, QPainter *painter, int radius);

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
    Connector* c1;
    Connector* c2;
    QPainter* painter;

    bool opened;

    void setConnectorPosition();

signals:

public slots:
};

#endif // DIODE_H
