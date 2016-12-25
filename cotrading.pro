TEMPLATE = app

QT += qml quick
CONFIG += c++14

SOURCES += main.cpp \
    quotesprovider.cpp \
    cqgprovider.cpp \
    cqgclient.cpp

RESOURCES += qml.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Default rules for deployment.
include(deployment.pri)

HEADERS += \
    quotesprovider.h \
    cqgprovider.h \
    cqgclient.h

LIBS += -L/usr/local/lib -lprotobuf -pthread -lpthread -lboost_system -lssl -lcrypto
