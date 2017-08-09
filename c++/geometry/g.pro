#
# qmake for mrghifu
#

# qmake template: lib or app
TEMPLATE = app

# include hifu.pri
include($(MAKE_HIFU_ROOT)/mak/hifu.pri)

# CONFIG: debug, warn_on, no-qt, and suport mult-thread
CONFIG += debug \
          warn_on \
          thread

# need qt or not
# CONFIG -= qt

# plugle
QT += widgets \
      network \
      sql \
      printsupport \
      multimedia

# DESTDIR: where put targets, $(MAKE_HIFU_ROOT)/bin or $(MAKE_HIFU_ROOT)/lib
DESTDIR = ./

# preprocessor macros(-D)
DEFINES += MRGFUS_IMPORT

# include path
INCLUDEPATH +=

# depended library
LIBS += -lpub \
        -llog \
        -ldicm \
        -ltherm \
        -lstats \
        -lproto \
        -llog4cplus \
        -lboost_system \
        -lboost_filesystem \
        -lplan \
        -lposition \
        -lhwif \
        -larmproto \
        -larmadillo \
        -lscmproto \
        -lconfig \
        -ldbo \
        -ldbsql \
        -ldbservice \
        -lmsg \
        -ltherm \
        -lthread \
        -lmainwidget \
        -limagewidget \
        -lbuttonwidget \
        -lthermwidget \
        -lmq \
        -lshm \
        -lwidgethelper \
        -linfowidget \
        -ldicmview \
        -ldicmcache \
        -lfeedback \
        -lutilwidget \
        -lprobemovement \
        -ltreatprepare \
        -ltreatparameter \
        -ldatawidget \
        -lresource \
        -lstate \
        -lmotiondetect \
        -lreportwidget \
        -lmrictrl \
        -lqwt \
        -lopencv_core -lopencv_ml -lopencv_calib3d -lopencv_imgproc -locvadapter

# head files
HEADERS =

# source files
SOURCES = g.cpp

# TARGET
TARGET = g

