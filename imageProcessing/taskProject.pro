#-------------------------------------------------
#
# Project created by QtCreator 2014-07-22T16:48:26
#
#-------------------------------------------------

QT       += core gui

TARGET = taskProject
TEMPLATE = app


SOURCES += main.cpp\
        widget.cpp \
    outedge.cpp \
    backpro.cpp \
    findcon.cpp \
    huofuTrans.cpp

HEADERS  += widget.h \
    outedge.h \
    backpro.h \
    findcontour.h \
    huofuTrans.h




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
