#ifndef PARTICLE_H
#define PARTICLE_H

#include <QObject>
#include <QList>
#include <QPainter>
#include <QPoint>

/**
 * @brief The Particle class класс частицы визуализации токов
 */
class Particle : public QObject
{
    Q_OBJECT
public:
    explicit Particle(QObject *parent = 0);

    /**
     * @brief setPath утсановка пути для движения
     * @param path список точек
     * @param numb номер точки, на которую частица "притягивается"
     */
    void setPath(QList<QPoint*> *path, int numb);

    /**
     * @brief setPosition установка позиции на экране
     * @param x координата по оси абсцисс
     * @param y координата по оси ординат
     */
    void setPosition(int x, int y);

    /**
     * @brief visualisation отрисовка на экране
     * @param painter
     */
    void visualisation(QPainter* painter);


    ~Particle();
private:
    /**
     * @brief x
     */
    int x;

    /**
     * @brief y
     */
    int y;

    /**
     * @brief pointNumber
     */
    int pointNumber;

    /**
     * @brief path
     */
    QList<QPoint*>* path;

signals:

public slots:
};

#endif // PARTICLE_H
