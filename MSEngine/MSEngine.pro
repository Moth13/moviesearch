#-------------------------------------------------
#
# Project created by QtCreator 2012-09-17T10:40:04
#
#-------------------------------------------------
VERSION     = 0.0.1
DEFINES     += MSEngine_VERSION=\'\"$$VERSION\"\'

QT          += core network

OUT_DIR     = release

contains( CONFIG, debug )
{
    DEFINES += _DEBUG
    OUT_DIR = debug
}

windows:
{
    DEFINES   += MSEngine_MAKEDLL
}

TARGET      = MSEngine
TEMPLATE    = lib

OBJECTS_DIR = ./build/objectfile/$$OUT_DIR
MOC_DIR     = ./build/moc/$$OUT_DIR
DESTDIR     = ../build/$$OUT_DIR/lib/

INCLUDEPATH += include

HEADERS     += \
    include/MSTools.h \
    include/MSData.h \
    include/MSDataMovie.h \
    include/MSDataPerson.h \
    include/MSEngineExport.h \
    include/MSSearchEngine.h

SOURCES     += \
    src/MSSearchEngine.cpp

target.files    = include/*
target.path     = ../build/$$OUT_DIR/include
INSTALLS        += target



















