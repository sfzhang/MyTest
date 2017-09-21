#
# qmake for treat_test
#

# qmake template: lib or app
TEMPLATE = app

# include protobuf.pri if compile protobuf
# include($(MAKE_HIFU_ROOT)/mak/protobuf.pri)

# include hifu.pri
include($(MAKE_HIFU_ROOT)/mak/hifu.pri)

# CONFIG: debug, warn_on, no-qt, and suport mult-thread
CONFIG += debug \
          warn_on \
          thread \
          plugin

# need qt or not
# CONFIG -= qt
QT += sql widgets

# DESTDIR: where put targets, $(MAKE_HIFU_ROOT)/bin or $(MAKE_HIFU_ROOT)/lib
DESTDIR = $(MAKE_HIFU_ROOT)/bin

# preprocessor macros(-D)
DEFINES +=

# include path 
INCLUDEPATH +=

# depended library
LIBS += -lpub -llog -ldbsql -lthread -llog4cplus

# head files
HEADERS = mtconn.h \
          mainwindow.h

# source files
SOURCES = mtdb.cpp \
          mainwindow.cpp \
          mtconn.cpp

# TARGET
TARGET = mtdb
