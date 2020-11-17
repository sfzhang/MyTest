CC = $(DISTCC) gcc
CXX = $(DISTCC) g++
RM = rm -f

mycpptest: mycpptest.cpp
	$(CXX) -g -std=c++11 -o $@ mycpptest.cpp

.PHONE: clean
clean:
	$(RM) mycpptest.o mycpptest
