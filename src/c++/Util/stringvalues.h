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

    static const QString TRANSISTOR_NAME;

    /**
     * @brief GRAPH_ISOLATION_COMPLETE статус после изоляции диодных втевей: успешно
     */
    static const QString GRAPH_ISOLATION_COMPLETE;

    /**
     * @brief GRAPH_ISOLATION_NEED_DIODE_OPEN статус после изоляции диодных втевей: успешно, но нужно открыть диодную ветвь
     */
    static const QString GRAPH_ISOLATION_NEED_DIODE_OPEN;

    /**
     * @brief GRAPH_ISOLATION_ERROR статус после изоляции диодных втевей: ошибка (граф не инициализирован)
     */
    static const QString GRAPH_ISOLATION_ERROR;

    /**
     * @brief NO_SUCH_COLTAGE_FOR_OPEN_DIODE_MESSAGE сообщение об ошибке, говорящее о недостаточном напряжении на ЭДС для открытия диода
     */
    static const QString NO_SUCH_COLTAGE_FOR_OPEN_DIODE_MESSAGE;

    /**
     * @brief VOLTAGE_MAP_VALUE
     */
    static const QString VOLTAGE_MAP_VALUE;

    /**
     * @brief RESISTANCE_MAP_VALUE
     */
    static const QString RESISTANCE_MAP_VALUE;

signals:

public slots:

};

#endif // STRINGVALUES_H
