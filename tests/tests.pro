TEMPLATE = app
CONFIG += console c++14
CONFIG -= app_bundle
CONFIG += qt

SOURCES += main.cpp \
    config_test.cpp \
    cqgprovider_test.cpp

LIBS += -L../src -lgtest -lgmock -lcotrading -lboost_system -lssl -lcrypto -lboost_date_time

INCLUDEPATH += ../src
INCLUDEPATH += ../libs/websocketpp

DISTFILES +=

RESOURCES += \
    resources.qrc
