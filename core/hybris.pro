QT += network

TEMPLATE = lib
TARGET = hybrissensorfw

include( ../common-config.pri )

SENSORFW_INCLUDEPATHS = .. \
                        ../include \
                        ../filters \
                        ../datatypes

DEPENDPATH += $$SENSORFW_INCLUDEPATHS
INCLUDEPATH += $$SENSORFW_INCLUDEPATHS

QMAKE_LIBDIR_FLAGS += -lsensordatatypes-qt5

SOURCES += hybrisadaptor.cpp
HEADERS += hybrisadaptor.h
LIBS += -L$$[QT_INSTALL_LIBS] -L../datatypes

!contains(CONFIG,binder) {
    INCLUDEPATH += /usr/include/android
    LIBS += -lhybris-common -lhardware
} else {
    INCLUDEPATH += /usr/include/gbinder /usr/include/gutil /usr/include/glib-2.0
    INCLUDEPATH += /usr/lib/x86_64-linux-gnu/glib-2.0/include /usr/lib/arm-linux-gnueabihf/glib-2.0/include /usr/lib/aarch64-linux-gnu/glib-2.0/include
    LIBS += -lgbinder
}

include(../common-install.pri)
target.path = $$SHAREDLIBPATH
INSTALLS += target
