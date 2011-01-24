#-------------------------------------------------
#
# Project created by QtCreator 2010-12-08T20:11:57
#
#-------------------------------------------------

QT       -= gui

TARGET = qtgdata
TEMPLATE = lib

DEFINES += QTGDATA_LIBRARY

SOURCES += qtgdata.cpp \
    ientity.cpp \
    qtgdataclient.cpp

HEADERS += qtgdata.h\
        qtgdata_global.h \
    ientity.h \
    defs.h \
    iparser.h \
    iserializer.h \
    iconnector.h \
    qtgdataclient.h

header_files.files = $$HEADERS
header_files.path = /usr/local/include/qtgdata
INSTALLS += header_files

target.path = /usr/local/lib/
INSTALLS += target
