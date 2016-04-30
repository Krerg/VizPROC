#ifndef CONSTVALUES_H
#define CONSTVALUES_H

#include <QObject>

/**
 * @brief The ConstValues class класс для константных числовых значений
 */
class ConstValues : public QObject
{
    Q_OBJECT
public:
    explicit ConstValues(QObject *parent = 0);

    /**
     * @brief DIODE_OPEN_TRESHOLD порог открытия для диода
     */
    static const double DIODE_OPEN_TRESHOLD;

    /**
     * @brief BRANCH_AMPERAGE_UNKNOWN
     */
    static const double BRANCH_AMPERAGE_UNKNOWN;

    /**
     * @brief LAST_POINT_EQUAL
     */
    static const int LAST_POINT_EQUAL;

    /**
     * @brief FIRST_POINT_EQUAL
     */
    static const int FIRST_POINT_EQUAL;

    /**
     * @brief NONE_POINT_EQUAL
     */
    static const int NONE_POINT_EQUAL;

    /**
     * @brief POSITIVE_SPEED
     */
    static const int POSITIVE_SPEED;

    /**
     * @brief NEGATIVE_SPPED
     */
    static const int NEGATIVE_SPEED;

signals:

public slots:

};

#endif // CONSTVALUES_H
