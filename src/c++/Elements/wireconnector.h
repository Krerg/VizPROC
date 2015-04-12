#ifndef WIRECONNECTOR_H
#define WIRECONNECTOR_H

#include <QObject>

class WireConnector : public QObject
{
    Q_OBJECT
public:
    explicit WireConnector(int x, int y,QObject *parent = 0);
    ~WireConnector();
    void paintComponent();
    int getX();
    int getY();
private:
    int x;
    int y;

signals:

public slots:
};

#endif // WIRECONNECTOR_H
