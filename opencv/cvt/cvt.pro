CONFIG += debug \
          warn_on \
          thread \
          c++11

QT += widgets

TARGET = cvt

TEMPLATE = app

SOURCES += cvt.cpp

HEADERS  += cvt.h

INCLUDEPATH +=

LIBS += -lopencv_core \
        -lopencv_highgui \
        -lopencv_ml

QMAKE_CLEAN += $(DESTDIR)$(TARGET)
