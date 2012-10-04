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
unix:LIBS   += -L$$PWD/resources/qjson/lib -lqjson
win32:LIBS  += -L$$PWD/resources/qjson/lib -lqjson0

DEPENDPATH  += $$PWD/resources/qjson/lib

HEADERS     +=  \
                include/MSTabInfo.h \
                include/MSData.h \
    include/MSData_TMDB.h \
    include/MSSearchEngine_TMDB.h \
    include/MSSearchEngine.h \
    include/MSTools.h \
    include/MSMainWindow.h

SOURCES     +=  src/main.cpp \
                src/MSTabInfo.cpp \
    src/MSSearchEngine.cpp \
    src/MSSearchEngine_TMDB.cpp \
    src/MSMainWindow.cpp

FORMS       +=  resources/MSMainwindow.ui \
                resources/MSTabInfo.ui














