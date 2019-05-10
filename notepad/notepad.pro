#-------------------------------------------------
#
# Project created by QtCreator 2016-12-11T19:36:47
# 
#-------------------------------------------------

QT       += core gui

TARGET = notepad
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    text.cpp \
    textedit.cpp

HEADERS  += mainwindow.h \
    text.h \
    textedit.h

FORMS    += mainwindow.ui

RC_FILE = notepad.rc
