#-------------------------------------------------
#
# Project created by QtCreator 2015-03-04T18:51:36
#
#-------------------------------------------------

QT       += core

TARGET = QtRptCGI
CONFIG   += console
CONFIG   -= gui
CONFIG   -= app_bundle

TEMPLATE = app

include(../QtRPT/QtRPT.pri)
DESTDIR = $${DEST_DIRECTORY}

SOURCES += main.cpp
