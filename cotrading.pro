TEMPLATE = subdirs

CONFIG += c++14
CONFIG += qt

SUBDIRS += src \
    app \
    tests

app.depends = src
tests.depends = src

CONFIG(debug, debug|release) {
    DESTDIR = build/debug
} else {
    DESTDIR = build/release
}

# Default rules for deployment.
include(deployment.pri)
