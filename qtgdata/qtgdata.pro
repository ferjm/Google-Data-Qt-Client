#-------------------------------------------------
#
# Project created by QtCreator 2010-12-08T20:11:57
#
#-------------------------------------------------

QT       -= gui
QT       += network

TARGET = qtgdata
TEMPLATE = lib

DEFINES += QTGDATA_LIBRARY QTGDATA_DEBUG

SOURCES += qtgdata.cpp \
    ientity.cpp \
    xmlserializer.cpp \
    httpconnector.cpp

HEADERS += qtgdata.h\
        qtgdata_global.h \
    ientity.h \
    defs.h \
    iparser.h \
    iserializer.h \
    qtgdataclient.h \
    xmlserializer.h \
    httpconnector.h

header_files.files = $$HEADERS
header_files.path = /usr/local/include/qtgdata
INSTALLS += header_files

target.path = /usr/local/lib/
INSTALLS += target
