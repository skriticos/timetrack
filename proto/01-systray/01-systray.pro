QT     += widgets
CONFIG += c++11

TARGET   = 01-systray
TEMPLATE = app

SOURCES += main.cpp systrayproto.cpp
HEADERS  += systrayproto.h

RESOURCES += \
    icons.qrc
