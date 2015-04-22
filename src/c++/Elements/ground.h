#ifndef GROUND_H
#define GROUND_H

#include <QObject>
#include "src/c++/Elements/connector.h"

/**
 * @brief The Ground class заземление
 */
class Ground : public QObject, Element
{
    Q_OBJECT
public:
    /**
     * @brief Ground конструктор класса
     * @param parent указатель на родительский элемент
     */
    explicit Ground(QObject *parent = 0);
    virtual void paintComponent();
    virtual void setPosition(int x, int y);
    virtual bool isSelected(int x, int y);
    int getHeight();
    int getWidth();
    virtual void enablePointing();
    virtual void disablePointing();
    virtual void enableSelection();
    virtual void disableSelection();
    virtual void connect(int x, int y);
    virtual void changeOrientation();
    virtual Connector* connectorPointCheck(int x, int y);
    virtual int getX();
    virtual int getY();
    virtual bool getType();
    virtual QString getName();
    virtual ~Ground();
    void visualisation(QPainter* painter);
private:
    /**
     * @brief x координата элемента по оси абсцисс
     */
    int x;

    /**
     * @brief y координата элемента по оси ординат
     */
    int y;

    /**
     * @brief c1 коннектор для соединения с проводом
     */
    Connector* c1;

    /**
     * @brief selected указывает на то, выделен ли элемент
     */
    bool selected;

    /**
     * @brief pointed указывает на то, наведен ли курсор на элемент
     */
    bool pointed;

    /**
     * @brief width ширина элемента
     */
    int width;

    /**
     * @brief height высота элемента
     */
    int height;

    /**
     * @brief setConnectorPosition
     */
    void setConnectorPosition();
signals:

public slots:

};

#endif // GROUND_H
