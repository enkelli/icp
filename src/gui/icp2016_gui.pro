#-------------------------------------------------
#
# Project created by QtCreator 2016-04-26T08:46:08
#
#-------------------------------------------------

QT       += core gui concurrent

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = hra2016
TEMPLATE = app

LIBS += -L ../boost/lib -lboost_serialization

INCLUDEPATH += ../common

OBJECTS += ../common/*.o

QMAKE_CXXFLAGS += -std=c++11 -isystem ../boost

SOURCES += main.cpp\
        mainwindow.cpp \
    stonewidget.cpp \
    newgamedialog.cpp \
    welcomedialog.cpp \
    aboutdialog.cpp

HEADERS  += mainwindow.h \
    stonewidget.h \
    newgamedialog.h \
    welcomedialog.h \
    aboutdialog.h

FORMS    += mainwindow.ui \
    newgamedialog.ui \
    welcomedialog.ui \
    aboutdialog.ui

RESOURCES += \
    resources.qrc
