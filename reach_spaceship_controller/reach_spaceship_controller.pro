QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    Map.cpp \
    comms.cpp \
    earth.cpp \
    hull.cpp \
    lifesupport.cpp \
    lights.cpp \
    main.cpp \
    mainwindow.cpp \
    navigation.cpp \
    planet.cpp \
    power.cpp \
    simulation.cpp \
    spaceship.cpp \
    thruster.cpp

HEADERS += \
    Map.h \
    comms.h \
    Lights.h \
    earth.h \
    hull.h \
    isavable.h \
    lifesupport.h \
    mainwindow.h \
    navigation.h \
    planet.h \
    power.h \
    simulation.h \
    spaceship.h \
    thruster.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
