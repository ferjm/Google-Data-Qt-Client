#-------------------------------------------------
#
# Project created by QtCreator 2010-12-08T20:11:57
#
#-------------------------------------------------

QT       -= gui
QT       += network xml

TARGET = qtgdata
TEMPLATE = lib

DEFINES += QTGDATA_LIBRARY

SOURCES += core/qtgdata.cpp \
    core/qtgdataientity.cpp \
    core/qtgdataxmlserializer.cpp \
    core/qtgdatahttpconnector.cpp \
    core/qtgdataxmlparser.cpp \
    core/qtgdataoauth.cpp \
    core/qtgdatahttprequest.cpp \
    core/qtgdataoauthrequest.cpp \
    core/qtgdataclient.cpp \
    core/qtgdataoauthdata.cpp \
    clients/blogger/qtgdatabloggerclient.cpp

HEADERS += core/qtgdata.h\
        core/qtgdata_global.h \
    core/qtgdataientity.h \
    core/qtgdatadefs.h \
    core/qtgdataiparser.h \
    core/qtgdataiserializer.h \
    core/qtgdataclient.h \
    core/qtgdataxmlserializer.h \
    core/qtgdatahttpconnector.h \
    core/qtgdataxmlparser.h \
    core/qtgdataoauth.h \
    core/qtgdatahttprequest.h \
    core/qtgdataoauthrequest.h \
    core/qtgdataiauthentication.h \
    core/qtgdataoauthdata.h \
    clients/blogger/qtgdatabloggerclient.h \
    data/blogger/qtgdatabloggerdata.h \
    data/blogger/qtgdataatomentry.h

INCLUDEPATH += core clients data data/blogger

header_files.files = $$HEADERS
header_files.path = /usr/local/include/qtgdata
INSTALLS += header_files

target.path = /usr/local/lib/
INSTALLS += target
