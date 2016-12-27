TEMPLATE = app
CONFIG += console c++14
CONFIG -= app_bundle
CONFIG += qt

SOURCES += main.cpp \
    config_test.cpp

LIBS += -L../src -lgtest -lcotrading

INCLUDEPATH += ../src

DISTFILES +=
