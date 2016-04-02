# QT Modules
QT += qml quick

# Target
TARGET = radarline
TEMPLATE = app

# Extra Configs
CONFIG += c++11
CONFIG(release, debug|release) {
    DEFINES += QT_NO_DEBUG_OUTPUT
}

# Source Files
INCLUDEPATH += src
HEADERS += \
    src/radarline.h

SOURCES += \
    src/main.cpp \
    src/radarline.cpp

# Qml Files
OTHER_FILES += qml/main.qml

# Resources
RESOURCES += radarline.qrc
QMAKE_RESOURCE_FLAGS += -no-compress

# Objects Pathes
DESTDIR = bin
UI_DIR = build
MOC_DIR = build
RCC_DIR = build
OBJECTS_DIR = build
