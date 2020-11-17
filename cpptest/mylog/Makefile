CXX = g++
RM = rm

all: libmylog.so
libmylog.so: mylog.cpp
	$(CXX) -g -std=c++11 -fPIC -c mylog.cpp
	$(CXX) -shared -o $@ mylog.o

.PHONE:clean
clean:
	$(RM) -f mylog.o libmylog.so
