#-------------------------------------------------
#
# Project created by QtCreator 2014-11-14T23:58:38
#
#-------------------------------------------------

QT       += core gui

TARGET = cutscreen
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp

HEADERS  += mainwindow.h

FORMS    += mainwindow.ui


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
