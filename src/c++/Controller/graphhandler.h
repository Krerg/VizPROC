#ifndef GRAPHHANDLER_H
#define GRAPHHANDLER_H

#include <QObject>
#include "src/c++/Elements/element.h"

class GraphHandler : public QObject
{
    Q_OBJECT
public:
    explicit GraphHandler(QObject *parent = 0);
    ~GraphHandler();

    void setElements(QList<Element*> *elements);
private:

    /**
     * @brief elements
     */
    QList<Element*> *elements;

    /**
     * @brief handleElement
     * @param elem
     * @return
     */
    bool handleElement(Element* elem);
signals:
    /**
     * @brief start
     */
    void start();

    /**
     * @brief cohesionError
     */
    void cohesionError();
public slots:

    /**
     * @brief handle обработа схемы и проверка на связность
     * @param elements
     */
    void handle();

};

#endif // GRAPHHANDLER_H
