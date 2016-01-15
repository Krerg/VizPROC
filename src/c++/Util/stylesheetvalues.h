#ifndef STYLESHEETVALUES_H
#define STYLESHEETVALUES_H

#include <QObject>
#include <QString>



class StyleSheetValues : public QObject
{
    Q_OBJECT
public:

    explicit StyleSheetValues(QObject *parent = 0);
    ~StyleSheetValues();
    static const QString BUTTON_STYLE;

    static const QString RESISTOR_BUTTON_STYLE;

    static const QString BUTTON_ACTIVATED_STYLE;

    static const QString RESISTOR_BUTTON_HOVER_STYLE;
signals:

public slots:
};


#endif // STYLESHEETVALUES_H

