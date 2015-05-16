#ifndef DIODEBRANCH_H
#define DIODEBRANCH_H

#include <QObject>
#include "src/c++/Elements/wire.h"
#include "src/c++/Elements/diode.h"
#include <QList>
#include <QMap>

class DiodeBranch : public QObject
{
    Q_OBJECT
public:
    explicit DiodeBranch(QObject *parent = 0);
    ~DiodeBranch();
    /**
     * @brief open открытие ветки в графе
     */
    void open();

    /**
     * @brief addWire
     * @param w
     */
    void addWire(Wire* w);

    /**
     * @brief addDiode
     * @param diode
     */
    void addDiode(Diode* diode);

    /**
     * @brief setGraph
     * @param graph
     */
    void setGraph(QMap<Wire*,int*>* graph);

    /**
     * @brief checkBranch
     * @return
     */
    bool checkBranch();

    /**
     * @brief setUpWire
     * @param w
     */
    void setUpWire(Wire* w);

    /**
     * @brief setDownWire
     * @param w
     */
    void setDownWire(Wire* w);
private:
    /**
     * @brief diodes список диодов на ветке
     */
    QList<Diode*>* diodes;

    /**
     * @brief wires список проводов на ветке
     */
    QList<Wire*>* wires;

    /**
     * @brief graph граф схемы
     */
    QMap<Wire*,int*>* graph;

    /**
     * @brief upWire
     */
    Wire* upWire;

    /**
     * @brief downWire
     */
    Wire* downWire;
signals:

public slots:
};

#endif // DIODEBRANCH_H
