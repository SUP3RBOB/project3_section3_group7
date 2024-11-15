QT += testlib
QT += gui

CONFIG += qt console warn_on depend_includepath testcase
CONFIG -= app_bundle

TEMPLATE = app

SOURCES +=  tst_simulation_tests.cpp
HEADERS += "../../reach_spaceship_controller/power.h"
HEADERS += "../../reach_spaceship_controller/comms.h"
INCLUDEPATH += "../../reach_spaceship_controller"
SOURCES += "../../reach_spaceship_controller/simulation.cpp"
SOURCES += "../../reach_spaceship_controller/power.cpp"
SOURCES += "../../reach_spaceship_controller/lights.cpp"
SOURCES += "../../reach_spaceship_controller/navigation.cpp"
SOURCES += "../../reach_spaceship_controller/lifesupport.cpp"
SOURCES += "../../reach_spaceship_controller/hull.cpp"
SOURCES += "../../reach_spaceship_controller/thruster.cpp"
SOURCES += "../../reach_spaceship_controller/comms.cpp"
SOURCES += "../../reach_spaceship_controller/Map.cpp"
SOURCES += "../../reach_spaceship_controller/planet.cpp"
SOURCES += "../../reach_spaceship_controller/spaceship.cpp"
SOURCES += "../../reach_spaceship_controller/earth.cpp"
