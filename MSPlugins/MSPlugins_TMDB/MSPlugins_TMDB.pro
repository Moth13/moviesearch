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
unix:LIBS   += -L./resources/qjson/lib -lqjson
win32:LIBS  += -L./resources/qjson/lib -lqjson0

LIBS        += -L./../../build/$$OUT_DIR/lib -lMSEngine

DEPENDPATH  += ./resources/qjson/lib
DEPENDPATH  += ./../../build/$$OUT_DIR/lib

HEADERS     +=  \
    include/MSData_TMDB.h \
    include/MSSearchEngine_TMDB.h \

SOURCES     +=  \
    src/MSSearchEngine_TMDB.cpp \


target_tmdb_lib.files    = ./resources/qjson/lib/libqjson.so
target_tmdb_lib.path     = $$DESTDIR/lib
target_tmdb_image.files    = ./resources/*.png
target_tmdb_image.path     = $$DESTDIR/resources/
INSTALLS        += target_tmdb_lib
INSTALLS        += target_tmdb_image



















