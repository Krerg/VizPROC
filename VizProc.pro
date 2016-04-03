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
    src/c++/Model/lumatrix.cpp \
    src/c++/Elements/diode.cpp \
    src/c++/Elements/wireconnector.cpp \
    src/c++/View/visualisationmanager.cpp \
    src/c++/View/particle.cpp \
    src/c++/Model/diodebranch.cpp \
    src/c++/Elements/amperemeter.cpp \
    src/c++/Util/programminformationwindow.cpp \
    src/c++/Util/filehandler.cpp \
    src/c++/Controller/graphhandler.cpp \
    src/c++/Util/stylesheetvalues.cpp \
    src/c++/Elements/voltmeter.cpp \
    src/c++/Elements/terminal.cpp \
    src/c++/Util/stringvalues.cpp \
    src/c++/Model/model.cpp \
    src/c++/Controller/applicationcontext.cpp \
    src/c++/Model/branch.cpp \
    src/c++/Model/graph.cpp \
    src/c++/Util/constvalues.cpp \
    src/c++/Exception/multidirectionekementsexception.cpp \
    src/c++/Visualization/amperagevisualisationhandler.cpp \
    src/c++/Visualization/visualization.cpp \
    src/c++/Event/initevent.cpp \
    src/c++/Event/nextstepevent.cpp \
    src/c++/Event/destroyevent.cpp \
    src/c++/Model/branchhandler.cpp \
    src/c++/Util/circuitutils.cpp \
    src/c++/Util/wirehandler.cpp

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
    src/c++/Model/lumatrix.h \
    src/c++/Elements/diode.h \
    src/c++/Elements/wireconnector.h \
    src/c++/View/visualisationmanager.h \
    src/c++/View/particle.h \
    src/c++/Model/diodebranch.h \
    src/c++/Elements/amperemeter.h \
    src/c++/Util/programminformationwindow.h \
    src/c++/Util/filehandler.h \
    src/c++/Controller/graphhandler.h \
    src/c++/Util/stylesheetvalues.h \
    src/c++/Elements/voltmeter.h \
    src/c++/Elements/terminal.h \
    src/c++/Util/stringvalues.h \
    src/c++/Model/model.h \
    src/c++/Controller/applicationcontext.h \
    src/c++/Model/branch.h \
    src/c++/Model/graph.h \
    src/c++/Util/constvalues.h \
    src/c++/Exception/multidirectionekementsexception.h \
    src/c++/Visualization/amperagevisualisationhandler.h \
    src/c++/Visualization/visualization.h \
    src/c++/Event/initevent.h \
    src/c++/Event/nextstepevent.h \
    src/c++/Event/destroyevent.h \
    src/c++/Model/branchhandler.h \
    src/c++/Util/circuitutils.h \
    src/c++/Util/wirehandler.h
FORMS    +=
