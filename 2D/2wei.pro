#-------------------------------------------------
#
# Project created by QtCreator 2015-04-08T10:52:20
#
#-------------------------------------------------

QT       += core gui

TARGET = 2wei
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
