#-------------------------------------------------
#
# Project created by QtCreator 2010-12-08T20:11:57
#
#-------------------------------------------------

QT       -= gui
QT       += network

CONFIG += kqoauth

TARGET = qtgdata
TEMPLATE = lib

DEFINES += QTGDATA_LIBRARY QTGDATA_DEBUG

SOURCES += qtgdata.cpp \
    qtgdataientity.cpp \
    qtgdataxmlserializer.cpp \
    qtgdatahttpconnector.cpp \
    qtgdataxmlparser.cpp \
    qtgdataoauth.cpp \
    qtgdatahttprequest.cpp

HEADERS += qtgdata.h\
        qtgdata_global.h \
    qtgdataientity.h \
    qtgdatadefs.h \
    qtgdataiparser.h \
    qtgdataiserializer.h \
    qtgdataclient.h \
    qtgdataxmlserializer.h \
    qtgdatahttpconnector.h \
    qtgdataxmlparser.h \
    qtgdataoauth.h \
    qtgdatahttprequest.h

header_files.files = $$HEADERS
header_files.path = /usr/local/include/qtgdata
INSTALLS += header_files

target.path = /usr/local/lib/
INSTALLS += target
