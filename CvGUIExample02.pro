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


INCLUDEPATH +=C:\OpenCV2.3.0\include

LIBS+=-LC:\OpenCV2.3.0\bin \
-lopencv_core230 \
-lopencv_highgui230 \
-lopencv_imgproc230 \
-lopencv_features2d230 \
-lopencv_calib3d230
