#include "constvalues.h"

const double ConstValues::DIODE_OPEN_TRESHOLD = 0.6;

const double ConstValues::BRANCH_AMPERAGE_UNKNOWN = -1.0;

const int ConstValues::NONE_POINT_EQUAL = 0;

const int ConstValues::FIRST_POINT_EQUAL = 1;

const int ConstValues::LAST_POINT_EQUAL = 2;

ConstValues::ConstValues(QObject *parent) :
    QObject(parent)
{
}
