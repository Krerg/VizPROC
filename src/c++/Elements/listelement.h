#ifndef LISTELEMENT_H
#define LISTELEMENT_H

#include <QObject>
#include <QString>

class ListElement : public QObject
{
    Q_OBJECT
public:
    explicit ListElement(QObject *parent = 0);
    void setType(QString type);
    void setElement(QObject *element);
    QString getType();
    QObject* getElement();
private:
    QString type;
    QObject *element;
signals:

public slots:

};

#endif // LISTELEMENT_H
