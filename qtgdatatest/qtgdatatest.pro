#-------------------------------------------------
#
# Project created by QtCreator 2011-01-21T14:06:34
#
#-------------------------------------------------

QT       += testlib

QT       -= gui

TARGET = qtgdatatest
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app

LIBS += -L/usr/local/lib/qtgdata -lqtgdata

SOURCES += qtgdatatest.cpp
DEFINES += SRCDIR=\\\"$$PWD/\\\"
