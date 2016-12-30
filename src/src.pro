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
    cqgsession.cpp \
    providersession.cpp \
    providerconnection.cpp \
    cqgconnection.cpp \
    providerconnectionfactory.cpp \
    contract.cpp \
    websocketclient.cpp \
    ../libs/cqg_webapi/webapi_1.pb.cc

HEADERS += \
    quotesprovider.h \
    cqgprovider.h \
    cqgclient.h \
    config.h \
    menucontroller.h \
    settingscontroller.h \
    cqgsession.h \
    providersession.h \
    providerconnection.h \
    cqgconnection.h \
    providerconnectionfactory.h \
    contract.h \
    websocketclient.h \
    ../libs/cqg_webapi/webapi_1.pb.h

LIBS += -L/usr/local/lib -lprotobuf -pthread -lpthread -lboost_system -lssl -lcrypto -lboost_date_time

INCLUDEPATH += ../libs/websocketpp
INCLUDEPATH += ../libs/cqg_webapi
