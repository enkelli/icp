#-------------------------------------------------
#
# Project created by QtCreator 2016-04-26T08:46:08
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = hra2016-gui
TEMPLATE = app

LIBS += -L boost/lib -lboost_serialization

INCLUDEPATH += ../

OBJECTS += ../AI_player.o ../algorithm_chimpanzee.o ../algorithm_monkey.o ../command_manager.o ../game.o ../othello.o ../table_move_command.o ../table.o

QMAKE_CXXFLAGS += -std=c++11 -isystem boost -g

SOURCES += main.cpp\
        mainwindow.cpp \
    stonewidget.cpp

HEADERS  += mainwindow.h \
    stonewidget.h

FORMS    += mainwindow.ui

RESOURCES += \
    resources.qrc
