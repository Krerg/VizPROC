#ifndef STRINGVALUES_H
#define STRINGVALUES_H

#include <QObject>

class StringValues : public QObject
{
    Q_OBJECT
public:
    explicit StringValues(QObject *parent = 0);

    static const QString EMF_NAME;

    static const QString RESISTOR_NAME;

    static const QString DIODE_NAME;

    static const QString GROUND_NAME;

signals:

public slots:

};

#endif // STRINGVALUES_H
