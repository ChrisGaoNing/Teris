


#-------------------------------------------------
#
# Project created by QtCreator 2018-4-25T16:35:11
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Tetris
TEMPLATE = app


SOURCES += main.cpp\
    controller.cpp \
    teris.cpp \
    block.cpp \
    map.cpp \
    mainscene.cpp \
    mainscenebutton.cpp \
    startbutton.cpp \
    mainwindow.cpp

HEADERS  += \
    constants.h \
    controller.h \
    teris.h \
    block.h \
    map.h \
    mainscene.h \
    mainscenebutton.h \
    startbutton.h \
    mainwindow.h

FORMS    += mainwindow.ui

RESOURCES += \
    resource.qrc
