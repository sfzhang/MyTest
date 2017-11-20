#
# qmake for eval test
#

# include protobuf.pri if compile protobuf
# include($(MAKE_HIFU_ROOT)/mak/protobuf.pri)

# include hifu.pri
include($(MAKE_HIFU_ROOT)/mak/hifu.pri)

# qmake template: lib or app
TEMPLATE = app

# CONFIG: debug, warn_on, no-qt, and suport mult-thread
CONFIG += debug \
          warn_on \
          thread \
          plugin

# need qt or not
# CONFIG -= qt
QT += widgets

# DESTDIR: where put targets, $(MAKE_HIFU_ROOT)/bin or $(MAKE_HIFU_ROOT)/lib
# DESTDIR = $(MAKE_HIFU_ROOT)/bin

# preprocessor macros(-D)
DEFINES +=

# include path
INCLUDEPATH +=

# depended library
LIBS +=

# make clean
QMAKE_CLEAN +=

# head files
HEADERS = \
    iconhelper.h \
    circulariconhelper.h \
    ringediconhelper.h \
    dial.h \
    circularbutton.h

# source files
SOURCES = \
    dial.cpp \
    main.cpp \
    circularbutton.cpp

# TARGET
TARGET = dial

# RESOURCE
RESOURCES = dial.qrc
