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
     * @brief readConnections
     * @param cm
     */
    static void readConnections(ComponentManager* cm, QXmlStreamReader* reader);

    /**
     * @brief readPotential
     * @param cm
     * @param reader
     */
    static void readPotential(ComponentManager* cm, QXmlStreamReader* reader);

    /**
     * @brief readWire
     * @param cm
     * @param reader
     * @return
     */
    static Wire* readWire(ComponentManager* cm, QXmlStreamReader* reader);

    /**
     * @brief readPath
     * @param reader
     * @param w
     */
    static void readPath(QXmlStreamReader* reader, Wire* w);

    /**
     * @brief connectWireFirstPointToElement
     * @param w
     * @param elem
     */
    static void connectWireFirstPointToElement(Wire* w, Element* elem);

    /**
     * @brief connectWireFirstPointToElement
     * @param w
     * @param elem
     */
    static void connectWireLastPointToElement(Wire* w, Element* elem);
signals:

public slots:
};

#endif // FILEHANDLER_H
