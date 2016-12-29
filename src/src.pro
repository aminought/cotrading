include(../deployment.pri)

TEMPLATE = lib

CONFIG += c++14
CONFIG += qt

TARGET = cotrading

SOURCES += \
    quotesprovider.cpp \
    cqgprovider.cpp \
    cqgclient.cpp \
    config.cpp \
    menucontroller.cpp \
    settingscontroller.cpp \
    ../libs/cqg_webapi/webapi_1.pb.cc \
    cqgsession.cpp \
    providersession.cpp \
    providerconnection.cpp \
    cqgconnection.cpp \
    providerconnectionfactory.cpp

HEADERS += \
    quotesprovider.h \
    cqgprovider.h \
    cqgclient.h \
    config.h \
    menucontroller.h \
    settingscontroller.h \
    ../libs/cqg_webapi/webapi_1.pb.h \
    cqgsession.h \
    providersession.h \
    providerconnection.h \
    cqgconnection.h \
    providerconnectionfactory.h

LIBS += -L/usr/local/lib -lprotobuf -pthread -lpthread -lboost_system -lssl -lcrypto -lboost_date_time

QMAKE_CXXFLAGS += -isystem "../../../src/../libs"
