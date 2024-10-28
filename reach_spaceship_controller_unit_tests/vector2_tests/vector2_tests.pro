QT += testlib
QT -= gui

CONFIG += qt console warn_on depend_includepath testcase
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += tst_vector2_tests.cpp

INCLUDEPATH += "../../reach_spaceship_controller"
SOURCES += ../../reach_spaceship_controller/vector2.cpp
