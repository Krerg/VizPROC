#ifndef MULTIDIRECTIONALDIODESINBRANCHEXCEPTION_H
#define MULTIDIRECTIONALDIODESINBRANCHEXCEPTION_H

#include <QObject>
#include <QException>

/**
 * @brief The MultidirectionalDiodesInBranchException class иключение выбрасываемое при расчете схемы,
 * когда одна ветвь имеет несколько разнонаправленных диода
 * TODO добавить информацию о ветви
 */
class MultidirectionalDiodesInBranchException : public QException
{
public:

    void raise() const { throw *this; }

    QException *clone() const { return new MultidirectionalDiodesInBranchException(*this); }
};

#endif // MULTIDIRECTIONALDIODESINBRANCHEXCEPTION_H
