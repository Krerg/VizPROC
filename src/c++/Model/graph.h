#ifndef GRAPH_H
#define GRAPH_H

#include <QObject>

/**
 * @brief The Graph class класс, который представляет схему в виде графа
 */
class Graph : public QObject
{
    Q_OBJECT
public:
    explicit Graph(QObject *parent = 0);

signals:

public slots:

};

#endif // GRAPH_H
