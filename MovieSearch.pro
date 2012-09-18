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
DESTDIR     = ./build/out/$$OUT_DIR

INCLUDEPATH += include
#To be changed
INCLUDEPATH += resources/qjson/include

#To be changed
LIBS        += -L../../../resources/qjson/lib -lqjson

HEADERS     +=  include/MSMainwindow.h \
                include/MSTabInfo.h \
                include/MSParser.h

SOURCES     +=  src/main.cpp \
                src/MSTabInfo.cpp \
                src/MSMainwindow.cpp \
                src/MSParser.cpp

FORMS       +=  resources/MSMainwindow.ui \
                resources/MSTabInfo.ui













