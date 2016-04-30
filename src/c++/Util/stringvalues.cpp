#include "stringvalues.h"

const QString StringValues::EMF_NAME = "Emf";

const QString StringValues::RESISTOR_NAME = "Res";

const QString StringValues::DIODE_NAME = "Diode";

const QString StringValues::GROUND_NAME = "Ground";

const QString StringValues::TRANSISTOR_NAME = "Transistor";

const QString StringValues::GRAPH_ISOLATION_COMPLETE = "graphIsolComplete";

const QString StringValues::GRAPH_ISOLATION_NEED_DIODE_OPEN = "graphIsolNeedDeiodeOpen";

const QString StringValues::GRAPH_ISOLATION_ERROR = "graphIsolError";

const QString StringValues::NO_SUCH_COLTAGE_FOR_OPEN_DIODE_MESSAGE = "Недостаточное напряжение на ЭДС для работы схемы";

const QString StringValues::VOLTAGE_MAP_VALUE = "voltage";

const QString StringValues::RESISTANCE_MAP_VALUE = "resistance";

StringValues::StringValues(QObject *parent) :
    QObject(parent)
{

}
