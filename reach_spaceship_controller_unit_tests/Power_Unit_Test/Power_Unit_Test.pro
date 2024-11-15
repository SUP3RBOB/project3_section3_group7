QT += testlib
QT -= gui

CONFIG += qt console warn_on depend_includepath testcase
CONFIG -= app_bundle

TEMPLATE = app

SOURCES +=  tst_power_test.cpp
INCLUDEPATH += "../../reach_spaceship_controller"
SOURCES += "../../reach_spaceship_controller/power.cpp"
HEADERS += "../../reach_spaceship_controller/power.h"
