RM = rm -fr
BINP = ../../bin
LIBP = -L/usr/local/vtk-9.0.1/lib

TARGET = buildugrid
SOURCES = buildugrid.cpp
LIBS = -lvtkCommonCore-9.0 -lvtkFiltersSources-9.0 -lvtkInteractionStyle-9.0 \
       -lvtkRenderingOpenGL2-9.0 -lvtkCommonExecutionModel-9.0 \
	   -lvtkRenderingCore-9.0 -lvtkCommonDataModel-9.0 \
	   -lvtkFiltersGeometry-9.0 -lvtkImagingSources-9.0 \
	   -lvtkFiltersGeneral-9.0 -lvtkFiltersCore-9.0 \
	   -lvtkCommonMisc-9.0 -lvtkIOLegacy-9.0 -lvtkCommonColor-9.0

all: $(BINP)/$(TARGET)
$(BINP)/$(TARGET): $(SOURCES)
	g++ -g -o $@ $^ $(LIBP) $(LIBS)

.PHONY: clean
clean:
	$(RM) *.o
	$(RM) $(BINP)/$(TARGET)
