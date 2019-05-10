#-------------------------------------------------
#
# Project created by QtCreator 2016-11-06T00:53:47
#
#-------------------------------------------------

QT       += core gui

TARGET = system_test1
TEMPLATE = app

RC_FILE = system.rc


SOURCES += main.cpp\
        mainwindow.cpp \
    Show.cpp \
    Edit.cpp

HEADERS  += mainwindow.h \
    filesystem.h \
    Show.h \
    Edit.h

INCLUDEPATH +=$(OPENCV23_MINGW)\include
LIBS        += -L$(OPENCV23_MINGW)\lib


LIBS        += -lopencv_calib3d231.dll \
               -lopencv_contrib231.dll \
    -lopencv_core231.dll \
    -lopencv_features2d231.dll \
    -lopencv_flann231.dll \
    -lopencv_gpu231.dll \
    -lopencv_highgui231.dll \
    -lopencv_imgproc231.dll \
    -lopencv_legacy231.dll \
    -lopencv_ml231.dll \
    -lopencv_objdetect231.dll \
    -lopencv_video231.dll
