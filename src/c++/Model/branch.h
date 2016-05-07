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
     * @brief addElement добавление элемента в ветвь
     * @param elem сам элемент
     * @param append добавление в конец или начало списка
     * @param check проверка на диоды
     */
    void addElement(Element* elem, bool append, bool check);

    /**
     * @brief addWire
     * @param w
     */
    void addWire(Wire* w, bool append);

    /**
     * @brief setVertexNumber1
     * @param vertexNumber
     */
    void setVertexNumber1(int vertexNumber);

    /**
     * @brief setVertexNumber2
     * @param vertexNumber
     */
    void setVertexNumber2(int vertexNumber);

    int getVertexNumber1();

    int getVertexNumber2();

    /**
     * @brief getAmperage
     * @return
     */
    double getAmperage();

    /**
     * @brief setAmperage установка напряжения на ветви
     * @param amperage напряжение на ветви
     */
    void setAmperage(double amperage);

    ~Branch();

    /**
     * @brief isHasEmf показывает содержит ли ветвь ЭДС
     * @return true если содержит, в противном случае false
     */
    bool isHasEmf();

    /**
     * @brief open открывает ветвь, для протекания через нее тока
     */
    void open();

    /**
     * @brief getBranchElements возвращает списко элементов в ветви
     * @return
     */
    QList<Element *> *getBranchElements();

    /**
     * @brief getBranchWires врзвращает список проводов в ветви
     * @return
     */
    QList<Wire *> *getBranchWires();

    /**
     * @brief getDiodeCount возвращает кол-во диодов в ветви
     * @return кол-во диодов в ветви
     */
    int getDiodeCount();

private:

    int diodeCount;

    void close();

    bool hasEmf;

    /**
     * @brief opened
     */
    bool opened;

    /**
     * @brief vertexNumber1 номер первой присоединенной вершины
     */
    int vertexNumber1;

    /**
     * @brief vertexNumber2 номер второй присоединенной вершины
     */
    int vertexNumber2;

    /**
     * @brief amperage сила тока на ветви
     */
    double amperage;

    /**
     * @brief isDiode переменная указывающая диодная ли ветвь
     */
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
