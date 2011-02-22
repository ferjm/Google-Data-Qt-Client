#-------------------------------------------------
#
# Project created by QtCreator 2011-01-21T14:06:34
#
#-------------------------------------------------

QT       += testlib network

QT       -= gui

TARGET = qtgdatatest
CONFIG   += console kqoauth
CONFIG   -= app_bundle

TEMPLATE = app

LIBS += -L/usr/local/lib -lqtgdata
INCLUDEPATH += /usr/local/include

SOURCES += qtgdatatest.cpp
DEFINES += SRCDIR=\\\"$$PWD/\\\" QTGDATA_DEBUG
