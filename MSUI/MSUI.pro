#-------------------------------------------------
#
# Project created by QtCreator 2012-09-17T10:40:04
#
#-------------------------------------------------
VERSION     = 0.0.1
DEFINES     += MS_VERSION=\'\"$$VERSION\"\'

QT          += core gui network

OUT_DIR     = release

contains( CONFIG, debug )
{
    DEFINES += _DEBUG
    OUT_DIR = debug
}

TARGET      = MovieSearch
TEMPLATE    = app

OBJECTS_DIR = ./build/objectfile/$$OUT_DIR
MOC_DIR     = ./build/moc/$$OUT_DIR
DESTDIR     = ../build/$$OUT_DIR

INCLUDEPATH += include
#To be changed
INCLUDEPATH += ../build/$$OUT_DIR/include

#To be changed
LIBS        += -L../build/$$OUT_DIR/lib -lMSEngine
LIBS        += -L./lib -lMSEngine

DEPENDPATH  += ../build/$$OUT_DIR/lib

HEADERS     +=  \
    include/MSImage.h \
    include/MSTabInfo.h \
    include/MSMainWindow.h \

SOURCES     += \
    src/MSImage.cpp \
    src/MSTabInfo.cpp \
    src/MSMainWindow.cpp \
    src/main.cpp \

FORMS       +=  resources/MSMainwindow.ui \
                resources/MSTabInfo.ui




















