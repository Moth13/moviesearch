QT       += core gui network

TARGET = MovieSearch
TEMPLATE = app
OBJECTS_DIR = ./build
MOC_DIR = ./build
DESTDIR = ./out
DEPENDPATH += . \
    include \
    src

INCLUDEPATH += include

SOURCES += \
    src/MovieSearchWindow.cpp \
    src/main.cpp \
    src/MovieSearchApp.cpp \
    src/MovieSearchRequest.cpp

HEADERS  += \
    include/MovieSearchApp.h \
    include/MovieSearchWindow.h \
    include/MovieSearchRequest.h
