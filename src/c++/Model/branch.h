#ifndef BRANCH_H
#define BRANCH_H

#include <QObject>
#include "src/c++/Elements/element.h"
#include "src/c++/Elements/wire.h"
#include "QList"

/**
 * @brief The Branch class класс, реализующий ветвь в графе
 */
class Branch : public QObject
{
    Q_OBJECT
public:

    /**
     * @brief Branch публичный конструктор
     * @param parent родительский элемент
     */
    explicit Branch(QObject *parent = 0);

    /**
     * @brief unionBranch метод объединения нескольких ветвей
     * @param anotherBranch ветвь, с которой нужно объединить
     */
    void unionBranch(Branch* anotherBranch);

    /**
     * @brief isDiodeBranch
     * @return
     */
    bool isDiodeBranch();

    /**
     * @brief addElement
     * @param elem
     */
    void addElement(Element* elem);

    /**
     * @brief addWire
     * @param w
     */
    void addWire(Wire* w);

    ~Branch();

private:

    bool isDiode;

    /**
     * @brief branchElements список элементов, входящих в ветвь
     */
    QList<Element*> *branchElements;

    /**
     * @brief branchWires список проводов, входящих в ветвь
     */
    QList<Wire*> *branchWires;

signals:

public slots:

};

#endif // BRANCH_H
