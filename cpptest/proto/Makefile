CXX = g++
PROTOC = protoc
RM = rm -f

all: libproto.so

libproto.so: imgxfer.proto imgxferproto.cpp
	$(PROTOC) --cpp_out=. imgxfer.proto
	$(CXX) -g -std=c++11 -fPIC -c imgxfer.pb.cc
	$(CXX) -g -std=c++11 -fPIC -c imgxferproto.cpp
	$(CXX) -shared -o $@ imgxfer.pb.o imgxferproto.o

clean:
	$(RM) libproto.so *.o imgxfer.pb.h imgxfer.pb.cc
