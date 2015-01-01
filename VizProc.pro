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
    src/c++/Elements/wire.cpp

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
    src/c++/Elements/wire.h

FORMS    +=
