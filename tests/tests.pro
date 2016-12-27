TEMPLATE = app
CONFIG += console c++14
CONFIG -= app_bundle
CONFIG += qt

SOURCES += main.cpp \
    ../config.cpp \
    config_test.cpp

LIBS += -lgtest

DISTFILES +=

HEADERS += \
    ../config.h
