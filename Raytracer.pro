#-------------------------------------------------
#
# Project created by QtCreator 2017-04-09T15:49:49
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Raytracer
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += main.cpp\
        mainwindow.cpp \
    geometry.cpp \
    cube.cpp \
    sphere.cpp \
    triangle.cpp \
    squareplane.cpp \
    mesh.cpp \
    intersection.cpp \
    ray.cpp \
    jsonparser.cpp \
    camera.cpp \
    material.cpp \
    scene.cpp \
    tiny_obj_loader.cc

HEADERS  += mainwindow.h \
    geometry.h \
    cube.h \
    sphere.h \
    triangle.h \
    squareplane.h \
    mesh.h \
    intersection.h \
    ray.h \
    jsonparser.h \
    la.h \
    camera.h \
    material.h \
    scene.h \
    tiny_obj_loader.h

FORMS    += mainwindow.ui
