TEMPLATE     = lib
CONFIG      += plugin

include( ../common-config.pri )

SENSORFW_INCLUDEPATHS = ../.. \
                        ../../include \
                        ../../core \
                        ../../datatypes

DEPENDPATH  += $$SENSORFW_INCLUDEPATHS
INCLUDEPATH += $$SENSORFW_INCLUDEPATHS

include(../common-install.pri)
publicheaders.files += $$HEADERS
target.path = $$PLUGINPATH

contains(CONFIG,binder) {
    INCLUDEPATH += /usr/include/gbinder /usr/include/gutil /usr/include/glib-2.0
    INCLUDEPATH += /usr/lib/x86_64-linux-gnu/glib-2.0/include /usr/lib/arm-linux-gnueabihf/glib-2.0/include /usr/lib/aarch64-linux-gnu/glib-2.0/include
    LIBS += -lgbinder
}

INSTALLS += target
