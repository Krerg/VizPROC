#ifndef CONNECTOR_H
#define CONNECTOR_H

#include <QObject>

/**
 * @brief The Connector class коннектор, который соединяет провод и элемент
 */
class Connector : public QObject
{
    Q_OBJECT
public:
    /**
     * @brief Connector конструктор класса
     * @param parent указатель на родительский элемент
     */
    explicit Connector(QObject *parent = 0);

    /**
     * @brief setConnection связывание коннектора с элементом
     * @param
     */
    void setConnection();

    /**
     * @brief setPosition утсановка позиции коннектора
     * @param x
     * @param y
     */
    void setPosition(int x, int y);

    /**
     * @brief getX возвращает координатц позиции коннектора по оси абсцисс
     * @return
     */
    int getX();

    /**
     * @brief getY возвращает координату позиции коннектора по оси ординат
     * @return
     */
    int getY();

    /**
     * @brief getConnectedElement возвращает присоединенный провод к коннектору
     * @return
     */
    void getConnectedElement();

    /**
     * @brief drawComponent отрисовка на экране
     */
    void drawComponent();

    /**
     * @brief enablePointing делает коннектор наведенным
     */
    void enablePointing();

    /**
     * @brief disablePointing снимает наведение с коннектора
     */
    void disablePointing();

    /**
     * @brief checkPointing проверяет на то, что курсора наведен на коннектор
     * @param x координата курсора по оси обсцисс
     * @param y координата курсора по оси ординат
     * @return
     */
    bool checkPointing(int x, int y);
private:
    /**
     * @brief x координата на экране
     */
    int x;

    /**
     * @brief y координата на экране
     */
    int y;

    /**
     * @brief width ширина коннектора
     */
    int width;

    /**
     * @brief height высота коннектора
     */
    int height;

    /**
     * @brief pointed наведен ли курсор на коннектор
     */
    bool pointed;
signals:

public slots:

};
\
#endif // CONNECTOR_H
