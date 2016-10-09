#-------------------------------------------------
#
# Project created by QtCreator 2015-04-23T22:14:09
#
#-------------------------------------------------

QT       += core gui
QT       += multimedia
QT       += sql
QT       += network
QT       += xml
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Mp3
TEMPLATE = app


SOURCES += main.cpp\
        widget.cpp \
    MusicLrcLabel.cpp \
    MusicListWidget.cpp \
    SearchWidget.cpp \
    SkinWidget.cpp \
    Thread.cpp \
    MiniWidget.cpp \
    Network.cpp \
    DownloadWidget.cpp \
    LrcThread.cpp \
    MusicThread.cpp \
    PicThread.cpp \
    ExtensionWidget.cpp \
    SearchThread.cpp \
    ExtensionListWidget.cpp \
    MusicDownThread.cpp \
    LrcWidget.cpp \
    ItemWidget.cpp \
    ListWidget.cpp \
    ListThread.cpp \
    PicListWidget.cpp

HEADERS  += widget.h \
    MusicLrcLabel.h \
    MusicListWidget.h \
    SearchWidget.h \
    SkinWidget.h \
    connection.h \
    Thread.h \
    MiniWidget.h \
    Network.h \
    DownloadWidget.h \
    LrcThread.h \
    MusicThread.h \
    PicThread.h \
    ExtensionWidget.h \
    SearchThread.h \
    ExtensionListWidget.h \
    MusicDownThread.h \
    LrcWidget.h \
    ItemWidget.h \
    ListWidget.h \
    ListThread.h \
    PicListWidget.h

RESOURCES += images.qrc
RC_FILE = icoico.rc
