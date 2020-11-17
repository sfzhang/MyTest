RM = rm -fr
BINP = ../../bin
LIBP = -L/usr/local/vtk-9.0.1/lib

TARGET = marching
SOURCES = marching.cpp
LIBS = -lvtkCommonCore-9.0 -lvtkFiltersSources-9.0 -lvtkInteractionStyle-9.0 \
       -lvtkRenderingOpenGL2-9.0 -lvtkCommonExecutionModel-9.0 \
	   -lvtkRenderingCore-9.0 -lvtkCommonDataModel-9.0 \
	   -lvtkInteractionWidgets-9.0 -lvtkRenderingAnnotation-9.0 \
	   -lvtkFiltersGeneral-9.0 -lvtkFiltersCore-9.0 \
	   -lvtkCommonTransforms-9.0 -lvtkIOParallel-9.0 \
	   -lvtkFiltersModeling-9.0 -lvtkIOGeometry-9.0 \
	   -lvtkRenderingLOD-9.0 -lvtkRenderingLabel-9.0 \
	   -lvtkCommonMisc-9.0 -lvtkFiltersExtraction-9.0 \
	   -lvtkRenderingFreeType-9.0


all: $(BINP)/$(TARGET)
$(BINP)/$(TARGET): $(SOURCES)
	g++ -g -o $(BINP)/$(TARGET) $(SOURCES) $(LIBP) $(LIBS)

.PHONY:
	$(RM) *.o
	$(RM) $(BINP)/$(TARGET)
