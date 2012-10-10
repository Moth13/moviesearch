#-------------------------------------------------
#
# Project created by QtCreator 2012-09-17T10:40:04
#
#-------------------------------------------------
VERSION     = 0.0.1
DEFINES     += MSPlugins_TMDB_VERSION=\'\"$$VERSION\"\'

QT          += core network

OUT_DIR     = release

contains( CONFIG, debug )
{
    DEFINES += _DEBUG
    OUT_DIR = debug
}

TARGET      = MSPlugins_TMDB
TEMPLATE    = lib
CONFIG      += plugin

OBJECTS_DIR = ./build/objectfile/$$OUT_DIR
MOC_DIR     = ./build/moc/$$OUT_DIR
DESTDIR     = ../../build/$$OUT_DIR/plugins/

INCLUDEPATH += include
#To be changed
INCLUDEPATH += ./resources/qjson/include
INCLUDEPATH += $$PWD/../../build/$$OUT_DIR/include

#To be changed
unix:LIBS   += -L$$PWD/resources/qjson/lib -lqjson
win32:LIBS  += -L$$PWD/resources/qjson/lib -lqjson0

LIBS        += -L$$PWD/../../build/$$OUT_DIR/lib -lMSEngine

DEPENDPATH  += $$PWD/resources/qjson/lib
DEPENDPATH  += $$PWD/../../build/$$OUT_DIR/lib

HEADERS     +=  \
    include/MSData_TMDB.h \
    include/MSSearchEngine_TMDB.h \

SOURCES     +=  \
    src/MSSearchEngine_TMDB.cpp \


target_tmdb.files    = ./resources
target_tmdb.path     = $$DESTDIR
INSTALLS        += target_tmdb



















