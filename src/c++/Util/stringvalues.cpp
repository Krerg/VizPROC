#include "stringvalues.h"

const QString StringValues::EMF_NAME = "Emf";

const QString StringValues::RESISTOR_NAME = "Res";

const QString StringValues::DIODE_NAME = "Diode";

const QString StringValues::GROUND_NAME = "Ground";

StringValues::StringValues(QObject *parent) :
    QObject(parent)
{

}
