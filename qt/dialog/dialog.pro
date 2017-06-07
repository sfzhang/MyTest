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
DESTDIR = $(MAKE_HIFU_ROOT)/bin

# preprocessor macros(-D)
DEFINES +=

# include path
INCLUDEPATH +=

# depended library
LIBS +=

# make clean
QMAKE_CLEAN +=

# head files
HEADERS = mainwindow.h \
          imagedialog.h

# source files
SOURCES = mainwindow.cpp \
          imagedialog.cpp \
          dialog.cpp

# TARGET
TARGET = dialog
