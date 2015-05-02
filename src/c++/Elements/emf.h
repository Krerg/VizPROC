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
    virtual void disableSelection();
    virtual void enableSelection();
    virtual void changeOrientation();
    virtual Connector* connectorPointCheck(int x, int y);
    virtual int getX();
    virtual int getY();

    /**
     * @brief visualisation
     * @param container1
     * @param container2
     * @param painter
     */
    void visualisation(int* container1, int* container2, QPainter* painter, int radius);

    /**
     * @brief getConnectedWire1
     * @return
     */
    Wire* getConnectedWire1();

    /**
     * @brief getConnectedWire2
     * @return
     */
    Wire* getConnectedWire2();

    /**
     * @brief getAnotherWire
     * @param w
     * @return
     */
    Wire* getAnotherWire(Wire* w);

    /**
     * @brief getAnotherWire
     * @param number
     * @return
     */
    Wire* getAnotherWire(int number);

    /**
     * @brief isGround проверяет заземлен ли проводо или нет
     * @param w
     * @return
     */
    bool isGround(Wire* w);

    /**
     * @brief getConductivity
     * @return возвращает значение проводимсти ЭДС
     */
    int getConductivity();

    /**
     * @brief setConductivity устанавливает значение проводимости ЭДС
     * @param conductivity значение проводимости
     */
    void setConductivity(int conductivity);

    /**
     * @brief getEmfDirection возвращает направление ЭДС по отношению к потенциалу
     * @param wireNumber номер потенциала
     * @return 1 если входит в провод и -1 если наоборот
     */
    int getEmfDirection(int wireNumber);

    /**
     * @brief getEmfDirection возвращает направление ЭДС по отношению к потенциалу
     * @param w wireNumber номер потенциала
     * @return 1 если входит в провод и -1 если наоборот
     */
    int getEmfDirection(Wire* w);

    /**
     * @brief getVoltage
     * @return напряжение на ЭДС
     */
    int getVoltage();

    /**
     * @brief setVoltage устанавливает напряжение на ЭДС
     * @param voltage значение напряжения не ЭДС
     */
    void setVoltage(int voltage);

    virtual QString getName();
    virtual bool getType();
    virtual ~EMF();
private:

    /**
     * @brief voltage напряжение на ЭДС
     */
    int voltage;

    /**
     * @brief conductivity проводимость ЭДС
     */
    int conductivity;

    /**
     * @brief name название элемента
     */
    const QString name = "Emf";

    /**
     * @brief c1 коннектор у большего потенциала
     */
    Connector *c1;

    /**
     * @brief c2 коннектор у меньшего потенциала
     */
    Connector *c2;

    bool pointed;
    bool selected;

    /**
     * @brief x коордимната по оси абсцисс
     */
    int x;

    /**
     * @brief y координата по оси ординат
     */
    int y;

    /**
     * @brief height высота ЭДС
     */
    int height;

    /**
     * @brief width ширина ЭДС
     */
    int width;

    /**
     * @brief pinLength длина выводов ЭДС
     */
    int pinLength;

    /**
     * @brief orientation ориентация положения
     */
    QString orientation;

    /**
     * @brief setConnectorPosition устанавливает позицию коннекторов
     */
    void setConnectorPosition();

signals:


public slots:

};

#endif // EMF_H
