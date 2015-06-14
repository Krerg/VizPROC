#-------------------------------------------------
#
# Project created by QtCreator 2014-08-28T00:35:50
#
#-------------------------------------------------

QT       += core gui \
            opengl

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = VizProc
TEMPLATE = app


SOURCES += main.cpp\
        src/c++/View/startscreen.cpp \
    windowmanager.cpp \
    src/c++/View/workbench.cpp \
    initcontroller.cpp \
    src/c++/View/oglrender.cpp \
    src/c++/View/componentmanager.cpp \
    src/c++/Elements/resistor.cpp \
    src/c++/View/updatethread.cpp \
    src/c++/Controller/eventhandler.cpp \
    src/c++/Elements/element.cpp \
    src/c++/Elements/emf.cpp \
    src/c++/Elements/connector.cpp \
    src/c++/View/mousetrackerthread.cpp \
    src/c++/Elements/wire.cpp \
    src/c++/Elements/ground.cpp \
    src/c++/Util/geometry.cpp \
    src/c++/Model/graph.cpp \
    src/c++/Model/lumatrix.cpp \
    src/c++/Elements/diode.cpp \
    src/c++/Elements/wireconnector.cpp \
    src/c++/View/visualisationmanager.cpp \
    src/c++/View/particle.cpp \
    src/c++/Model/diodebranch.cpp \
    src/c++/Elements/amperemeter.cpp \
    src/c++/Util/programminformationwindow.cpp

HEADERS  += src/c++/View/startscreen.h \
    windowmanager.h \
    src/c++/View/workbench.h \
    main.h \
    initcontroller.h \
    src/c++/View/oglrender.h \
    src/c++/View/componentmanager.h \
    src/c++/Elements/resistor.h \
    src/c++/View/updatethread.h \
    src/c++/Controller/eventhandler.h \
    src/c++/Elements/element.h \
    src/c++/Elements/emf.h \
    src/c++/Elements/connector.h \
    src/c++/View/mousetrackerthread.h \
    src/c++/Elements/wire.h \
    src/c++/Elements/ground.h \
    src/c++/Util/geometry.h \
    src/c++/Model/graph.h \
    src/c++/Model/lumatrix.h \
    src/c++/Elements/diode.h \
    src/c++/Elements/wireconnector.h \
    src/c++/View/visualisationmanager.h \
    src/c++/View/particle.h \
    src/c++/Model/diodebranch.h \
    src/c++/Elements/amperemeter.h \
    src/c++/Util/programminformationwindow.h
FORMS    +=
