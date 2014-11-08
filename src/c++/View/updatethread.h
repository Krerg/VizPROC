#ifndef UPDATETHREAD_H
#define UPDATETHREAD_H

#include <QObject>
#include <QThread>

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
