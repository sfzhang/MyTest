#-------------------------------------------------
#
# Project created by QtCreator 2016-10-20T11:24:29
#
#-------------------------------------------------

TEMPLATE = app

include($(MAKE_HIFU_ROOT)/mak/hifu.pri)

CONFIG += debug \
          warn_on \
          thread

QT += qml quick quickwidgets

TARGET = quick

SOURCES += quick.cpp \
           main.cpp

HEADERS += quick.h

DESTDIR = $(MAKE_HIFU_ROOT)/bin

INCLUDEPATH +=

LIBS += \
    -ldicm \
    -llog \
    -llog4cplus

RESOURCES += qml.qrc \
    qml.qrc
