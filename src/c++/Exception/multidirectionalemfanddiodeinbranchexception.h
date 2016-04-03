#ifndef MULTIDIRECTIONALEMFANDDIODEINBRANCHEXCEPTION_H
#define MULTIDIRECTIONALEMFANDDIODEINBRANCHEXCEPTION_H

#include <QException>

/**
 * @brief The MultidirectionalEmfAndDiodeInBranchException class исключение,
 * выбрасываемое при несоответствии направления ЭДС и диода в одной ветви
 */
class MultidirectionalEmfAndDiodeInBranchException : public QException
{
    Q_OBJECT
public:

    void raise() const {throw *this;}

    QException *clone() const { return new MultidirectionalEmfAndDiodeInBranchException(*this); }

signals:

public slots:

};

#endif // MULTIDIRECTIONALEMFANDDIODEINBRANCHEXCEPTION_H
