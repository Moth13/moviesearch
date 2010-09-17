#-------------------------------------------------
#
# Project created by QtCreator 2010-09-15T15:45:55
#
#-------------------------------------------------

QT       += core gui network

TARGET = MovieSearch
TEMPLATE = app
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
