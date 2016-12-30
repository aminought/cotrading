include(../deployment.pri)

QT += qml quick charts
CONFIG += c++14
CONFIG += qt
CONFIG -= app_bundle


TEMPLATE = app

SOURCES += main.cpp

LIBS += -L../src -lcotrading

INCLUDEPATH += ../src
INCLUDEPATH += ../libs/websocketpp
INCLUDEPATH += ../libs

RESOURCES += qml.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =
