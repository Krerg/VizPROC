#ifndef FILEHANDLER_H
#define FILEHANDLER_H

#include <QObject>
#include "src/c++/View/componentmanager.h"
#include <QXmlStreamReader>

/**
 * @brief The FileHandler class класс для обработки файлов (сохранение/загрузка)
 */
class FileHandler : public QObject
{
    Q_OBJECT
public:
    explicit FileHandler(QObject *parent = 0);
    ~FileHandler();

    /**
     * @brief saveFile сохранение в файл
     * @param cm менеджер компоенент
     */
    static void saveFile(ComponentManager* cm);

    /**
     * @brief openFile открытие файла
     * @param cm
     */
    static void openFile(ComponentManager* cm);

private:

    /**
     * @brief readConnections чтение соединений между элементами
     * @param cm менеджер компонент для загрузки
     */
    static void readConnections(ComponentManager* cm, QXmlStreamReader* reader);

    /**
     * @brief readPotential чтение потенциала с проводами
     * @param cm менеджер комопнент для загрузки
     * @param reader xmlReader
     */
    static void readPotential(ComponentManager* cm, QXmlStreamReader* reader);

    /**
     * @brief readWire чтение и сохранение провода в менеджер компонент
     * @param cm менеджер компонент
     * @param reader xmlReader
     * @return провод
     */
    static Wire* readWire(ComponentManager* cm, QXmlStreamReader* reader);

    /**
     * @brief readPath чтение точек отрисовки для провода
     * @param reader xmlReader
     * @param w провод для которого происходит чтение
     */
    static void readPath(QXmlStreamReader* reader, Wire* w);

    /**
     * @brief connectWireFirstPointToElement соединение начальной точки провода с элементом
     * @param w Соединяемый провод
     * @param elem Соединяемый элемент
     */
    static void connectWireFirstPointToElement(Wire* w, Element* elem);

    /**
     * @brief connectWireFirstPointToElement соединение конечной точки провода с элементом
     * @param w соединяемый провод
     * @param elem соединяемый элемент
     */
    static void connectWireLastPointToElement(Wire* w, Element* elem);
signals:

public slots:
};

#endif // FILEHANDLER_H
