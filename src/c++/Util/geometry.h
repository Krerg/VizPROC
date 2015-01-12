#ifndef GEOMETRY_H
#define GEOMETRY_H

#include <QObject>

/**
 * @brief The Geometry class класс для работы с математикой
 */
class Geometry : public QObject
{
    Q_OBJECT
public:
    explicit Geometry(QObject *parent = 0);
    /**
     * @brief pointCrossX определеяет пересекает ли точка следующей позицией другую
     * точку по оси абсцисс
     * @param oldX старые координаты точки которая двигается
     * @param staticX точка относительно которой смотрится пересечение
     * @param newX новые координаты движущейся точки
     * @return true если пересакает и false в другом случае
     */
    static bool pointCrossX(int oldX, int staticX, int newX);
    /**
     * @brief pointCrossY определяет пересекает ли точка следующей позицией другую
     * точку по оси ординат
     * @param oldY старые координаты движущейся точки
     * @param staticY точка относительно которой смотрится пересечение
     * @param newY новые координаты движущейся точки
     * @return true если пересакает и false в другом случае
     */
    static bool pointCrossY(int oldY, int staticY, int newY);
signals:

public slots:

};

#endif // GEOMETRY_H
