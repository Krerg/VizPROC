#ifndef VOLTMETER_H
#define VOLTMETER_H

#include <QObject>
#include "src/c++/Elements/element.h"
#include "src/c++/Elements/terminal.h"

class Voltmeter : public QObject, Element
{
    Q_OBJECT
public:
    explicit Voltmeter(QObject *parent = 0);
    ~Voltmeter();

    virtual void paintComponent();


    void setUpterminal(Terminal* terminal);

    void setDownTerminal(Terminal* terminal);

    void visualisation();

    void setPosition(int x, int y);
    void connect(int x, int y);
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
    void paintComponent(QPainter *painter);
    QList<Connector *> *getConnectors();

private:

    int x;

    int y;

    int width;

    int height;

    bool pointed;

    bool selected;

    Terminal* upTerminal;

    Terminal* downTerminal;

signals:

public slots:

    // Element interface
public:

};

#endif // VOLTMETER_H
