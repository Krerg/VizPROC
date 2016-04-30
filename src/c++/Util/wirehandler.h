#ifndef WIREHANDLER_H
#define WIREHANDLER_H

#include <QObject>
#include <QPair>
#include "src/c++/Elements/wire.h"


class WireHandler : public QObject
{
    Q_OBJECT
public:
    explicit WireHandler(QObject *parent = 0);

    /**
     * @brief getFirstConnectedWires достает провода присоединенные к данному с начала его пути
     * @param w
     * @return
     */
    static QList<QPair<Wire*,int> >* getFirstConnectedWires(Wire* w);

    /**
     * @brief getLastConnectedWires достает провода присоединенные к данному с конца его пути
     * @param w
     * @return
     */
    static QList<QPair<Wire*,int> >* getLastConnectedWires(Wire* w);

private:

    /**
     * @brief hasPoint проверка на вхождение точки в проводник
     * @param w
     * @param p
     * @return 0 если не входит, 1 если совпадает начальная точка, 2 если совпадает конечная точка
     */
    static int hasPoint(Wire* w, QPoint* p);

    /**
     * @brief getConnectedWire
     * @param p
     * @param w
     * @return
     */
    static QList<QPair<Wire*,int> >* getConnectedWires(QPoint* p, Wire* w);

signals:

public slots:

};

#endif // WIREHANDLER_H
