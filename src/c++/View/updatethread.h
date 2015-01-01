#ifndef UPDATETHREAD_H
#define UPDATETHREAD_H

#include <QObject>
#include <QThread>

/**
 * @brief The UpdateThread class класс-потокб который обновляет избражение на экране с заданной частотой
 */
class UpdateThread : public QThread
{
    Q_OBJECT
public:
    explicit UpdateThread(QObject *parent = 0);


protected:
    void run();
public:

private:

signals:
    void update();
public slots:

};

#endif // UPDATETHREAD_H
