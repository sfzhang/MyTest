RM = rm -fr
BINP = ../../bin
LIBP = -L/usr/local/vtk-9.0.1/lib

TARGET = cadpart
SOURCES = cadpart.cpp
LIBS = -lvtkCommonCore-9.0 -lvtkFiltersSources-9.0 -lvtkInteractionStyle-9.0 \
       -lvtkRenderingOpenGL2-9.0 -lvtkCommonExecutionModel-9.0 \
	   -lvtkRenderingCore-9.0 -lvtkIOMotionFX-9.0 -lvtkRenderingLOD-9.0 \
	   -lvtkIOGeometry-9.0


all: $(BINP)/$(TARGET)
$(BINP)/$(TARGET): $(SOURCES)
	g++ -g -o $@ $^ $(LIBP) $(LIBS)

.PHONY:
	$(RM) *.o
	$(RM) $(BINP)/$(TARGET)
