#-------------------------------------------------
#
# Project created by QtCreator 2013-06-26T14:31:07
#
#-------------------------------------------------

QT       += core gui

TARGET = MyZip
TEMPLATE = app

DEFINES += QUAZIP_STATIC
SOURCES += main.cpp\
        mainwindow.cpp \
    quazip/zip.c \
    quazip/unzip.c \
    quazip/quazipnewinfo.cpp \
    quazip/quazipfileinfo.cpp \
    quazip/quazipfile.cpp \
    quazip/quazipdir.cpp \
    quazip/quazip.cpp \
    quazip/quaziodevice.cpp \
    quazip/quagzipfile.cpp \
    quazip/quacrc32.cpp \
    quazip/quaadler32.cpp \
    quazip/qioapi.cpp \
    quazip/JlCompress.cpp

HEADERS  += mainwindow.h \
    quazip/zip.h \
    quazip/unzip.h \
    quazip/quazipnewinfo.h \
    quazip/quazipfileinfo.h \
    quazip/quazipfile.h \
    quazip/quazipdir.h \
    quazip/quazip_global.h \
    quazip/quazip.h \
    quazip/quaziodevice.h \
    quazip/quagzipfile.h \
    quazip/quacrc32.h \
    quazip/quachecksum32.h \
    quazip/quaadler32.h \
    quazip/JlCompress.h \
    quazip/ioapi.h \
    quazip/crypt.h

FORMS    += mainwindow.ui

RESOURCES += \
    menu.qrc
