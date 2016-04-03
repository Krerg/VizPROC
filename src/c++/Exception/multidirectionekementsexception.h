#ifndef MULTIDIRECTIONEKEMENTSEXCEPTION_H
#define MULTIDIRECTIONEKEMENTSEXCEPTION_H

#include <QException>

/**
 * @brief The MultidirectionEkementsException class Исключение, выбрасываемое при несоответствии направдений элементов (ЭДС, диод)
 */
class MultidirectionEkementsException : public QException
{
public:

    void raise() const { throw *this; }

};

#endif // MULTIDIRECTIONEKEMENTSEXCEPTION_H
