#-------------------------------------------------
#
# Project created by QtCreator 2011-11-07T21:23:47
#
#-------------------------------------------------

QT       += core gui

TARGET = CvGUIExample02
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp

HEADERS  += mainwindow.h

FORMS    += mainwindow.ui


INCLUDEPATH +=C:\OpenCV\install\include

LIBS+=-LC:\OpenCV\install\bin \
-lopencv_core240 \
-lopencv_highgui240 \
-lopencv_imgproc240 \
-lopencv_features2d240 \
-lopencv_calib3d240
