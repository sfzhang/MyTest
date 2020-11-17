CXX = g++
RM = rm

all: add sub

add: add.cpp
	$(CXX) -g -std=c++11 -o $@ add.cpp

sub: sub.cpp
	$(CXX) -g -std=c++11 -o $@ sub.cpp

.PHONY: clean
clean:
	$(RM) -f add sub
