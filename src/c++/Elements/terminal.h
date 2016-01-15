#ifndef TERMINAL_H
#define TERMINAL_H

#include <QObject>
#include "src/c++/Elements/wire.h"

class Terminal : public QObject, Element
{
    Q_OBJECT
public:
    explicit Terminal(QObject *parent = 0);
    ~Terminal();

    /**
     * @brief setConnectedWire
     * @param w
     */
    void setConnectedWire(Wire* w);

    /**
     * @brief isConnected
     * @return
     */
    bool isConnected();

    /**
     * @brief getValue
     * @return
     */
    double getValue();

    /**
     * @brief paintComponent
     * @param painter
     */
    void paintComponent(QPainter* painter);

    /**
     * @brief clearConnection
     */
    void clearConnection();

    /**
     * @brief setColor
     * @param color
     */
    void setColor(QColor color);

private:

    QColor color;

    int x;

    int y;

    Wire* connectedWire;

signals:

public slots:

    // Element interface
public:
    void setPosition(int x, int y);
    void connect(int x, int y);
    void paintComponent();
    bool isSelected(int x, int y);
    void disableSelection();
    void enableSelection();
    void enablePointing();
    void disablePointing();
    void changeOrientation();
    Connector *connectorPointCheck(int x, int y);
    int getX();
    int getY();
    bool getType();
    QString getName();
    void disconnectWire(Wire *w);
    QList<Connector *> *getConnectors();
};

#endif // TERMINAL_H
