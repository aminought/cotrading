include(../deployment.pri)

TEMPLATE = lib

CONFIG += c++14
CONFIG += qt

TARGET = cotrading

SOURCES += \
    chart/horizontalline.cpp \
    coop/coopclient.cpp \
    coop/coopconnection.cpp \
    coop/coopmessage.cpp \
    coop/coopserver.cpp \
    core/chartcontroller.cpp \
    core/config.cpp \
    core/menucontroller.cpp \
    core/settingscontroller.cpp \
    trading/model/contract.cpp \
    trading/model/timebar.cpp \
    trading/network/websocketclient.cpp \
    trading/provider/cqg/cqgclient.cpp \
    trading/provider/cqg/cqgconnection.cpp \
    trading/provider/cqg/cqgprovider.cpp \
    trading/provider/cqg/cqgsession.cpp \
    trading/provider/providerconnection.cpp \
    trading/provider/providerconnectionfactory.cpp \
    trading/provider/providersession.cpp \
    trading/provider/quotesprovider.cpp \
    ../libs/cqg_webapi/webapi_1.pb.cc \
    core/toolbarcontroller.cpp \
    trading/provider/sharedproviderconnection.cpp

HEADERS += \
    chart/horizontalline.h \
    coop/coopclient.h \
    coop/coopconnection.h \
    coop/coopmessage.h \
    coop/coopserver.h \
    core/chartcontroller.h \
    core/config.h \
    core/menucontroller.h \
    core/settingscontroller.h \
    trading/model/contract.h \
    trading/model/timebar.h \
    trading/network/websocketclient.h \
    trading/provider/cqg/cqgclient.h \
    trading/provider/cqg/cqgconnection.h \
    trading/provider/cqg/cqgprovider.h \
    trading/provider/cqg/cqgsession.h \
    trading/provider/providerconnection.h \
    trading/provider/providerconnectionfactory.h \
    trading/provider/providersession.h \
    trading/provider/quotesprovider.h \
    ../libs/cqg_webapi/webapi_1.pb.h \
    ../libs/json/src/json.hpp \
    core/toolbarcontroller.h \
    trading/provider/sharedproviderconnection.h

LIBS += -L/usr/local/lib -lprotobuf -pthread -lpthread -lboost_system -lssl -lcrypto -lboost_date_time

INCLUDEPATH += ../libs/websocketpp
INCLUDEPATH += ../libs/cqg_webapi
INCLUDEPATH += ../libs/json/src
