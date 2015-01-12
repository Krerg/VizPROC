#ifndef GROUND_H
#define GROUND_H

#include <QObject>
#include "src/c++/Elements/connector.h"

/**
 * @brief The Ground class заземление
 */
class Ground : public QObject
{
    Q_OBJECT
public:
    /**
     * @brief Ground конструктор класса
     * @param parent указатель на родительский элемент
     */
    explicit Ground(QObject *parent = 0);

    /**
     * @brief paintComponent отрисовка заземления на экране
     */
    void paintComponent();

    /**
     * @brief setPosition установка позиции на элемента
     * @param x координата по оси абсцисс
     * @param y координата по оси ординат
     */
    void setPosition(int x, int y);

    /**
     * @brief isSelected
     * @param x
     * @param y
     * @return
     */
    bool isSelected(int x, int y);
private:
    /**
     * @brief x координата элемента по оси абсцисс
     */
    int x;

    /**
     * @brief y координата элемента по оси ординат
     */
    int y;

    /**
     * @brief c1 коннектор для соединения с проводом
     */
    Connector* c1;

    /**
     * @brief selected указывает на то, выделен ли элемент
     */
    bool selected;

    /**
     * @brief pointed указывает на то, наведен ли курсор на элемент
     */
    bool pointed;
signals:

public slots:

};

#endif // GROUND_H
