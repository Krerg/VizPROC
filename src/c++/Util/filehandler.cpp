#include "filehandler.h"
#include <QFileDialog>
#include <QDebug>
#include <QXmlStreamWriter>
#include <QXmlStreamReader>
#include "src/c++/Elements/element.h"
#include "src/c++/Elements/resistor.h"
#include "src/c++/Elements/emf.h"
#include "src/c++/Elements/diode.h"
#include "src/c++/Elements/ground.h"
#include "src/c++/Elements/wire.h"
#include <QList>
#include <QPoint>

FileHandler::FileHandler(QObject *parent) : QObject(parent)
{

}

FileHandler::~FileHandler()
{

}

void FileHandler::saveFile(ComponentManager *cm)
{
    QList<Element*>* elements = cm->getElements();
    QList<Element*>::Iterator i;
    QList<Wire*>::Iterator j;
    QFileDialog fileDialog;
    fileDialog.setNameFilter(tr("VizProc files (*.vproc)"));
    QString fileName = QFileDialog::getSaveFileName(
                0,
                tr("Save Document"),
                QDir::currentPath(),
                tr("VizPROC project file (*.vpro)") );
    QFile f(fileName);
    f.open(QIODevice::WriteOnly);
    QXmlStreamWriter writer(&f);
    writer.setAutoFormatting(true);
    writer.writeStartDocument("1.0");
    writer.writeComment("Test file");
        writer.writeStartElement("Circuit"); //<Circuit>
            writer.writeStartElement("Elements"); //<Elements>
                int savingNumber=0;
                for(i=elements->begin();i!=elements->end();i++) {
                    (*i)->setSavingNumber(savingNumber);
                    if((*i)->getName()=="Res") {
                        Resistor* resTemp = (Resistor*)(*i);
                        writer.writeStartElement("Resistor");
                                writer.writeStartElement("Orientation");
                                    writer.writeAttribute("value",(*i)->getPosition());
                                writer.writeEndElement();
                                writer.writeStartElement("x");
                                    writer.writeAttribute("value",QString::number(resTemp->getX()));
                                writer.writeEndElement();
                                writer.writeStartElement("y");
                                    writer.writeAttribute("value",QString::number(resTemp->getY()));
                                writer.writeEndElement();
                        writer.writeEndElement();
                    } else if((*i)->getName()=="Emf") {
                        EMF* emfTemp = (EMF*)(*i);
                        writer.writeStartElement("EMF");
                                writer.writeStartElement("Orientation");
                                    writer.writeAttribute("value",(*i)->getPosition());
                                writer.writeEndElement();
                                writer.writeStartElement("x");
                                    writer.writeAttribute("value",QString::number(emfTemp->getX()));
                                writer.writeEndElement();
                                writer.writeStartElement("y");
                                    writer.writeAttribute("value",QString::number(emfTemp->getY()));
                                writer.writeEndElement();
                        writer.writeEndElement();
                    } else if((*i)->getName()=="Diode") {
                        Diode* diodeTemp = (Diode*)(*i);
                        writer.writeStartElement("Diode");
                                writer.writeStartElement("Orientation");
                                    writer.writeAttribute("value",(*i)->getPosition());
                                writer.writeEndElement();
                                writer.writeStartElement("x");
                                    writer.writeAttribute("value",QString::number(diodeTemp->getX()));
                                writer.writeEndElement();
                                writer.writeStartElement("y");
                                    writer.writeAttribute("value",QString::number(diodeTemp->getY()));
                                writer.writeEndElement();
                        writer.writeEndElement();
                    } else if((*i)->getName()=="Ground") {
                        Ground* groundTemp = (Ground*)(*i);
                        writer.writeStartElement("Ground");
                                writer.writeStartElement("Orientation");
                                    writer.writeAttribute("value",(*i)->getPosition());
                                writer.writeEndElement();
                                writer.writeStartElement("x");
                                    writer.writeAttribute("value",QString::number(groundTemp->getX()));
                                writer.writeEndElement();
                                writer.writeStartElement("y");
                                    writer.writeAttribute("value",QString::number(groundTemp->getY()));
                                writer.writeEndElement();
                        writer.writeEndElement();
                    }
                    savingNumber++;
                }
            writer.writeEndElement(); //</Elements>
            writer.writeStartElement("Connections"); //<Connections>
                //провода
                QList<Wire*>* wires = cm->getWires();
                for(j=wires->begin();j!=wires->end();j++) {
                    if((*j)->isSaved()) {
                        (*j)->resetSavingFlag();
                        continue;
                    }
                    QList<Wire*>* potential = (*j)->getConnectedWires();
                    QList<Wire*>::Iterator k;
                    writer.writeStartElement("Potential"); //<Potential>
                        for(k=potential->begin();k!=potential->end();k++) {
                            writer.writeStartElement("Wire"); //<Wire>

                                writer.writeStartElement("Path"); //<Path>
                                    QList<QPoint*>* path = (*k)->getPath();
                                    QList<QPoint*>::Iterator l;
                                    for(l=path->begin();l!=path->end();l++) {
                                        writer.writeStartElement("Point");
                                        writer.writeAttribute("x",QString::number((*l)->x()));
                                        writer.writeAttribute("y",QString::number((*l)->y()));
                                        writer.writeEndElement();
                                    }
                                writer.writeEndElement(); //</Path>
                                //соединение с другими
                                Connector* connector1 = (*k)->getConneted1();
                                Connector* connector2 = (*k)->getConneted2();
                                if(connector1!=NULL) {
                                    writer.writeStartElement("Connected1");
                                        writer.writeAttribute("Element",QString::number(connector1->getParentElement()->getSavingNumber()));
                                    writer.writeEndElement();
                                }
                                if(connector2!=NULL) {
                                    writer.writeStartElement("Connected2");
                                        writer.writeAttribute("Element",QString::number(connector2->getParentElement()->getSavingNumber()));
                                    writer.writeEndElement();
                                }
                            writer.writeEndElement(); //</Wire>
                            (*k)->setSavedFlag();
                        }
                    writer.writeEndElement(); //</Potential>
                    (*j)->resetSavingFlag();
                }
            writer.writeEndElement(); //</Connections>
        writer.writeEndElement(); //<//Circuit>
    writer.writeEndDocument();
    f.close();
}

void FileHandler::openFile(ComponentManager *cm)
{
    QFileDialog fileDialog;
    QFile f(fileDialog.getOpenFileName());
    f.open(QIODevice::ReadOnly);
    QXmlStreamReader reader(&f);
    int x;
    int y;
    Resistor* tmpRes;
    EMF* tmpEmf;
    Ground* groundTemp;
    while(!reader.atEnd() && !reader.hasError()) {
        reader.readNext();
        if (reader.isStartDocument())
                    continue;
        if (reader.isStartElement()) {
            if (reader.name().toString() == "Circuit") {
                continue;
            }
            if (reader.name().toString() == "Elements") {
                while (true) {
                    //считывание элементов
                    reader.readNext();
                    if (reader.isStartElement() && reader.name().toString() == "Resistor") {
                        //считывание атрибутов резистора
                        tmpRes = new Resistor();
                        while (true) {
                            //считывание элементов
                            reader.readNext();
                            if(reader.name()=="Orientation") {
                                try {
                                    if(reader.attributes().size()==0) {
                                        continue;
                                    }
                                    ((Element*)(tmpRes))->setPosition(reader.attributes().at(0).value().toString());
                                } catch (...) {
                                    qDebug()<<"Error while parsing file";
                                }
                            }

                            if(reader.name()=="x") {
                                if(reader.attributes().size()==0) {
                                    continue;
                                }
                                x = reader.attributes().at(0).value().toInt();
                            }

                            if(reader.name()=="y") {
                                if(reader.attributes().size()==0) {
                                    continue;
                                }
                               y =  reader.attributes().at(0).value().toInt();
                            }
                            if(reader.isEndElement() && reader.name()=="Resistor") {
                                break;
                            }

                        }
                        tmpRes->setPosition(x,y);
                        cm->addResistor(tmpRes);
                        tmpRes=NULL;
                    } else if (reader.isStartElement() && reader.name().toString() == "EMF") {
                        //считывание атрибутов резистора
                        tmpEmf = new EMF();
                        while (true) {
                            //считывание элементов
                            reader.readNext();
                            if(reader.name()=="Orientation") {
                                try {
                                    if(reader.attributes().size()==0) {
                                        continue;
                                    }
                                    ((Element*)(tmpEmf))->setPosition(reader.attributes().at(0).value().toString());
                                } catch (...) {
                                    qDebug()<<"Error while parsing file";
                                }
                            }

                            if(reader.name()=="x") {
                                if(reader.attributes().size()==0) {
                                    continue;
                                }
                                x = reader.attributes().at(0).value().toInt();
                            }

                            if(reader.name()=="y") {
                                if(reader.attributes().size()==0) {
                                    continue;
                                }
                               y =  reader.attributes().at(0).value().toInt();
                            }
                            if(reader.isEndElement() && reader.name()=="EMF") {
                                break;
                            }

                        }
                        tmpEmf->setPosition(x,y);
                        cm->addEMF(tmpEmf);
                    } else if (reader.isStartElement() && reader.name().toString() == "Ground") {
                        //считывание атрибутов резистора
                        groundTemp = new Ground();
                        while (true) {
                            //считывание элементов
                            reader.readNext();
                            if(reader.name()=="Orientation") {
                                try {
                                    if(reader.attributes().size()==0) {
                                        continue;
                                    }
                                    ((Element*)(groundTemp))->setPosition(reader.attributes().at(0).value().toString());
                                } catch (...) {
                                    qDebug()<<"Error while parsing file";
                                }
                            }

                            if(reader.name()=="x") {
                                if(reader.attributes().size()==0) {
                                    continue;
                                }
                                x = reader.attributes().at(0).value().toInt();
                            }

                            if(reader.name()=="y") {
                                if(reader.attributes().size()==0) {
                                    continue;
                                }
                               y =  reader.attributes().at(0).value().toInt();
                            }
                            if(reader.isEndElement() && reader.name()=="Ground") {
                                break;
                            }

                        }
                        groundTemp->setPosition(x,y);
                        cm->addGround(groundTemp);
                    }

                    if(reader.isEndElement() && reader.name()=="Circuit") {
                        break;
                    }

                    if (reader.name().toString() == "Connections") {
                        readConnections(cm,&reader);
                    }

                }
            }
        }
    }
    f.close();
}

void FileHandler::readConnections(ComponentManager *cm, QXmlStreamReader *reader)
{
    //QList<Wire*> wires = cm->getWires();
    while(true) {
        reader->readNext();
        if(reader->isEndElement() && reader->name() == "Connections") {
            break;
        }
        if(reader->name()=="Potential") {
            readPotential(cm, reader);
        }
    }
}

void FileHandler::readPotential(ComponentManager *cm, QXmlStreamReader *reader)
{
    QList<Wire*> *wires = cm->getWires();
    QList<Wire*> *potential = new QList<Wire*>();
    while(true) {
        reader->readNext();
        if(reader->isEndElement() && reader->name() == "Potential") {
            break;
        }
        if(reader->name()=="Wire" && reader->isStartElement()) {
            Wire* tmpWire = readWire(cm, reader);
            potential->append(tmpWire);
            tmpWire->setWireList(potential);
            //wires->append(tmpWire);
            cm->addWire(tmpWire);
        }
    }
}

Wire *FileHandler::readWire(ComponentManager *cm, QXmlStreamReader *reader)
{
    Wire* wire = new Wire();
    while(true) {
        reader->readNext();
        if(reader->isEndElement() && reader->name() == "Wire") {
            break;
        }
        if(reader->name()=="Path") {
            readPath(reader,wire);
        }
        if(reader->name()=="Connected1" && reader->attributes().length()>0) {
            //qDebug()<<"Connected1";
            int elemIndex = reader->attributes().at(0).value().toInt();
            connectWireFirstPointToElement(wire,cm->getElements()->at(elemIndex));
        }
        if(reader->name()=="Connected2" && reader->attributes().length()>0) {
            //qDebug()<<"Connected2";
            int elemIndex = reader->attributes().at(0).value().toInt();
            connectWireLastPointToElement(wire,cm->getElements()->at(elemIndex));
            //setsConnected2
        }
    }
    return wire;
}

void FileHandler::readPath(QXmlStreamReader *reader, Wire *w)
{
    int x, y;
    while(true) {
        reader->readNext();
        if(reader->isEndElement() && reader->name() == "Path") {
            break;
        }

        if(reader->name()=="Point" && reader->attributes().length()>0) {
            x = reader->attributes().at(0).value().toInt();
            y = reader->attributes().at(1).value().toInt();
            w->addPoint(x,y);
        }
    }
}

void FileHandler::connectWireFirstPointToElement(Wire *w, Element *elem)
{
    QList<Connector*>* connectors = elem->getConnectors();
    QPoint* point = w->getPath()->at(0);
    QList<Connector*>::Iterator i;
    for(i=connectors->begin();i!=connectors->end();i++) {
        if(point->x() == (*i)->getX() && point->y()== (*i)->getY()) {
            w->startConnection((*i));
            break;
        }
    }
    delete connectors;
}

void FileHandler::connectWireLastPointToElement(Wire *w, Element *elem)
{
    QList<Connector*>* connectors = elem->getConnectors();
    QPoint* point = w->getPath()->last();
    QList<Connector*>::Iterator i;
    for(i=connectors->begin();i!=connectors->end();i++) {
        if(point->x() == (*i)->getX() && point->y()== (*i)->getY()) {
            w->endConnection((*i));
            break;
        }
    }
    delete connectors;
}



