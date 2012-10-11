#-------------------------------------------------
#
# Project created by QtCreator 2012-09-17T10:40:04
#
#-------------------------------------------------
CONFIG += ordered

MSEngine.subdir     = MSEngine
MSPlugins.depends   = MSEngine
MSPlugins.subdir    = MSPlugins
MSUI.depends        = MSEngine
MSUI.subdir         = MSUI

TEMPLATE            = subdirs
SUBDIRS             = MSEngine MSPlugins MSUI
